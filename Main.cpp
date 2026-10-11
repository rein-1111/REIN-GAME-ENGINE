
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Renderer.hpp"
#include "Windowing/Windowing.hpp"

std::string vertShader = R"(
#version 460 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 vColor;
out vec3 vNormal;
out vec3 vFragPos;
void main()
{
    vec4 worldPos=model*vec4(aPos,1.0);
    vFragPos=worldPos.xyz;
    vNormal=mat3(transpose(inverse(model)))*aNormal;
    vColor=aColor;
    gl_Position=projection*view*worldPos;
}
)";

std::string fragShader = R"(
#version 460 core
in vec3 vColor;
in vec3 vNormal;
in vec3 vFragPos;
uniform vec3 lightPos;
uniform vec3 viewPos;
out vec4 FragColor;
void main()
{
    vec3 normal=normalize(vNormal);
    vec3 lightDir=normalize(lightPos-vFragPos);
    vec3 viewDir=normalize(viewPos-vFragPos);
    vec3 reflectDir=reflect(-lightDir,normal);
    vec3 ambient=0.15*vColor;
    float diff=max(dot(normal,lightDir),0.0);
    vec3 diffuse=diff*vColor;
    float spec=pow(max(dot(viewDir,reflectDir),0.0),32.0);
    vec3 specular=vec3(0.5)*spec;
    FragColor=vec4(ambient+diffuse+specular,1.0);
}
)";

std::string screenVertShader = R"(
#version 460 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec2 aUV;
out vec2 vUV;
void main()
{
    vUV=aUV;
    gl_Position=vec4(aPos,0.0,1.0);
}
)";

std::string screenFragShader = R"(
#version 460 core
in vec2 vUV;
uniform sampler2D screenTexture;
out vec4 FragColor;

void main()
{
    vec4 color = texture(screenTexture, vUV);
    FragColor = vec4(color.r, color.g * 0.3, color.b * 0.3, color.a);
}
)";

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.5f, 1, 0, 0, 0, 0, 1,
    0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 0, 1,
    0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0, 1,
    -0.5f, 0.5f, 0.5f, 1, 1, 0, 0, 0, 1,

    0.5f, -0.5f, -0.5f, 0, 1, 1, 0, 0, -1,
    -0.5f, -0.5f, -0.5f, 1, 0, 1, 0, 0, -1,
    -0.5f, 0.5f, -0.5f, 1, 1, 1, 0, 0, -1,
    0.5f, 0.5f, -0.5f, 0.2f, 0.8f, 1, 0, 0, -1,

    -0.5f, -0.5f, -0.5f, 1, 0, 1, -1, 0, 0,
    -0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0, 0,
    -0.5f, 0.5f, 0.5f, 1, 1, 0, -1, 0, 0,
    -0.5f, 0.5f, -0.5f, 1, 1, 1, -1, 0, 0,

    0.5f, -0.5f, 0.5f, 0, 1, 0, 1, 0, 0,
    0.5f, -0.5f, -0.5f, 0, 1, 1, 1, 0, 0,
    0.5f, 0.5f, -0.5f, 0.2f, 0.8f, 1, 1, 0, 0,
    0.5f, 0.5f, 0.5f, 0, 0, 1, 1, 0, 0,

    -0.5f, 0.5f, 0.5f, 1, 1, 0, 0, 1, 0,
    0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 1, 0,
    0.5f, 0.5f, -0.5f, 0.2f, 0.8f, 1, 0, 1, 0,
    -0.5f, 0.5f, -0.5f, 1, 1, 1, 0, 1, 0,

    -0.5f, -0.5f, -0.5f, 1, 0, 1, 0, -1, 0,
    0.5f, -0.5f, -0.5f, 0, 1, 1, 0, -1, 0,
    0.5f, -0.5f, 0.5f, 0, 1, 0, 0, -1, 0,
    -0.5f, -0.5f, 0.5f, 1, 0, 0, 0, -1, 0};

std::vector<unsigned int> indices = {
    0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20};

std::vector<float> screenVertices = {
    -1, -1, 0, 0,
    1, -1, 1, 0,
    1, 1, 1, 1,
    -1, 1, 0, 1};

std::vector<unsigned int> screenIndices = {0, 1, 2, 2, 3, 0};

int main()
{
    constexpr uint32_t width = 720;
    constexpr uint32_t height = 480;

    Window win;
    win.title = "RGE - FBO RBO Test";
    win.width = width;
    win.height = height;

    OpenGlProfile profile;
    profile.version_major = 4;
    profile.version_minor = 6;

    RGE::BufferBit bufferBit{};
    bufferBit.color = true;
    bufferBit.depth = true;
    bufferBit.stencil = false;

    RGE::Color clearColor{0.1f, 0.2f, 0.3f, 1.0f};

    Windowing::Init();
    Windowing::SetOpenGlProfile(profile);
    Windowing::CreateWindow(win);
    Windowing::SetContext(win);

    RGE::Renderer::Init();
    RGE::Renderer::SetClearColor(clearColor);
    RGE::Renderer::SetRenderState(RGE::RenderState::DEPTH_TEST);
    RGE::Renderer::SetViewport(0, 0, width, height);

    // Cube pipeline
    RGE::Pipeline pipeline{};
    RGE::Renderer::CreatePipeline(pipeline, vertShader, fragShader);

    RGE::VertexArray vao{};
    RGE::Renderer::CreateVertexArray(vao);

    RGE::VertexBuffer vbo{};
    RGE::Renderer::CreateBuffer(vbo);
    RGE::Renderer::SetBufferData(vbo, vertices.size() * sizeof(float), vertices.data(), RGE::BufferUsage::STATIC_DRAW);

    RGE::IndexBuffer ibo{};
    ibo.count = static_cast<uint32_t>(indices.size());
    RGE::Renderer::CreateBuffer(ibo);
    RGE::Renderer::SetBufferData(ibo, indices.size() * sizeof(unsigned int), indices.data(), RGE::BufferUsage::STATIC_DRAW);

    RGE::VertexLayout layout{};
    RGE::VertexAttribute aPos{}, aColor{}, aNormal{};

    aPos.bindingIndex = 0;
    aPos.location = 0;
    aPos.size = 3;
    aPos.offset = 0;
    aPos.stride = 9 * sizeof(float);
    aPos.dataType = RGE::DataType::FLOAT;

    aColor.bindingIndex = 0;
    aColor.location = 1;
    aColor.size = 3;
    aColor.offset = 3 * sizeof(float);
    aColor.stride = 9 * sizeof(float);
    aColor.dataType = RGE::DataType::FLOAT;

    aNormal.bindingIndex = 0;
    aNormal.location = 2;
    aNormal.size = 3;
    aNormal.offset = 6 * sizeof(float);
    aNormal.stride = 9 * sizeof(float);
    aNormal.dataType = RGE::DataType::FLOAT;

    layout.attribute = {aPos, aColor, aNormal};
    RGE::Renderer::SetVertexLayout(vao, vbo, layout);
    RGE::Renderer::SetVertexIndex(vao, ibo);

    // FBO color attachment texture
    RGE::Texture colorTexture{};
    RGE::TextureDesc textureDesc{};
    textureDesc.type = RGE::TextureType::TEXTURE_2D;
    textureDesc.format = RGE::TextureFormat::RGBA8;
    textureDesc.width = width;
    textureDesc.height = height;
    textureDesc.depth = 1;
    textureDesc.levels = 1;
    textureDesc.minFilter = RGE::TextureFilter::LINEAR;
    textureDesc.magFilter = RGE::TextureFilter::LINEAR;
    textureDesc.wrapS = RGE::TextureWrap::CLAMP_TO_EDGE;
    textureDesc.wrapT = RGE::TextureWrap::CLAMP_TO_EDGE;
    RGE::Renderer::CreateTexture(colorTexture, textureDesc);

    // FBO depth attachment renderbuffer
    RGE::RenderBuffer depthBuffer{};
    RGE::RenderBufferDesc renderBufferDesc{};
    renderBufferDesc.format = RGE::RenderBufferFormat::DEPTH24;
    renderBufferDesc.width = width;
    renderBufferDesc.height = height;
    RGE::Renderer::CreateRenderbuffer(depthBuffer, renderBufferDesc);

    // Framebuffer setup
    RGE::FrameBuffer framebuffer{};
    RGE::Renderer::CreateFramebuffer(framebuffer);
    RGE::Renderer::AttachTexture(framebuffer, colorTexture, RGE::FrameBufferAttachment::COLOR0);
    RGE::Renderer::AttachRenderbuffer(framebuffer, depthBuffer, RGE::FrameBufferAttachment::DEPTH);
    RGE::Renderer::SetFramebufferDrawBuffers(framebuffer, {RGE::FrameBufferAttachment::COLOR0});

    if (!RGE::Renderer::CheckFramebuffer(framebuffer))
    {
        std::cerr << "FBO is incomplete!\n";
        RGE::Renderer::DestroyFramebuffer(framebuffer);
        RGE::Renderer::DestroyRenderbuffer(depthBuffer);
        RGE::Renderer::DestroyTexture(colorTexture);
        RGE::Renderer::DestroyVertexArray(vao);
        RGE::Renderer::DestroyBuffer(vbo);
        RGE::Renderer::DestroyBuffer(ibo);
        RGE::Renderer::DestroyPipeline(pipeline);
        Windowing::DestroyWindow(win);
        Windowing::Quit();
        return -1;
    }

    std::cout << "FBO is complete!\n";

    // Fullscreen quad pipeline
    RGE::Pipeline screenPipeline{};
    RGE::Renderer::CreatePipeline(screenPipeline, screenVertShader, screenFragShader);

    RGE::VertexArray screenVao{};
    RGE::Renderer::CreateVertexArray(screenVao);

    RGE::VertexBuffer screenVbo{};
    RGE::Renderer::CreateBuffer(screenVbo);
    RGE::Renderer::SetBufferData(screenVbo, screenVertices.size() * sizeof(float), screenVertices.data(), RGE::BufferUsage::STATIC_DRAW);

    RGE::IndexBuffer screenIbo{};
    screenIbo.count = static_cast<uint32_t>(screenIndices.size());
    RGE::Renderer::CreateBuffer(screenIbo);
    RGE::Renderer::SetBufferData(screenIbo, screenIndices.size() * sizeof(unsigned int), screenIndices.data(), RGE::BufferUsage::STATIC_DRAW);

    RGE::VertexLayout screenLayout{};
    RGE::VertexAttribute screenPos{}, screenUV{};

    screenPos.bindingIndex = 0;
    screenPos.location = 0;
    screenPos.size = 2;
    screenPos.offset = 0;
    screenPos.stride = 4 * sizeof(float);
    screenPos.dataType = RGE::DataType::FLOAT;

    screenUV.bindingIndex = 0;
    screenUV.location = 1;
    screenUV.size = 2;
    screenUV.offset = 2 * sizeof(float);
    screenUV.stride = 4 * sizeof(float);
    screenUV.dataType = RGE::DataType::FLOAT;

    screenLayout.attribute = {screenPos, screenUV};
    RGE::Renderer::SetVertexLayout(screenVao, screenVbo, screenLayout);
    RGE::Renderer::SetVertexIndex(screenVao, screenIbo);
    RGE::Renderer::SetUniformInt(screenPipeline, "screenTexture", 0);

    auto startTime = std::chrono::steady_clock::now();

    while (Windowing::WindowActive(win))
    {
        float time = std::chrono::duration<float>(std::chrono::steady_clock::now() - startTime).count();

        glm::vec3 viewPos(2.0f, 2.0f, 3.0f);
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0, 1, 0));
        model = glm::rotate(model, time * 0.5f, glm::vec3(1, 0, 0));
        glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0.0f), glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f, 100.0f);
        glm::vec3 lightPos(2.0f, 3.0f, 2.0f);

        // Pass 1: render cube into FBO
        RGE::Renderer::BindFramebuffer(framebuffer);
        RGE::Renderer::SetViewport(0, 0, width, height);
        RGE::Renderer::ClearBufferBit(bufferBit);
        RGE::Renderer::UsePipeline(pipeline);
        RGE::Renderer::SetUniformMat4(pipeline, "model", glm::value_ptr(model));
        RGE::Renderer::SetUniformMat4(pipeline, "view", glm::value_ptr(view));
        RGE::Renderer::SetUniformMat4(pipeline, "projection", glm::value_ptr(projection));
        RGE::Renderer::SetUniformVec3(pipeline, "lightPos", glm::value_ptr(lightPos));
        RGE::Renderer::SetUniformVec3(pipeline, "viewPos", glm::value_ptr(viewPos));
        RGE::Renderer::BindVertexArray(vao);
        RGE::Renderer::DrawIndexed(RGE::DrawMode::TRIANGLES, ibo);

        // Pass 2: display FBO color texture on the window
        RGE::Renderer::BindDefaultFramebuffer();
        RGE::Renderer::SetViewport(0, 0, width, height);
        RGE::Renderer::ClearBufferBit(bufferBit);
        RGE::Renderer::SetRenderState(RGE::RenderState::DEPTH_TEST);
        RGE::Renderer::UsePipeline(screenPipeline);
        RGE::Renderer::SetUniformTexture(screenPipeline, "screenTexture", colorTexture, 0);
        RGE::Renderer::BindVertexArray(screenVao);
        RGE::Renderer::DrawIndexed(RGE::DrawMode::TRIANGLES, screenIbo);

        Windowing::SwapBuffers(win);
        Windowing::PollEvent();
    }

    RGE::Renderer::DestroyVertexArray(screenVao);
    RGE::Renderer::DestroyBuffer(screenVbo);
    RGE::Renderer::DestroyBuffer(screenIbo);
    RGE::Renderer::DestroyPipeline(screenPipeline);

    RGE::Renderer::DestroyFramebuffer(framebuffer);
    RGE::Renderer::DestroyRenderbuffer(depthBuffer);
    RGE::Renderer::DestroyTexture(colorTexture);

    RGE::Renderer::DestroyVertexArray(vao);
    RGE::Renderer::DestroyBuffer(vbo);
    RGE::Renderer::DestroyBuffer(ibo);
    RGE::Renderer::DestroyPipeline(pipeline);

    Windowing::DestroyWindow(win);
    Windowing::Quit();
    return 0;
}

#include <iostream>
#include <vector>
#include "Renderer/Renderer.hpp"
#include "Windowing/Windowing.hpp"

std::string vertShader = R"(
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vColor = aColor;
}
)";

std::string fragShader = R"(
#version 460 core

in vec3 vColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}
)";

std::vector<float> vertices =
    {
        // Front
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,

        // Back
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.2f, 0.8f, 1.0f};

std::vector<unsigned int> indices =
    {
        0, 1, 2, 2, 3, 0,
        4, 6, 5, 6, 4, 7,
        4, 0, 3, 3, 7, 4,
        1, 5, 6, 6, 2, 1,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4};
int main()
{
    Window win;
    win.title = "REIN GAME ENGINE";
    win.width = 720;
    win.height = 480;
    OpenGlProfile profile;
    profile.version_major = 4;
    profile.version_minor = 6;

    RGE::BufferBit bufferBit;
    bufferBit.color = true;
    bufferBit.depth = true;
    bufferBit.stencil = false;

    RGE::Color clearColor;
    clearColor.r = 0.1f;
    clearColor.g = 0.2f;
    clearColor.b = 0.3f;
    clearColor.a = 1.0f;

    Windowing::Init();
    Windowing::SetOpenGlProfile(profile);
    Windowing::CreateWindow(win);
    Windowing::SetContext(win);

    RGE::Renderer::Init();
    RGE::Renderer::SetClearColor(clearColor);

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
    RGE::Renderer::SetBufferData(ibo, indices.size () * sizeof(unsigned int), indices.data(), RGE::BufferUsage::STATIC_DRAW);

    RGE::VertexLayout layout{};
    RGE::VertexAttribute aPos{};
    RGE::VertexAttribute aColor{};

    aPos.bindingIndex =0;
    aPos.location =0;
    aPos.size =3;
    aPos.offset =0;
    aPos.stride = 6 * sizeof(float);
    aPos.dataType = RGE::DataType::FLOAT;

    aColor.bindingIndex =0;
    aColor.location =1;
    aColor.size =3;
    aColor.offset = 3 * sizeof(float);
    aColor.stride = 6 * sizeof(float);
    aColor.dataType = RGE::DataType::FLOAT;

    layout.attribute = {aPos, aColor};

    RGE::Renderer::SetVertexLayout(vao, vbo, layout);
    RGE::Renderer::SetVertexIndex(vao, ibo);

    while (Windowing::WindowActive(win))
    {
        RGE::Renderer::ClearBufferBit(bufferBit);
        RGE::Renderer::UsePipeline(pipeline);
        RGE::Renderer::BindVertexArray(vao);
        RGE::Renderer::DrawIndexed(RGE::DrawMode::TRIANGLES, ibo);
        Windowing::SwapBuffers(win);
        Windowing::PollEvent();
    }
    Windowing::DestroyWindow(win);
    Windowing::Quit();
}

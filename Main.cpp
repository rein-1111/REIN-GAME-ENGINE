#include <iostream>
#include <vector>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Renderer.hpp"
#include "Windowing/Windowing.hpp"

std::string vertShader = R"(
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vColor;
out vec3 vNormal;
out vec3 vFragPos;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    vFragPos = worldPos.xyz;
    vNormal = mat3(transpose(inverse(model))) * aNormal;
    vColor = aColor;
    gl_Position = projection * view * worldPos;
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
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vFragPos);
    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec3 ambient = 0.15 * vColor;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vColor;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = vec3(0.5) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
)";

std::vector<float> vertices = {
    // Front
    -0.5f,-0.5f, 0.5f, 1,0,0, 0,0,1,
     0.5f,-0.5f, 0.5f, 0,1,0, 0,0,1,
     0.5f, 0.5f, 0.5f, 0,0,1, 0,0,1,
    -0.5f, 0.5f, 0.5f, 1,1,0, 0,0,1,

    // Back
     0.5f,-0.5f,-0.5f, 0,1,1, 0,0,-1,
    -0.5f,-0.5f,-0.5f, 1,0,1, 0,0,-1,
    -0.5f, 0.5f,-0.5f, 1,1,1, 0,0,-1,
     0.5f, 0.5f,-0.5f, 0.2f,0.8f,1, 0,0,-1,

    // Left
    -0.5f,-0.5f,-0.5f, 1,0,1, -1,0,0,
    -0.5f,-0.5f, 0.5f, 1,0,0, -1,0,0,
    -0.5f, 0.5f, 0.5f, 1,1,0, -1,0,0,
    -0.5f, 0.5f,-0.5f, 1,1,1, -1,0,0,

    // Right
     0.5f,-0.5f, 0.5f, 0,1,0, 1,0,0,
     0.5f,-0.5f,-0.5f, 0,1,1, 1,0,0,
     0.5f, 0.5f,-0.5f, 0.2f,0.8f,1, 1,0,0,
     0.5f, 0.5f, 0.5f, 0,0,1, 1,0,0,

    // Top
    -0.5f, 0.5f, 0.5f, 1,1,0, 0,1,0,
     0.5f, 0.5f, 0.5f, 0,0,1, 0,1,0,
     0.5f, 0.5f,-0.5f, 0.2f,0.8f,1, 0,1,0,
    -0.5f, 0.5f,-0.5f, 1,1,1, 0,1,0,

    // Bottom
    -0.5f,-0.5f,-0.5f, 1,0,1, 0,-1,0,
     0.5f,-0.5f,-0.5f, 0,1,1, 0,-1,0,
     0.5f,-0.5f, 0.5f, 0,1,0, 0,-1,0,
    -0.5f,-0.5f, 0.5f, 1,0,0, 0,-1,0
};

std::vector<unsigned int> indices = {
     0, 1, 2, 2, 3, 0,
     4, 5, 6, 6, 7, 4,
     8, 9,10,10,11, 8,
    12,13,14,14,15,12,
    16,17,18,18,19,16,
    20,21,22,22,23,20
};

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

    RGE::Renderer::SetRenderState(RGE::RenderState::DEPTH_TEST);

    RGE::Pipeline pipeline{};
    RGE::Renderer::CreatePipeline(pipeline, vertShader, fragShader);

    RGE::VertexArray vao{};
    RGE::Renderer::CreateVertexArray(vao);

    RGE::VertexBuffer vbo{};
    RGE::Renderer::CreateBuffer(vbo);
    RGE::Renderer::SetBufferData(
        vbo, vertices.size() * sizeof(float),
        vertices.data(), RGE::BufferUsage::STATIC_DRAW
    );

    RGE::IndexBuffer ibo{};
    ibo.count = static_cast<uint32_t>(indices.size());
    RGE::Renderer::CreateBuffer(ibo);
    RGE::Renderer::SetBufferData(
        ibo, indices.size() * sizeof(unsigned int),
        indices.data(), RGE::BufferUsage::STATIC_DRAW
    );

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

    auto startTime = std::chrono::steady_clock::now();

    while (Windowing::WindowActive(win))
    {
        float time = std::chrono::duration<float>(
            std::chrono::steady_clock::now() - startTime
        ).count();

        glm::vec3 viewPos(2.0f, 2.0f, 3.0f);

        glm::mat4 model = glm::rotate(
            glm::mat4(1.0f), time, glm::vec3(0, 1, 0)
        );
        model = glm::rotate(
            model, time * 0.5f, glm::vec3(1, 0, 0)
        );

        glm::mat4 view = glm::lookAt(
            viewPos, glm::vec3(0.0f), glm::vec3(0, 1, 0)
        );

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f), 720.0f / 480.0f, 0.1f, 100.0f
        );

        RGE::Renderer::ClearBufferBit(bufferBit);
        RGE::Renderer::UsePipeline(pipeline);

        RGE::Renderer::SetUniformMat4(
            pipeline, "model", glm::value_ptr(model)
        );
        RGE::Renderer::SetUniformMat4(
            pipeline, "view", glm::value_ptr(view)
        );
        RGE::Renderer::SetUniformMat4(
            pipeline, "projection", glm::value_ptr(projection)
        );

        glm::vec3 lightPos(2.0f, 3.0f, 2.0f);

        RGE::Renderer::SetUniformVec3(
            pipeline, "lightPos", glm::value_ptr(lightPos)
        );
        RGE::Renderer::SetUniformVec3(
            pipeline, "viewPos", glm::value_ptr(viewPos)
        );

        RGE::Renderer::BindVertexArray(vao);
        RGE::Renderer::DrawIndexed(RGE::DrawMode::TRIANGLES, ibo);

        Windowing::SwapBuffers(win);
        Windowing::PollEvent();
    }

    Windowing::DestroyWindow(win);
    Windowing::Quit();

    return 0;
}
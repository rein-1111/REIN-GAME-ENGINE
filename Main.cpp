#include <iostream>
#include <vector>
#include "Windowing/Windowing.hpp"
#include "Renderer/Renderer.hpp"

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

    Windowing::Init();
    Windowing::SetOpenGlProfile(profile);
    Windowing::CreateWindow(win);
    Windowing::SetContext(win);

    RGE::ShaderHandle shaderHandle;
    RGE::ShaderSource shaderSource;
    shaderSource.vertSource = vertShader;
    shaderSource.fragSource = fragShader;

    RGE::VertexAttribute aPos;
    aPos.index = 0;
    aPos.size = 3;
    aPos.relative = 0;

    RGE::VertexAttribute aColor;
    aColor.index = 1;
    aColor.size = 3;
    aColor.relative = 3;

    RGE::VertexLayout layout;
    layout.index = 0;
    layout.offset = 0;
    layout.stride = 6;
    layout.attributes = {aPos, aColor};

    RGE::Color clearColor;
    clearColor.r = 0.1f;
    clearColor.g = 0.2f;
    clearColor.b = 0.3f;
    clearColor.a = 1.0f;

    RGE::MeshHandle meshHandle;
    RGE::MeshSource meshSource;
    meshSource.vertices = vertices;
    meshSource.indices = indices;
    meshSource.layout = layout;

    RGE::DepthStencilParams bufferParams;
    bufferParams.depthTest = true;
    bufferParams.stencilTest = false;

    RGE::ClearParams Clear;
    Clear.color = true;
    Clear.depth = true;
    Clear.stencil = false;

    RGE::Renderer::backend = RGE::Backend::OpenGl;
    RGE::Renderer::Init();
    RGE::Renderer::SetDepthStencil(bufferParams);
    RGE::Renderer::SetClearColor(clearColor);
    RGE::Renderer::CreateShader(shaderHandle, shaderSource);
    RGE::Renderer::CreateMesh(meshHandle, meshSource);
    RGE::Renderer::UseShader(shaderHandle);
    RGE::Renderer::BindMesh(meshHandle);
    while (Windowing::WindowActive(win))
    {
        RGE::Renderer::Clear(Clear);

        RGE::Renderer::DrawMesh(meshHandle);
        Windowing::SwapBuffers(win);
        Windowing::PollEvent();
    }
    RGE::Renderer::UnbindMesh();
    RGE::Renderer::DestroyShader(shaderHandle);
    Windowing::DestroyWindow(win);
    Windowing::Quit();
}

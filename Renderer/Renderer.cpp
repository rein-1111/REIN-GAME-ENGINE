#include "Renderer.hpp"
#include "Backend/OpenGlRenderer.hpp"

namespace RGE
{
    void Renderer::Init()
    {
        if (backend == Backend::OpenGl)
        {
            renderer = std::make_unique<OpenGlRenderer>();
            renderer->Init();
        }
    }

    void Renderer::SetClearColor(Color &color)
    {
        renderer->SetClearColor(color);
    }

    void Renderer::SetDepthStencil(DepthStencilParams &params)
    {
        renderer->SetDepthStencil(params);
    }

    void Renderer::Clear(ClearParams &params)
    {
        renderer->Clear(params);
    }

    void Renderer::CreateShader(ShaderHandle &handle, ShaderSource &source)
    {
        renderer->CreateShader(handle, source);
    }

    void Renderer::DestroyShader(ShaderHandle &handle)
    {
        renderer->DestroyShader(handle);
    }

    void Renderer::UseShader(ShaderHandle &shaderHandle)
    {
        renderer->UseShader(shaderHandle);
    }

    void Renderer::CreateMesh(MeshHandle &handle, MeshSource &source)
    {
        renderer->CreateMesh(handle, source);
    }

    void Renderer::DestroyMesh(MeshHandle &handle)
    {
        renderer->DestroyMesh(handle);
    }

    void Renderer::BindMesh(MeshHandle &handle)
    {
        renderer->BindMesh(handle);
    }

    void Renderer::UnbindMesh()
    {
        renderer->UnbindMesh();
    }

    void Renderer::DrawMesh(MeshHandle &meshHandle)
    {
        renderer->DrawMesh(meshHandle);
    }

    void Renderer::CreateTexture2D(TextureHandle &textureHandle, TextureSource &textureSource)
    {
        renderer->CreateTexture2D(textureHandle, textureSource);
    }
    
    void Renderer::SetTexture2DFilter(TextureHandle &textureHandle, Texture2DFilter &texture2DFilter){
        renderer->SetTexture2DFilter(textureHandle, texture2DFilter);
    }

    void Renderer::SetTexture2DWrap(TextureHandle &textureHandle, Texture2DWrap &texture2DWrap){
        renderer->SetTexture2DWrap(textureHandle, texture2DWrap);
    }

    void Renderer::DestroyTexture2D(TextureHandle &textureHandle)
    {
        renderer->DestroyTexture2D(textureHandle);
    }

    void Renderer::BindTexture(TextureHandle &textureHandle, uint32_t unit)
    {
        renderer->BindTexture(textureHandle, unit);
    }

    void Renderer::UnbindTexture(uint32_t unit)
    {
        renderer->UnbindTexture(unit);
    }

    void Renderer::GenerateTextureMipmap(TextureHandle &textureHandle){
        renderer->GenerateTextureMipmap(textureHandle);
    }
}
#pragma once

#include "IRenderer.hpp"
#include "Backend/OpenGlRenderer.hpp"

namespace RGE
{
    enum class Backend
    {
        OpenGl,
        Dawn,
    };
    class Renderer
    {
    private:
        inline static IRenderer *renderer;

    public:
        inline static Backend backend = Backend::OpenGl;

        static bool Init();

        static void SetClearColor(Color &color);
        static void ClearBufferBit(BufferBit &bufferBit);
        static void SetRenderState(RenderState renderState);

        static void CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource);
        static void UsePipeline(Pipeline &pipeline);

        static void CreateVertexArray(VertexArray &vertexArray);
        static void CreateBuffer(VertexBuffer &vertexBuffer);
        static void CreateBuffer(IndexBuffer &indexBuffer);
        static void CreateBuffer(UniformBuffer &uniformBuffer);
        static void SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage);
        static void SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage);
        static void SetBufferData(UniformBuffer &uniformBuffer, size_t size, const void *data, BufferUsage bufferUsage);
        static void SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout);
        static void SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer);
        static void BindVertexArray(VertexArray &vertexArray);
        static void Draw(DrawMode drawMode, uint32_t count);
        static void DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer);

        static void BindUniformBuffer(Pipeline &pipeline, UniformBuffer &uniformBuffer, const std::string &name, uint32_t binding);

        static void DestroyVertexArray(VertexArray &vertexArray);
        static void DestroyBuffer(VertexBuffer &vertexBuffer);
        static void DestroyBuffer(IndexBuffer &indexBuffer);
        static void DestroyBuffer(UniformBuffer &uniformBuffer);
        static void DestroyPipeline(Pipeline &pipeline);

        static void CreateTexture(Texture &texture, TextureDesc &desc);
        static void SetTextureData(Texture &texture, TextureType textureType, uint32_t mipLevel, uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint16_t depth, TextureFormat format, const void *data);
        static void GenerateTextureMipmap(Texture &texture);
        static void BindTexture(Texture &texture, uint32_t unit);
        static void DestroyTexture(Texture &texture);

        static void SetUniformInt(Pipeline &pipeline, const std::string &name, int value);
        static void SetUniformFloat(Pipeline &pipeline, const std::string &name, float value);
        static void SetUniformVec2(Pipeline &pipeline, const std::string &name, const float *value);
        static void SetUniformVec3(Pipeline &pipeline, const std::string &name, const float *value);
        static void SetUniformVec4(Pipeline &pipeline, const std::string &name, const float *value);
        static void SetUniformMat3(Pipeline &pipeline, const std::string &name, const float *value);
        static void SetUniformMat4(Pipeline &pipeline, const std::string &name, const float *value);
        static void SetUniformTexture(Pipeline &pipeline, const std::string &name, Texture &texture, uint32_t unit);

        static void CreateRenderbuffer(RenderBuffer &renderBuffer, RenderBufferDesc &desc);
        static void ResizeRenderbuffer(RenderBuffer &renderBuffer, uint32_t width, uint32_t height);
        static void DestroyRenderbuffer(RenderBuffer &renderBuffer);
    };

    inline bool Renderer::Init()
    {
        if (backend == Backend::OpenGl)
        {
            renderer = new OpenGlRenderer;
            return renderer->Init();
        }
        return false;
    }

    inline void Renderer::SetClearColor(Color &color)
    {
        renderer->SetClearColor(color);
    }
    inline void Renderer::ClearBufferBit(BufferBit &bufferBit)
    {
        renderer->ClearBufferBit(bufferBit);
    }
    inline void Renderer::SetRenderState(RenderState renderState)
    {
        renderer->SetRenderState(renderState);
    }
    inline void Renderer::CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource)
    {
        renderer->CreatePipeline(pipeline, vertSource, fragSource);
    }
    inline void Renderer::UsePipeline(Pipeline &pipeline)
    {
        renderer->UsePipeline(pipeline);
    }
    inline void Renderer::CreateVertexArray(VertexArray &vertexArray)
    {
        renderer->CreateVertexArray(vertexArray);
    }
    inline void Renderer::CreateBuffer(VertexBuffer &vertexBuffer)
    {
        renderer->CreateBuffer(vertexBuffer);
    }
    inline void Renderer::CreateBuffer(IndexBuffer &indexBuffer)
    {
        renderer->CreateBuffer(indexBuffer);
    }
    inline void Renderer::SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage)
    {
        renderer->SetBufferData(vertexBuffer, size, data, bufferUsage);
    }
    inline void Renderer::SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage)
    {
        renderer->SetBufferData(indexBuffer, size, data, bufferUsage);
    }
    inline void Renderer::SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout)
    {
        renderer->SetVertexLayout(vertexArray, vertexBuffer, vertexLayout);
    }
    inline void Renderer::SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer)
    {
        renderer->SetVertexIndex(vertexArray, indexBuffer);
    }
    inline void Renderer::BindVertexArray(VertexArray &vertexArray)
    {
        renderer->BindVertexArray(vertexArray);
    }
    inline void Renderer::Draw(DrawMode drawMode, uint32_t count)
    {
        renderer->Draw(drawMode, count);
    }
    inline void Renderer::DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer)
    {
        renderer->DrawIndexed(drawMode, indexBuffer);
    }
    inline void Renderer::BindUniformBuffer(Pipeline &pipeline, UniformBuffer &uniformBuffer, const std::string &name, uint32_t binding)
    {
        renderer->BindUniformBuffer(pipeline, uniformBuffer, name, binding);
    }
    inline void Renderer::DestroyVertexArray(VertexArray &vertexArray)
    {
        renderer->DestroyVertexArray(vertexArray);
    }
    inline void Renderer::DestroyBuffer(VertexBuffer &vertexBuffer)
    {
        renderer->DestroyBuffer(vertexBuffer);
    }
    inline void Renderer::DestroyBuffer(IndexBuffer &indexBuffer)
    {
        renderer->DestroyBuffer(indexBuffer);
    }
    inline void Renderer::DestroyBuffer(UniformBuffer &uniformBuffer)
    {
        renderer->DestroyBuffer(uniformBuffer);
    }
    inline void Renderer::DestroyPipeline(Pipeline &pipeline)
    {
        renderer->DestroyPipeline(pipeline);
    }
    inline void Renderer::CreateTexture(Texture &texture, TextureDesc &desc)
    {
        renderer->CreateTexture(texture, desc);
    }
    inline void Renderer::SetTextureData(Texture &texture, TextureType textureType, uint32_t mipLevel, uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint16_t depth, TextureFormat format, const void *data)
    {
        renderer->SetTextureData(texture, textureType, mipLevel, x, y, z, width, height, depth, format, data);
    }
    inline void Renderer::GenerateTextureMipmap(Texture &texture)
    {
        renderer->GenerateTextureMipmap(texture);
    }
    inline void Renderer::BindTexture(Texture &texture, uint32_t unit)
    {
        renderer->BindTexture(texture, unit);
    }
    inline void Renderer::DestroyTexture(Texture &texture)
    {
        renderer->DestroyTexture(texture);
    }
    inline void Renderer::SetUniformInt(Pipeline &pipeline, const std::string &name, int value)
    {
        renderer->SetUniformInt(pipeline, name, value);
    }
    inline void Renderer::SetUniformFloat(Pipeline &pipeline, const std::string &name, float value)
    {
        renderer->SetUniformFloat(pipeline, name, value);
    }
    inline void Renderer::SetUniformVec2(Pipeline &pipeline, const std::string &name, const float *value)
    {
        renderer->SetUniformVec2(pipeline, name, value);
    }
    inline void Renderer::SetUniformVec3(Pipeline &pipeline, const std::string &name, const float *value)
    {
        renderer->SetUniformVec3(pipeline, name, value);
    }
    inline void Renderer::SetUniformVec4(Pipeline &pipeline, const std::string &name, const float *value)
    {
        renderer->SetUniformVec4(pipeline, name, value);
    }
    inline void Renderer::SetUniformMat3(Pipeline &pipeline, const std::string &name, const float *value)
    {
        renderer->SetUniformMat3(pipeline, name, value);
    }
    inline void Renderer::SetUniformMat4(Pipeline &pipeline, const std::string &name, const float *value)
    {
        renderer->SetUniformMat4(pipeline, name, value);
    }
    inline void Renderer::SetUniformTexture(Pipeline &pipeline, const std::string &name, Texture &texture, uint32_t unit)
    {
        renderer->SetUniformTexture(pipeline, name, texture, unit);
    }
    inline void Renderer::CreateRenderbuffer(RenderBuffer &renderBuffer, RenderBufferDesc &desc)
    {
        renderer->CreateRenderbuffer(renderBuffer, desc);
    }
    inline void Renderer::ResizeRenderbuffer(RenderBuffer &renderBuffer, uint32_t width, uint32_t height)
    {
        renderer->ResizeRenderbuffer(renderBuffer, width, height);
    }
    inline void Renderer::DestroyRenderbuffer(RenderBuffer &renderBuffer)
    {
        renderer->DestroyRenderbuffer(renderBuffer);
    }
}
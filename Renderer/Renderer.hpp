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

        static void CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource);
        static void UsePipeline(Pipeline &pipeline);

        static void CreateVertexArray(VertexArray &vertexArray);
        static void CreateBuffer(VertexBuffer &vertexBuffer);
        static void CreateBuffer(IndexBuffer &indexBuffer);
        static void SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage);
        static void SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage);
        static void SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout);
        static void SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer);
        static void BindVertexArray(VertexArray &vertexArray);
        static void Draw(DrawMode drawMode, uint32_t count);
        static void DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer);
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
        renderer->SetVertexLayout(vertexArray,vertexBuffer, vertexLayout);
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
}
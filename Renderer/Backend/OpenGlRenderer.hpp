#pragma once
#include "../IRenderer.hpp"
#include "wrapper/OpenGl.hpp"
#include <map>

namespace RGE
{
    class OpenGlRenderer : public IRenderer
    {
        struct Program
        {
            unsigned int program;
        };
        struct VertexArrayObject
        {
            unsigned int vertexArray;
        };
        struct VertexBufferObject
        {
            unsigned int vertexBuffer;
        };
        struct IndexBufferObject
        {
            unsigned int indexBuffer;
        };

    private:
        std::map<Pipeline, Program> programStorage;
        uint32_t nextProgramId = 0;
        std::map<VertexArray, VertexArrayObject> VAOStorage;
        uint32_t VAONextId = 0;
        std::map<VertexBuffer, VertexBufferObject> VBOStorage;
        uint32_t VBONextId = 0;
        std::map<IndexBuffer, IndexBufferObject> IBOStorage;
        uint32_t IBONextId = 0;

    public:
        bool Init() override;
        void SetClearColor(Color &color) override;
        void ClearBufferBit(BufferBit &bufferBit) override;

        void CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource) override;
        void UsePipeline(Pipeline &pipeline);

        void CreateVertexArray(VertexArray &vertexArray) override;
        void CreateBuffer(VertexBuffer &vertexBuffer) override;
        void CreateBuffer(IndexBuffer &indexBuffer) override;
        void SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage) override;
        void SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage) override;
        void SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout) override;
        void SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer) override;
        void BindVertexArray(VertexArray &vertexArray) override;
        void Draw(DrawMode drawMode, uint32_t count) override;
        void DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer) override;
    };

    inline bool OpenGlRenderer::Init()
    {
        return OpenGlWrapper::OpenGl::Init();
    }

    inline void OpenGlRenderer::SetClearColor(Color &color)
    {
        OpenGlWrapper::OpenGl::SetClearColor(color.r, color.g, color.b, color.a);
    }
    inline void OpenGlRenderer::ClearBufferBit(BufferBit &bufferBit)
    {
        int mask = 0;

        if (bufferBit.color)
            mask |= GL_COLOR_BUFFER_BIT;
        if (bufferBit.depth)
            mask |= GL_DEPTH_BUFFER_BIT;
        if (bufferBit.stencil)
            mask |= GL_STENCIL_BUFFER_BIT;

        if (mask != 0)
            OpenGlWrapper::OpenGl::ClearBufferBit(mask);
    }
    inline void OpenGlRenderer::CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource)
    {
        OpenGlWrapper::OpenGl::CreateShader(pipeline.shader.vertexShader, vertSource.c_str(), GL_VERTEX_SHADER);
        OpenGlWrapper::OpenGl::CreateShader(pipeline.shader.fragmentShader, fragSource.c_str(), GL_FRAGMENT_SHADER);
        OpenGlWrapper::OpenGl::CompileShader(pipeline.shader.vertexShader);
        OpenGlWrapper::OpenGl::CompileShader(pipeline.shader.fragmentShader);
        Program program;
        OpenGlWrapper::OpenGl::CreateProgram(program.program, pipeline.shader.vertexShader, pipeline.shader.fragmentShader);
        OpenGlWrapper::OpenGl::DeleteShader(pipeline.shader.vertexShader);
        OpenGlWrapper::OpenGl::DeleteShader(pipeline.shader.fragmentShader);

        pipeline.handle = nextProgramId++;
        programStorage.emplace(pipeline, program);
    }

    inline void OpenGlRenderer::UsePipeline(Pipeline &pipeline)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        OpenGlWrapper::OpenGl::UseProgram(it->second.program);
    }

    inline void OpenGlRenderer::CreateVertexArray(VertexArray &vertexArray)
    {
        VertexArrayObject vao;
        OpenGlWrapper::OpenGl::CreateVertexArray(vao.vertexArray);
        vertexArray.handle = VAONextId++;

        VAOStorage.emplace(vertexArray, vao);
    }
    inline void OpenGlRenderer::CreateBuffer(VertexBuffer &vertexBuffer)
    {
        VertexBufferObject vbo;
        OpenGlWrapper::OpenGl::CreateBuffer(vbo.vertexBuffer);
        vertexBuffer.handle = VBONextId++;
        VBOStorage.emplace(vertexBuffer, vbo);
    }
    inline void OpenGlRenderer::CreateBuffer(IndexBuffer &indexBuffer)
    {
        IndexBufferObject ibo;
        OpenGlWrapper::OpenGl::CreateBuffer(ibo.indexBuffer);
        indexBuffer.handle = IBONextId++;
        IBOStorage.emplace(indexBuffer, ibo);
    }
    inline void OpenGlRenderer::SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage)
    {
        auto it = VBOStorage.find(vertexBuffer);
        if (it == VBOStorage.end())
            return;

        int mask = 0;
        if (bufferUsage == BufferUsage::STATIC_DRAW)
            mask = GL_STATIC_DRAW;
        if (bufferUsage == BufferUsage::STATIC_READ)
            mask = GL_STATIC_READ;
        if (bufferUsage == BufferUsage::STATIC_COPY)
            mask = GL_STATIC_COPY;
        if (bufferUsage == BufferUsage::DYNAMIC_DRAW)
            mask = GL_DYNAMIC_DRAW;
        if (bufferUsage == BufferUsage::DYNAMIC_READ)
            mask = GL_DYNAMIC_READ;
        if (bufferUsage == BufferUsage::DYNAMIC_COPY)
            mask = GL_DYNAMIC_COPY;
        if (bufferUsage == BufferUsage::STREAM_DRAW)
            mask = GL_STREAM_DRAW;
        if (bufferUsage == BufferUsage::STREAM_READ)
            mask = GL_STREAM_READ;
        if (bufferUsage == BufferUsage::STREAM_COPY)
            mask = GL_STREAM_COPY;

        OpenGlWrapper::OpenGl::SetBufferData(it->second.vertexBuffer, size, data, mask);
    }
    inline void OpenGlRenderer::SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage)
    {
        auto it = IBOStorage.find(indexBuffer);
        if (it == IBOStorage.end())
            return;

        int mask = 0;
        if (bufferUsage == BufferUsage::STATIC_DRAW)
            mask = GL_STATIC_DRAW;
        if (bufferUsage == BufferUsage::STATIC_READ)
            mask = GL_STATIC_READ;
        if (bufferUsage == BufferUsage::STATIC_COPY)
            mask = GL_STATIC_COPY;
        if (bufferUsage == BufferUsage::DYNAMIC_DRAW)
            mask = GL_DYNAMIC_DRAW;
        if (bufferUsage == BufferUsage::DYNAMIC_READ)
            mask = GL_DYNAMIC_READ;
        if (bufferUsage == BufferUsage::DYNAMIC_COPY)
            mask = GL_DYNAMIC_COPY;
        if (bufferUsage == BufferUsage::STREAM_DRAW)
            mask = GL_STREAM_DRAW;
        if (bufferUsage == BufferUsage::STREAM_READ)
            mask = GL_STREAM_READ;
        if (bufferUsage == BufferUsage::STREAM_COPY)
            mask = GL_STREAM_COPY;

        OpenGlWrapper::OpenGl::SetBufferData(it->second.indexBuffer, size, data, mask);
    }

    inline void OpenGlRenderer::SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout)
    {
        auto it_vao = VAOStorage.find(vertexArray);
        auto it_vbo = VBOStorage.find(vertexBuffer);
        if (it_vao == VAOStorage.end() || it_vbo == VBOStorage.end())
            return;

        for (auto vertexAttribute : vertexLayout.attribute)
        {
            int mask = 0;
            if (vertexAttribute.dataType == DataType::INT)
                mask = GL_INT;
            if (vertexAttribute.dataType == DataType::FLOAT)
                mask = GL_FLOAT;

            OpenGlWrapper::OpenGl::SetVertexLayout(it_vao->second.vertexArray, it_vbo->second.vertexBuffer, vertexAttribute.bindingIndex, vertexAttribute.location, vertexAttribute.size, vertexAttribute.offset, vertexAttribute.stride, mask);
        }
    }
    inline void OpenGlRenderer::SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer)
    {
        auto it_vao = VAOStorage.find(vertexArray);
        auto it_ibo = IBOStorage.find(indexBuffer);
        if (it_vao == VAOStorage.end() || it_ibo == IBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::SetVertexArrayIndexBuffer(it_vao->second.vertexArray, it_ibo->second.indexBuffer);
    }
    inline void OpenGlRenderer::BindVertexArray(VertexArray &vertexArray)
    {
        auto it = VAOStorage.find(vertexArray);
        if (it == VAOStorage.end())
            return;

        OpenGlWrapper::OpenGl::BindVertexArray(it->second.vertexArray);
    }
    inline void OpenGlRenderer::Draw(DrawMode drawMode, uint32_t count)
    {
        int mask = 0;
        if (drawMode == DrawMode::POINTS)
            mask = GL_POINTS;
        if (drawMode == DrawMode::LINES)
            mask = GL_LINES;
        if (drawMode == DrawMode::LINE_STRIP)
            mask = GL_LINE_STRIP;
        if (drawMode == DrawMode::LINE_LOOP)
            mask = GL_LINE_LOOP;
        if (drawMode == DrawMode::TRIANGLES)
            mask = GL_TRIANGLES;
        if (drawMode == DrawMode::TRIANGLE_STRIP)
            mask = GL_TRIANGLE_STRIP;
        if (drawMode == DrawMode::TRIANGLE_FAN)
            mask = GL_TRIANGLE_FAN;

        OpenGlWrapper::OpenGl::Draw(mask, count);
    }
    inline void OpenGlRenderer::DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer)
    {
        auto it = IBOStorage.find(indexBuffer);
        if (it == IBOStorage.end())
            return;

        int mask = 0;
        if (drawMode == DrawMode::POINTS)
            mask = GL_POINTS;
        if (drawMode == DrawMode::LINES)
            mask = GL_LINES;
        if (drawMode == DrawMode::LINE_STRIP)
            mask = GL_LINE_STRIP;
        if (drawMode == DrawMode::LINE_LOOP)
            mask = GL_LINE_LOOP;
        if (drawMode == DrawMode::TRIANGLES)
            mask = GL_TRIANGLES;
        if (drawMode == DrawMode::TRIANGLE_STRIP)
            mask = GL_TRIANGLE_STRIP;
        if (drawMode == DrawMode::TRIANGLE_FAN)
            mask = GL_TRIANGLE_FAN;
        OpenGlWrapper::OpenGl::DrawIndexed(mask, GL_UNSIGNED_INT, nullptr, indexBuffer.count);
    }

}
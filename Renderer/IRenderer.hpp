#pragma once
#include <iostream>
#include <vector>

namespace RGE
{
    enum class DataType
    {
        INT,
        FLOAT
    };
    enum class BufferUsage
    {
        STATIC_DRAW,
        STATIC_READ,
        STATIC_COPY,
        DYNAMIC_DRAW,
        DYNAMIC_READ,
        DYNAMIC_COPY,
        STREAM_DRAW,
        STREAM_READ,
        STREAM_COPY,
    };
    enum class DrawMode
    {
        POINTS,
        LINES,
        LINE_STRIP,
        LINE_LOOP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };
    struct Color
    {
        float r;
        float g;
        float b;
        float a;
    };
    struct BufferBit
    {
        bool color;
        bool depth;
        bool stencil;
    };
    struct Shader
    {
        unsigned int vertexShader;
        unsigned int fragmentShader;
    };
    struct Pipeline
    {
        uint32_t handle;
        Shader shader;

        bool const operator<(const Pipeline &other) const
        {
            return handle < other.handle;
        }
    };
    struct VertexAttribute
    {
        uint32_t bindingIndex;
        uint32_t location;
        uint32_t size;
        uint16_t offset;
        uint32_t stride;
        DataType dataType;
    };
    struct VertexLayout
    {
        std::vector<VertexAttribute> attribute;
    };
    struct VertexArray
    {
        uint32_t handle;

        bool const operator<(const VertexArray &other) const
        {
            return handle < other.handle;
        }
    };
    struct VertexBuffer
    {
        uint32_t handle;

        bool const operator<(const VertexBuffer &other) const
        {
            return handle < other.handle;
        }
    };
    struct IndexBuffer
    {
        uint32_t handle;
        uint32_t count;

        bool const operator<(const IndexBuffer &other) const
        {
            return handle < other.handle;
        }
    };
    class IRenderer
    {
    public:
        virtual bool Init() = 0;
        virtual void SetClearColor(Color &color) = 0;
        virtual void ClearBufferBit(BufferBit &bufferBit) = 0;

        virtual void CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource) = 0;
        virtual void UsePipeline(Pipeline &pipeline) = 0;

        virtual void CreateVertexArray(VertexArray &vertexArray) = 0;
        virtual void CreateBuffer(VertexBuffer &vertexBuffer) = 0;
        virtual void CreateBuffer(IndexBuffer &indexBuffer) = 0;
        virtual void SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage) = 0;
        virtual void SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage) = 0;
        virtual void SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout) = 0;
        virtual void SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer) = 0;
        virtual void BindVertexArray(VertexArray &vertexArray) = 0;
        virtual void Draw(DrawMode drawMode, uint32_t count) = 0;
        virtual void DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer) = 0;
    };
}
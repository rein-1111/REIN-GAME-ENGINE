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
    enum class TextureType
    {
        TEXTURE_2D,
        TEXTURE_3D
    };
    enum class TextureFormat
    {
        R8,
        RG8,
        RGB8,
        RGBA8,
        R16F,
        RG16F,
        RGB16F,
        RGBA16F,
        DEPTH24,
        DEPTH24_STENCIL8
    };
    enum class TextureFilter
    {
        NEAREST,
        LINEAR,
        NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_LINEAR
    };
    enum class TextureWrap
    {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER
    };
    enum class PixelFormat
    {
        RED,
        RG,
        RGB,
        RGBA,
        DEPTH,
        DEPTH_STENCIL
    };
    enum class PixelType
    {
        UNSIGNED_BYTE,
        BYTE,
        UNSIGNED_SHORT,
        SHORT,
        UNSIGNED_INT,
        INT,
        HALF_FLOAT,
        FLOAT,
        UNSIGNED_INT_24_8
    };
    enum class RenderState
    {
        BLEND,
        CULL_FACE,
        DEPTH_TEST,
        SCISSOR_TEST,
        STENCIL_TEST,
        MULTISAMPLE,
        FRAMEBUFFER_SRGB,
        RASTERIZER_DISCARD
    };
    enum class RenderBufferFormat
    {
        DEPTH24,
        DEPTH24_STENCIL8,
        STENCIL8,
        RGBA8
    };
    enum class FrameBufferAttachment{
        COLOR0,
        COLOR1,
        COLOR2,
        COLOR3,
        DEPTH,
        STENCIL,
        DEPTH_STENCIL,
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
    struct UniformBuffer
    {
        uint32_t handle;

        bool const operator<(const UniformBuffer &other) const
        {
            return handle < other.handle;
        }
    };
    struct Texture
    {
        uint32_t handle;

        bool const operator<(const Texture &other) const
        {
            return handle < other.handle;
        }
    };
    struct TextureDesc
    {
        TextureType type;
        TextureFormat format;
        uint32_t width = 1;
        uint32_t height = 1;
        uint32_t depth = 1;
        uint32_t levels = 1;
        TextureFilter minFilter = TextureFilter::LINEAR;
        TextureFilter magFilter = TextureFilter::LINEAR;
        TextureWrap wrapS = TextureWrap::REPEAT;
        TextureWrap wrapT = TextureWrap::REPEAT;
        TextureWrap wrapR = TextureWrap::REPEAT;
    };
    struct RenderBuffer
    {
        uint32_t handle;

        bool const operator<(const RenderBuffer &other) const
        {
            return handle < other.handle;
        }
    };
    struct RenderBufferDesc
    {
        RenderBufferFormat format;
        uint32_t width;
        uint32_t height;
    };
    struct FrameBuffer{
        uint32_t handle;

        bool const operator<(const FrameBuffer&other) const{
            return handle < other.handle;
        }
    };
    struct FrameBufferDesc{
        uint32_t width;
        uint32_t height;
    };
    class IRenderer
    {
    public:
        virtual bool Init() = 0;
        virtual void SetClearColor(Color &color) = 0;
        virtual void ClearBufferBit(BufferBit &bufferBit) = 0;
        virtual void SetRenderState(RenderState renderState) = 0;

        virtual void CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource) = 0;
        virtual void UsePipeline(Pipeline &pipeline) = 0;

        virtual void CreateVertexArray(VertexArray &vertexArray) = 0;
        virtual void CreateBuffer(VertexBuffer &vertexBuffer) = 0;
        virtual void CreateBuffer(IndexBuffer &indexBuffer) = 0;
        virtual void CreateBuffer(UniformBuffer &uniformBuffer) = 0;
        virtual void SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage) = 0;
        virtual void SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage) = 0;
        virtual void SetBufferData(UniformBuffer &uniformBuffer, size_t size, const void *data, BufferUsage bufferUsage) = 0;
        virtual void SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout) = 0;
        virtual void SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer) = 0;
        virtual void BindVertexArray(VertexArray &vertexArray) = 0;
        virtual void Draw(DrawMode drawMode, uint32_t count) = 0;
        virtual void DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer) = 0;

        virtual void BindUniformBuffer(Pipeline &pipeline, UniformBuffer &uniformBuffer, const std::string &name, uint32_t binding) = 0;

        virtual void DestroyVertexArray(VertexArray &vertexArray) = 0;
        virtual void DestroyBuffer(VertexBuffer &vertexBuffer) = 0;
        virtual void DestroyBuffer(IndexBuffer &indexBuffer) = 0;
        virtual void DestroyBuffer(UniformBuffer &uniformBuffer) = 0;
        virtual void DestroyPipeline(Pipeline &pipeline) = 0;

        virtual void CreateTexture(Texture &texture, TextureDesc &desc) = 0;
        virtual void SetTextureData(Texture &texture, TextureType textureType, uint32_t mipLevel, uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint16_t depth, TextureFormat format, const void *data) = 0;
        virtual void GenerateTextureMipmap(Texture &texture) = 0;
        virtual void BindTexture(Texture &texture, uint32_t unit) = 0;
        virtual void DestroyTexture(Texture &texture) = 0;

        virtual void SetUniformInt(Pipeline &pipeline, const std::string &name, int value) = 0;
        virtual void SetUniformFloat(Pipeline &pipeline, const std::string &name, float value) = 0;
        virtual void SetUniformVec2(Pipeline &pipeline, const std::string &name, const float *value) = 0;
        virtual void SetUniformVec3(Pipeline &pipeline, const std::string &name, const float *value) = 0;
        virtual void SetUniformVec4(Pipeline &pipeline, const std::string &name, const float *value) = 0;
        virtual void SetUniformMat3(Pipeline &pipeline, const std::string &name, const float *value) = 0;
        virtual void SetUniformMat4(Pipeline &pipeline, const std::string &name, const float *value) = 0;
        virtual void SetUniformTexture(Pipeline &pipeline, const std::string &name, Texture &texture, uint32_t unit) = 0;

        virtual void CreateRenderbuffer(RenderBuffer &renderBuffer, RenderBufferDesc &desc) = 0;
        virtual void ResizeRenderbuffer(RenderBuffer &renderBuffer, uint32_t width, uint32_t height) = 0;
        virtual void DestroyRenderbuffer(RenderBuffer &renderBuffer) = 0;
    };
}
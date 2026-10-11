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
        struct UniformBufferObject
        {
            unsigned int uniformBuffer;
        };
        struct TextureBufferObject
        {
            unsigned int textureBuffer;
        };
        struct RenderBufferObject
        {
            unsigned int renderBufferObject;
            RenderBufferFormat format;
        };
        struct FrameBufferObject
        {
            unsigned int frameBuffer;
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
        std::map<UniformBuffer, UniformBufferObject> UBOStorage;
        uint32_t UBONextId = 0;
        std::map<Texture, TextureBufferObject> TBOStorage;
        uint32_t TBONextId = 0;
        std::map<RenderBuffer, RenderBufferObject> RBOStorage;
        uint32_t RBONextId = 0;
        std::map<FrameBuffer, FrameBufferObject> FBOStorage;
        uint32_t FBONextId = 0;

        static GLenum ToGL(DataType type);
        static GLenum ToGL(BufferUsage usage);
        static GLenum ToGL(DrawMode mode);
        static GLenum ToGL(TextureType type);
        static GLenum ToGL(TextureFormat format);
        static GLenum ToGL(TextureFilter filter);
        static GLenum ToGL(TextureWrap wrap);
        static GLenum ToGL(PixelFormat format);
        static GLenum ToGL(PixelType type);
        static GLenum ToGL(RenderState renderState);
        static GLenum ToGL(RenderBufferFormat renderBufferFormat);
        static GLenum ToGL(FrameBufferAttachment frameBufferAttachment);

    public:
        bool Init() override;
        void SetClearColor(Color &color) override;
        void ClearBufferBit(BufferBit &bufferBit) override;
        void SetRenderState(RenderState renderState) override;

        void SetViewport(int x, int y, uint32_t width, uint32_t height) override;

        void CreatePipeline(Pipeline &pipeline, std::string vertSource, std::string fragSource) override;
        void UsePipeline(Pipeline &pipeline) override;

        void CreateVertexArray(VertexArray &vertexArray) override;
        void CreateBuffer(VertexBuffer &vertexBuffer) override;
        void CreateBuffer(IndexBuffer &indexBuffer) override;
        void CreateBuffer(UniformBuffer &uniformBuffer) override;
        void SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage) override;
        void SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage) override;
        void SetBufferData(UniformBuffer &uniformBuffer, size_t size, const void *data, BufferUsage bufferUsage) override;
        void SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout) override;
        void SetVertexIndex(VertexArray &vertexArray, IndexBuffer &indexBuffer) override;
        void BindVertexArray(VertexArray &vertexArray) override;
        void Draw(DrawMode drawMode, uint32_t count) override;
        void DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer) override;

        void BindUniformBuffer(Pipeline &pipeline, UniformBuffer &uniformBuffer, const std::string &name, uint32_t binding) override;

        void DestroyVertexArray(VertexArray &vertexArray) override;
        void DestroyBuffer(VertexBuffer &vertexBuffer) override;
        void DestroyBuffer(IndexBuffer &indexBuffer) override;
        void DestroyBuffer(UniformBuffer &uniformBuffer) override;
        void DestroyPipeline(Pipeline &pipeline) override;

        void CreateTexture(Texture &texture, TextureDesc &desc) override;
        void SetTextureData(Texture &texture, TextureType textureType, uint32_t mipLevel, uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint16_t depth, TextureFormat format, const void *data) override;
        void GenerateTextureMipmap(Texture &texture) override;
        void BindTexture(Texture &texture, uint32_t unit) override;
        void DestroyTexture(Texture &texture) override;

        void SetUniformInt(Pipeline &pipeline, const std::string &name, int value) override;
        void SetUniformFloat(Pipeline &pipeline, const std::string &name, float value) override;
        void SetUniformVec2(Pipeline &pipeline, const std::string &name, const float *value) override;
        void SetUniformVec3(Pipeline &pipeline, const std::string &name, const float *value) override;
        void SetUniformVec4(Pipeline &pipeline, const std::string &name, const float *value) override;
        void SetUniformMat3(Pipeline &pipeline, const std::string &name, const float *value) override;
        void SetUniformMat4(Pipeline &pipeline, const std::string &name, const float *value) override;
        void SetUniformTexture(Pipeline &pipeline, const std::string &name, Texture &texture, uint32_t unit) override;

        void CreateRenderbuffer(RenderBuffer &renderBuffer, RenderBufferDesc &desc) override;
        void ResizeRenderbuffer(RenderBuffer &renderBuffer, uint32_t width, uint32_t height) override;
        void DestroyRenderbuffer(RenderBuffer &renderBuffer) override;

        void CreateFramebuffer(FrameBuffer &framebuffer) override;
        void SetFramebufferDrawBuffers(FrameBuffer &framebuffer, const std::vector<FrameBufferAttachment> &attachments) override;
        void AttachTexture(FrameBuffer &framebuffer, Texture &texture, FrameBufferAttachment attachment, uint32_t mipLevel = 0) override;
        void AttachRenderbuffer(FrameBuffer &framebuffer, RenderBuffer &renderBuffer, FrameBufferAttachment attachment) override;
        bool CheckFramebuffer(FrameBuffer &framebuffer) override;
        void DestroyFramebuffer(FrameBuffer &framebuffer) override;
        void BindFramebuffer(FrameBuffer &framebuffer) override;
        void BindDefaultFramebuffer() override;
    };

    inline GLenum OpenGlRenderer::ToGL(DataType type)
    {
        if (type == DataType::INT)
            return GL_INT;
        if (type == DataType::FLOAT)
            return GL_FLOAT;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(BufferUsage usage)
    {
        if (usage == BufferUsage::STATIC_DRAW)
            return GL_STATIC_DRAW;
        if (usage == BufferUsage::STATIC_READ)
            return GL_STATIC_READ;
        if (usage == BufferUsage::STATIC_COPY)
            return GL_STATIC_COPY;
        if (usage == BufferUsage::DYNAMIC_DRAW)
            return GL_DYNAMIC_DRAW;
        if (usage == BufferUsage::DYNAMIC_READ)
            return GL_DYNAMIC_READ;
        if (usage == BufferUsage::DYNAMIC_COPY)
            return GL_DYNAMIC_COPY;
        if (usage == BufferUsage::STREAM_DRAW)
            return GL_STREAM_DRAW;
        if (usage == BufferUsage::STREAM_READ)
            return GL_STREAM_READ;
        if (usage == BufferUsage::STREAM_COPY)
            return GL_STREAM_COPY;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(DrawMode mode)
    {
        if (mode == DrawMode::POINTS)
            return GL_POINTS;
        if (mode == DrawMode::LINES)
            return GL_LINES;
        if (mode == DrawMode::LINE_STRIP)
            return GL_LINE_STRIP;
        if (mode == DrawMode::LINE_LOOP)
            return GL_LINE_LOOP;
        if (mode == DrawMode::TRIANGLES)
            return GL_TRIANGLES;
        if (mode == DrawMode::TRIANGLE_STRIP)
            return GL_TRIANGLE_STRIP;
        if (mode == DrawMode::TRIANGLE_FAN)
            return GL_TRIANGLE_FAN;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(TextureType type)
    {
        if (type == TextureType::TEXTURE_2D)
            return GL_TEXTURE_2D;
        if (type == TextureType::TEXTURE_3D)
            return GL_TEXTURE_3D;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(TextureFormat format)
    {
        if (format == TextureFormat::R8)
            return GL_R8;
        if (format == TextureFormat::RG8)
            return GL_RG8;
        if (format == TextureFormat::RGB8)
            return GL_RGB8;
        if (format == TextureFormat::RGBA8)
            return GL_RGBA8;
        if (format == TextureFormat::R16F)
            return GL_R16F;
        if (format == TextureFormat::RG16F)
            return GL_RG16F;
        if (format == TextureFormat::RGB16F)
            return GL_RGB16F;
        if (format == TextureFormat::RGBA16F)
            return GL_RGBA16F;
        if (format == TextureFormat::DEPTH24)
            return GL_DEPTH_COMPONENT24;
        if (format == TextureFormat::DEPTH24_STENCIL8)
            return GL_DEPTH24_STENCIL8;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(TextureFilter filter)
    {
        if (filter == TextureFilter::NEAREST)
            return GL_NEAREST;
        if (filter == TextureFilter::LINEAR)
            return GL_LINEAR;
        if (filter == TextureFilter::NEAREST_MIPMAP_NEAREST)
            return GL_NEAREST_MIPMAP_NEAREST;
        if (filter == TextureFilter::LINEAR_MIPMAP_LINEAR)
            return GL_LINEAR_MIPMAP_LINEAR;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(TextureWrap wrap)
    {
        if (wrap == TextureWrap::REPEAT)
            return GL_REPEAT;
        if (wrap == TextureWrap::MIRRORED_REPEAT)
            return GL_MIRRORED_REPEAT;
        if (wrap == TextureWrap::CLAMP_TO_EDGE)
            return GL_CLAMP_TO_EDGE;
        if (wrap == TextureWrap::CLAMP_TO_BORDER)
            return GL_CLAMP_TO_BORDER;
        return 0;
    }
    inline GLenum OpenGlRenderer::ToGL(PixelFormat format)
    {
        if (format == PixelFormat::RED)
            return GL_RED;
        if (format == PixelFormat::RG)
            return GL_RG;
        if (format == PixelFormat::RGB)
            return GL_RGB;
        if (format == PixelFormat::RGBA)
            return GL_RGBA;
        if (format == PixelFormat::DEPTH)
            return GL_DEPTH_COMPONENT;
        if (format == PixelFormat::DEPTH_STENCIL)
            return GL_DEPTH_STENCIL;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(PixelType type)
    {
        if (type == PixelType::UNSIGNED_BYTE)
            return GL_UNSIGNED_BYTE;
        if (type == PixelType::BYTE)
            return GL_BYTE;
        if (type == PixelType::UNSIGNED_SHORT)
            return GL_UNSIGNED_SHORT;
        if (type == PixelType::SHORT)
            return GL_SHORT;
        if (type == PixelType::UNSIGNED_INT)
            return GL_UNSIGNED_INT;
        if (type == PixelType::INT)
            return GL_INT;
        if (type == PixelType::HALF_FLOAT)
            return GL_HALF_FLOAT;
        if (type == PixelType::FLOAT)
            return GL_FLOAT;
        if (type == PixelType::UNSIGNED_INT_24_8)
            return GL_UNSIGNED_INT_24_8;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(RenderState state)
    {
        if (state == RenderState::BLEND)
            return GL_BLEND;
        if (state == RenderState::CULL_FACE)
            return GL_CULL_FACE;
        if (state == RenderState::DEPTH_TEST)
            return GL_DEPTH_TEST;
        if (state == RenderState::SCISSOR_TEST)
            return GL_SCISSOR_TEST;
        if (state == RenderState::STENCIL_TEST)
            return GL_STENCIL_TEST;
        if (state == RenderState::MULTISAMPLE)
            return GL_MULTISAMPLE;
        if (state == RenderState::FRAMEBUFFER_SRGB)
            return GL_FRAMEBUFFER_SRGB;
        if (state == RenderState::RASTERIZER_DISCARD)
            return GL_RASTERIZER_DISCARD;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(RenderBufferFormat format)
    {
        if (format == RenderBufferFormat::DEPTH24)
            return GL_DEPTH_COMPONENT24;
        if (format == RenderBufferFormat::DEPTH24_STENCIL8)
            return GL_DEPTH24_STENCIL8;
        if (format == RenderBufferFormat::STENCIL8)
            return GL_STENCIL_INDEX8;
        if (format == RenderBufferFormat::RGBA8)
            return GL_RGBA8;
        return 0;
    }

    inline GLenum OpenGlRenderer::ToGL(FrameBufferAttachment attachment)
    {
        if (attachment == FrameBufferAttachment::COLOR0)
            return GL_COLOR_ATTACHMENT0;
        if (attachment == FrameBufferAttachment::COLOR1)
            return GL_COLOR_ATTACHMENT1;
        if (attachment == FrameBufferAttachment::COLOR2)
            return GL_COLOR_ATTACHMENT2;
        if (attachment == FrameBufferAttachment::COLOR3)
            return GL_COLOR_ATTACHMENT3;
        if (attachment == FrameBufferAttachment::DEPTH)
            return GL_DEPTH_ATTACHMENT;
        if (attachment == FrameBufferAttachment::STENCIL)
            return GL_STENCIL_ATTACHMENT;
        if (attachment == FrameBufferAttachment::DEPTH_STENCIL)
            return GL_DEPTH_STENCIL_ATTACHMENT;
        return 0;
    }

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

    inline void OpenGlRenderer::SetRenderState(RenderState renderState)
    {
        OpenGlWrapper::OpenGl::Enable(ToGL(renderState));
    }

    inline void OpenGlRenderer::SetViewport(int x, int y, uint32_t width, uint32_t height)
{
    OpenGlWrapper::OpenGl::SetViewport(x, y, width, height);
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

    inline void OpenGlRenderer::CreateBuffer(UniformBuffer &uniformBuffer)
    {
        UniformBufferObject ubo;
        OpenGlWrapper::OpenGl::CreateBuffer(ubo.uniformBuffer);
        uniformBuffer.handle = UBONextId++;
        UBOStorage.emplace(uniformBuffer, ubo);
    }

    inline void OpenGlRenderer::SetBufferData(VertexBuffer &vertexBuffer, size_t size, const void *data, BufferUsage bufferUsage)
    {
        auto it = VBOStorage.find(vertexBuffer);
        if (it == VBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::SetBufferData(it->second.vertexBuffer, size, data, ToGL(bufferUsage));
    }
    inline void OpenGlRenderer::SetBufferData(IndexBuffer &indexBuffer, size_t size, const void *data, BufferUsage bufferUsage)
    {
        auto it = IBOStorage.find(indexBuffer);
        if (it == IBOStorage.end())
            return;
        OpenGlWrapper::OpenGl::SetBufferData(it->second.indexBuffer, size, data, ToGL(bufferUsage));
    }

    inline void OpenGlRenderer::SetBufferData(UniformBuffer &uniformBuffer, size_t size, const void *data, BufferUsage bufferUsage)
    {
        auto it = UBOStorage.find(uniformBuffer);
        if (it == UBOStorage.end())
            return;
        OpenGlWrapper::OpenGl::SetBufferData(it->second.uniformBuffer, size, data, ToGL(bufferUsage));
    }

    inline void OpenGlRenderer::SetVertexLayout(VertexArray &vertexArray, VertexBuffer &vertexBuffer, VertexLayout &vertexLayout)
    {
        auto it_vao = VAOStorage.find(vertexArray);
        auto it_vbo = VBOStorage.find(vertexBuffer);
        if (it_vao == VAOStorage.end() || it_vbo == VBOStorage.end())
            return;

        for (auto vertexAttribute : vertexLayout.attribute)
        {
            OpenGlWrapper::OpenGl::SetVertexLayout(it_vao->second.vertexArray, it_vbo->second.vertexBuffer, vertexAttribute.bindingIndex, vertexAttribute.location, vertexAttribute.size, vertexAttribute.offset, vertexAttribute.stride, ToGL(vertexAttribute.dataType));
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
        OpenGlWrapper::OpenGl::Draw(ToGL(drawMode), count);
    }

    inline void OpenGlRenderer::DrawIndexed(DrawMode drawMode, IndexBuffer &indexBuffer)
    {
        auto it = IBOStorage.find(indexBuffer);
        if (it == IBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DrawIndexed(ToGL(drawMode), GL_UNSIGNED_INT, nullptr, it->first.count);
    }

    inline void OpenGlRenderer::BindUniformBuffer(Pipeline &pipeline, UniformBuffer &uniformBuffer, const std::string &name, uint32_t binding)
    {
        auto it_program = programStorage.find(pipeline);
        auto it_uniform = UBOStorage.find(uniformBuffer);

        if (it_program == programStorage.end() || it_uniform == UBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::BindUniformBuffer(it_program->second.program, it_uniform->second.uniformBuffer, name.c_str(), binding);
    }

    inline void OpenGlRenderer::DestroyVertexArray(VertexArray &vertexArray)
    {
        auto it = VAOStorage.find(vertexArray);
        if (it == VAOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DeleteVertexArray(it->second.vertexArray);
        VAOStorage.erase(vertexArray);
        vertexArray.handle = UINT32_MAX;
    }

    inline void OpenGlRenderer::DestroyBuffer(VertexBuffer &vertexBuffer)
    {
        auto it = VBOStorage.find(vertexBuffer);
        if (it == VBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DeleteBuffer(it->second.vertexBuffer);
        VBOStorage.erase(vertexBuffer);
        vertexBuffer.handle = UINT32_MAX;
    }

    inline void OpenGlRenderer::DestroyBuffer(IndexBuffer &indexBuffer)
    {
        auto it = IBOStorage.find(indexBuffer);
        if (it == IBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DeleteBuffer(it->second.indexBuffer);
        IBOStorage.erase(indexBuffer);
        indexBuffer.handle = UINT32_MAX;
    }

    inline void OpenGlRenderer::DestroyBuffer(UniformBuffer &uniformBuffer)
    {
        auto it = UBOStorage.find(uniformBuffer);
        if (it == UBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DeleteBuffer(it->second.uniformBuffer);
        UBOStorage.erase(uniformBuffer);
        uniformBuffer.handle = UINT32_MAX;
    }

    inline void OpenGlRenderer::DestroyPipeline(Pipeline &pipeline)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        OpenGlWrapper::OpenGl::DeleteProgram(it->second.program);
        programStorage.erase(pipeline);
        pipeline.handle = UINT32_MAX;
    }

    inline void OpenGlRenderer::CreateTexture(Texture &texture, TextureDesc &desc)
    {
        TextureBufferObject tbo;

        OpenGlWrapper::OpenGl::CreateTexture(tbo.textureBuffer, ToGL(desc.type), ToGL(desc.format), desc.width, desc.height, desc.depth, desc.levels, ToGL(desc.minFilter), ToGL(desc.magFilter), ToGL(desc.wrapS), ToGL(desc.wrapT), ToGL(desc.wrapR));

        texture.handle = TBONextId++;
        TBOStorage.emplace(texture, tbo);
    }

    inline void OpenGlRenderer::SetTextureData(Texture &texture, TextureType textureType, uint32_t mipLevel, uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint16_t depth, TextureFormat format, const void *data)
    {
        auto it = TBOStorage.find(texture);
        if (it == TBOStorage.end())
            return;

        PixelFormat pixelFormat;
        PixelType pixelType;

        if (format == TextureFormat::R8)
        {
            pixelFormat = PixelFormat::RED;
            pixelType = PixelType::UNSIGNED_BYTE;
        }
        if (format == TextureFormat::RG8)
        {
            pixelFormat = PixelFormat::RG;
            pixelType = PixelType::UNSIGNED_BYTE;
        }
        if (format == TextureFormat::RGB8)
        {
            pixelFormat = PixelFormat::RGB;
            pixelType = PixelType::UNSIGNED_BYTE;
        }
        if (format == TextureFormat::RGBA8)
        {
            pixelFormat = PixelFormat::RGBA;
            pixelType = PixelType::UNSIGNED_BYTE;
        }
        if (format == TextureFormat::R16F)
        {
            pixelFormat = PixelFormat::RED;
            pixelType = PixelType::HALF_FLOAT;
        }
        if (format == TextureFormat::RG16F)
        {
            pixelFormat = PixelFormat::RG;
            pixelType = PixelType::HALF_FLOAT;
        }
        if (format == TextureFormat::RGB16F)
        {
            pixelFormat = PixelFormat::RGB;
            pixelType = PixelType::HALF_FLOAT;
        }
        if (format == TextureFormat::RGBA16F)
        {
            pixelFormat = PixelFormat::RGBA;
            pixelType = PixelType::HALF_FLOAT;
        }
        if (format == TextureFormat::DEPTH24)
        {
            pixelFormat = PixelFormat::DEPTH;
            pixelType = PixelType::UNSIGNED_INT;
        }
        if (format == TextureFormat::DEPTH24_STENCIL8)
        {
            pixelFormat = PixelFormat::DEPTH_STENCIL;
            pixelType = PixelType::UNSIGNED_INT_24_8;
        }

        OpenGlWrapper::OpenGl::SetTextureData(it->second.textureBuffer, ToGL(textureType), mipLevel, x, y, z, width, height, depth, ToGL(pixelFormat), ToGL(pixelType), data);
    }

    inline void OpenGlRenderer::GenerateTextureMipmap(Texture &texture)
    {
        auto it = TBOStorage.find(texture);
        if (it == TBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::GenerateTextureMipmap(it->second.textureBuffer);
    }

    inline void OpenGlRenderer::BindTexture(Texture &texture, uint32_t unit)
    {
        auto it = TBOStorage.find(texture);
        if (it == TBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::BindTexture(it->second.textureBuffer, unit);
    }

    inline void OpenGlRenderer::DestroyTexture(Texture &texture)
    {
        auto it = TBOStorage.find(texture);
        if (it == TBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DestroyTexture(it->second.textureBuffer);
        TBOStorage.erase(texture);
        texture.handle = UINT32_MAX;
    }

    inline void OpenGlRenderer::SetUniformInt(Pipeline &pipeline, const std::string &name, int value)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniform1i(it->second.program, location, value);
    }

    inline void OpenGlRenderer::SetUniformFloat(Pipeline &pipeline, const std::string &name, float value)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniform1f(it->second.program, location, value);
    }

    inline void OpenGlRenderer::SetUniformVec2(Pipeline &pipeline, const std::string &name, const float *value)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniformVec2f(it->second.program, location, value);
    }

    inline void OpenGlRenderer::SetUniformVec3(Pipeline &pipeline, const std::string &name, const float *value)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniformVec3f(it->second.program, location, value);
    }

    inline void OpenGlRenderer::SetUniformVec4(Pipeline &pipeline, const std::string &name, const float *value)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniformVec4f(it->second.program, location, value);
    }

    inline void OpenGlRenderer::SetUniformMat3(Pipeline &pipeline, const std::string &name, const float *value)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniformMat3f(it->second.program, location, value);
    }

    inline void OpenGlRenderer::SetUniformMat4(Pipeline &pipeline, const std::string &name, const float *value)
    {
        auto it = programStorage.find(pipeline);
        if (it == programStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniformMat4f(it->second.program, location, value);
    }

    inline void OpenGlRenderer::SetUniformTexture(Pipeline &pipeline, const std::string &name, Texture &texture, uint32_t unit)
    {
        auto it_program = programStorage.find(pipeline);
        auto it_texture = TBOStorage.find(texture);
        if (it_program == programStorage.end() || it_texture == TBOStorage.end())
            return;

        int location = OpenGlWrapper::OpenGl::GetUniformLocation(it_program->second.program, name.c_str());
        if (location == -1)
            return;

        OpenGlWrapper::OpenGl::SetProgramUniformTexture(it_program->second.program, location, it_texture->second.textureBuffer, unit);
    }

    inline void OpenGlRenderer::CreateRenderbuffer(RenderBuffer &renderBuffer, RenderBufferDesc &desc)
    {
        RenderBufferObject rbo;
        rbo.format = desc.format;
        OpenGlWrapper::OpenGl::CreateRenderbuffer(rbo.renderBufferObject, ToGL(desc.format), desc.width, desc.height);
        renderBuffer.handle = RBONextId++;
        RBOStorage.emplace(renderBuffer, rbo);
    }

    inline void OpenGlRenderer::ResizeRenderbuffer(RenderBuffer &renderBuffer, uint32_t width, uint32_t height)
    {
        auto it = RBOStorage.find(renderBuffer);
        if (it == RBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::ResizeRenderbuffer(it->second.renderBufferObject, ToGL(it->second.format), width, height);
    }

    inline void OpenGlRenderer::DestroyRenderbuffer(RenderBuffer &renderBuffer)
    {
        auto it = RBOStorage.find(renderBuffer);
        if (it == RBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DeleteRenderBuffer(it->second.renderBufferObject);
        RBOStorage.erase(renderBuffer);
        renderBuffer.handle = UINT32_MAX;
    }

    inline void OpenGlRenderer::CreateFramebuffer(FrameBuffer &framebuffer)
    {
        FrameBufferObject fbo;
        OpenGlWrapper::OpenGl::CreateFramebuffer(fbo.frameBuffer);
        framebuffer.handle = FBONextId++;
        FBOStorage.emplace(framebuffer, fbo);
    }

    inline void OpenGlRenderer::SetFramebufferDrawBuffers(FrameBuffer &framebuffer, const std::vector<FrameBufferAttachment> &attachments)
    {
        auto it = FBOStorage.find(framebuffer);
        if (it == FBOStorage.end())
            return;

        std::vector<GLenum> drawBuffers;
        drawBuffers.reserve(attachments.size());

        for (auto attachment : attachments)
        {
            drawBuffers.push_back(ToGL(attachment));
        }

        OpenGlWrapper::OpenGl::SetFramebufferDrawBuffers(it->second.frameBuffer, drawBuffers);
    }

    inline void OpenGlRenderer::AttachTexture(FrameBuffer &framebuffer, Texture &texture, FrameBufferAttachment attachment, uint32_t mipLevel)
    {
        auto itFBO = FBOStorage.find(framebuffer);
        auto itTexture = TBOStorage.find(texture);
        if (itFBO == FBOStorage.end() || itTexture == TBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::AttachTexture(itFBO->second.frameBuffer, itTexture->second.textureBuffer, ToGL(attachment), mipLevel);
    }

    inline void OpenGlRenderer::AttachRenderbuffer(FrameBuffer &framebuffer, RenderBuffer &renderBuffer, FrameBufferAttachment attachment)
    {
        auto itFBO = FBOStorage.find(framebuffer);
        auto itRBO = RBOStorage.find(renderBuffer);
        if (itFBO == FBOStorage.end() || itRBO == RBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::AttachRenderbuffer(itFBO->second.frameBuffer, itRBO->second.renderBufferObject, ToGL(attachment));
    }

    inline bool OpenGlRenderer::CheckFramebuffer(FrameBuffer &framebuffer)
    {
        auto it = FBOStorage.find(framebuffer);
        if (it == FBOStorage.end())
            return false;

        return OpenGlWrapper::OpenGl::CheckFramebuffer(it->second.frameBuffer);
    }

    inline void OpenGlRenderer::BindFramebuffer(FrameBuffer &framebuffer)
    {
        auto it = FBOStorage.find(framebuffer);
        if (it == FBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::BindFramebuffer(it->second.frameBuffer);
    }

    inline void OpenGlRenderer::BindDefaultFramebuffer()
    {
        OpenGlWrapper::OpenGl::BindDefaultFramebuffer();
    }

    inline void OpenGlRenderer::DestroyFramebuffer(FrameBuffer &framebuffer)
    {
        auto it = FBOStorage.find(framebuffer);
        if (it == FBOStorage.end())
            return;

        OpenGlWrapper::OpenGl::DestroyFramebuffer(it->second.frameBuffer);
        FBOStorage.erase(it);
        framebuffer.handle = UINT32_MAX;
    }
}
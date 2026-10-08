#include "OpenGlRenderer.hpp"
#include "Wrapper/OpenGl.hpp"

namespace RGE
{
    void OpenGlRenderer::Init()
    {
        // EXEC
        OpenGlWrapper::OpenGl::Init();
    }

    void OpenGlRenderer::SetClearColor(Color &color)
    {
        // MAPPING
        OpenGlWrapper::Color _color;
        _color.r = color.r;
        _color.g = color.g;
        _color.b = color.b;
        _color.a = color.a;
        // EXEC
        OpenGlWrapper::OpenGl::SetClearColor(_color);
    }

    void OpenGlRenderer::SetDepthStencil(DepthStencilParams &params)
    {
        // MAPPING
        OpenGlWrapper::DepthStencilParams _params;
        _params.depthTest = params.depthTest;
        _params.stencilTest = params.stencilTest;
        // EXEC
        OpenGlWrapper::OpenGl::SetDepthStencil(_params);
    }

    void OpenGlRenderer::Clear(ClearParams &params)
    {
        // EXEC
        OpenGlWrapper::OpenGl::Clear(params.color, params.depth, params.stencil);
    }

    void OpenGlRenderer::CreateShader(ShaderHandle &handle, ShaderSource &source)
    {
        // MAPPING
        OpenGlWrapper::ShaderProgram _shaderProgram;
        OpenGlWrapper::ShaderSource _shaderSource;
        _shaderSource.vertSource = source.vertSource;
        _shaderSource.fragSource = source.fragSource;
        // EXEC
        OpenGlWrapper::OpenGl::CreateShader(_shaderSource, _shaderProgram);
        // OUT
        handle.handle = nextShaderId++;
        shaderStorage.emplace(handle, _shaderProgram);
    }

    void OpenGlRenderer::DestroyShader(ShaderHandle &handle)
    {
        // FIND
        auto it = shaderStorage.find(handle);
        if (it == shaderStorage.end())
        {
            return;
        }
        // EXEC
        OpenGlWrapper::OpenGl::DestroyShader(it->second.program);
        shaderStorage.erase(handle);
    }

    void OpenGlRenderer::UseShader(ShaderHandle &shaderHandle)
    {
        auto it = shaderStorage.find(shaderHandle);
        if (it == shaderStorage.end())
        {
            return;
        }
        OpenGlWrapper::OpenGl::UseShaderProgram(it->second.program);
    }

    void OpenGlRenderer::CreateMesh(MeshHandle &handle, MeshSource &source)
    {
        // MAPPING
        OpenGlWrapper::VertexArrayBuffer vao;
        OpenGlWrapper::VertexBuffer vbo;
        vbo.vertices = source.vertices;

        OpenGlWrapper::ElementBuffer ebo;
        ebo.indices = source.indices;

        OpenGlWrapper::VertexLayout _layout;
        _layout.index = source.layout.index;
        _layout.offset = source.layout.offset;
        _layout.stride = source.layout.stride;

        OpenGlWrapper::OpenGl::CreateVertexArrayBuffer(vao);
        OpenGlWrapper::OpenGl::CreateVertexBuffer(vbo);
        OpenGlWrapper::OpenGl::CreateElementBuffer(ebo);

        for (const auto &attribute : source.layout.attributes)
        {
            OpenGlWrapper::VertexAttribute _attribute;
            _attribute.index = attribute.index;
            _attribute.size = attribute.size;
            _attribute.relative = attribute.relative;

            OpenGlWrapper::OpenGl::SetupVertexArrayVertexBuffer(vao, vbo, _layout, _attribute);
        }
        OpenGlWrapper::OpenGl::SetupVertexArrayElementBuffer(vao, ebo);

        OpenGlMesh mesh;
        mesh.vao = vao;
        mesh.vbo = vbo;
        mesh.ebo = ebo;

        handle.handle = nextMeshId++;
        meshStorage.emplace(handle, mesh);
    }

    void OpenGlRenderer::DestroyMesh(MeshHandle &handle)
    {
        auto it = meshStorage.find(handle);
        if (it == meshStorage.end())
        {
            return;
        }
        OpenGlWrapper::OpenGl::DestroyVertexArrayVertexBufferElementBuffer(it->second.vao, it->second.vbo, it->second.ebo);
        meshStorage.erase(handle);
    }

    void OpenGlRenderer::BindMesh(MeshHandle &handle)
    {
        auto it = meshStorage.find(handle);
        if (it == meshStorage.end())
        {
            return;
        }
        OpenGlWrapper::OpenGl::BindVertexArrayBuffer(it->second.vao);
    }

    void OpenGlRenderer::UnbindMesh()
    {
        OpenGlWrapper::OpenGl::UnbindVertexArrayBuffer();
    }

    void OpenGlRenderer::DrawMesh(MeshHandle &handle)
    {
        auto it = meshStorage.find(handle);
        if (it == meshStorage.end())
        {
            return;
        }
        OpenGlWrapper::OpenGl::DrawArrayElement(it->second.ebo);
    }

    void OpenGlRenderer::CreateTexture2D(TextureHandle &textureHandle, TextureSource &textureSource)
    {
        OpenGlWrapper::TextureBuffer textureBuffer;
        OpenGlWrapper::TextureAttribute textureAttribute;
        textureAttribute.width = textureSource.width;
        textureAttribute.height = textureSource.height;
        textureAttribute.levels = 1;
        textureAttribute.xOffset = 0;
        textureAttribute.yOffset = 0;
        textureAttribute.dataType = GL_UNSIGNED_BYTE;
        textureAttribute.textureType = GL_TEXTURE_2D;

        switch (textureSource.format)
        {
        case TextureFormat::R8:
            textureAttribute.internalFormat = GL_R8;
            textureAttribute.format = GL_RED;
            break;
        case TextureFormat::RG8:
            textureAttribute.internalFormat = GL_RG8;
            textureAttribute.format = GL_RG;
            break;
        case TextureFormat::RGB8:
            textureAttribute.internalFormat = GL_RGB;
            textureAttribute.format = GL_RGB;
            break;
        case TextureFormat::RGBA8:
            textureAttribute.internalFormat = GL_RGBA8;
            textureAttribute.format = GL_RGBA;
            break;
        }

        OpenGlWrapper::TextureSource _textureSource;
        _textureSource.source = textureSource.data.data();

        OpenGlWrapper::OpenGl::CreateTexture(textureBuffer, textureAttribute);
        OpenGlWrapper::OpenGl::SetupTexture(textureBuffer, textureAttribute, _textureSource);

        OpenGlTexture texture;
        texture.texture = textureBuffer;

        textureHandle.handle = nextTextureId++;
        textureStorage.emplace(textureHandle, texture);
    }

    void OpenGlRenderer::SetTexture2DFilter(TextureHandle &textureHandle, Texture2DFilter &texture2dFilter)
    {
        auto it = textureStorage.find(textureHandle);
        if (it == textureStorage.end())
        {
            return;
        }

        OpenGlWrapper::TextureFilter textureFilter;

        switch (texture2dFilter.min)
        {
        case TextureFilter::Linear:
            textureFilter.min = GL_LINEAR;
            break;
        case TextureFilter::Nearest:
            textureFilter.min = GL_NEAREST;
            break;
        case TextureFilter::NearestMipmapNearest:
            textureFilter.min = GL_NEAREST_MIPMAP_NEAREST;
            break;
        case TextureFilter::LinearMipmapNearest:
            textureFilter.min = GL_LINEAR_MIPMAP_NEAREST;
            break;
        case TextureFilter::NearestMipmapLinear:
            textureFilter.min = GL_NEAREST_MIPMAP_LINEAR;
            break;
        case TextureFilter::LinearMipmapLinear:
            textureFilter.min = GL_LINEAR_MIPMAP_LINEAR;
            break;
        default:
            textureFilter.min = GL_LINEAR;
            break;
        }

        switch (texture2dFilter.mag)
        {
        case TextureFilter::Linear:
            textureFilter.mag = GL_LINEAR;
            break;
        case TextureFilter::Nearest:
            textureFilter.mag = GL_NEAREST;
            break;
        default:
            textureFilter.mag = GL_LINEAR;
            break;
        }
        OpenGlWrapper::OpenGl::SetTextureFilter(it->second.texture, textureFilter);
    }
    void OpenGlRenderer::SetTexture2DWrap(TextureHandle &textureHandle, Texture2DWrap &texture2DWrap)
    {
        auto it = textureStorage.find(textureHandle);
        if (it == textureStorage.end())
        {
            return;
        }

        OpenGlWrapper::TextureWrap textureWrap;

        switch (texture2DWrap.s)
        {
        case TextureWrap::Repeat:
            textureWrap.s = GL_REPEAT;
            break;
        case TextureWrap::MirroredRepeat:
            textureWrap.s = GL_MIRRORED_REPEAT;
            break;
        case TextureWrap::ClampToEdge:
            textureWrap.s = GL_CLAMP_TO_EDGE;
            break;
        case TextureWrap::ClampToBorder:
            textureWrap.s = GL_CLAMP_TO_BORDER;
            break;
        }
        switch (texture2DWrap.t)
        {
        case TextureWrap::Repeat:
            textureWrap.t = GL_REPEAT;
            break;
        case TextureWrap::MirroredRepeat:
            textureWrap.t = GL_MIRRORED_REPEAT;
            break;
        case TextureWrap::ClampToEdge:
            textureWrap.t = GL_CLAMP_TO_EDGE;
            break;
        case TextureWrap::ClampToBorder:
            textureWrap.t = GL_CLAMP_TO_BORDER;
            break;
        }
        textureWrap.r = GL_NONE;

        OpenGlWrapper::OpenGl::SetTextureWrap(it->second.texture, textureWrap);
    }
    void OpenGlRenderer::GenerateTextureMipmap(TextureHandle &textureHandle){
        auto it = textureStorage.find(textureHandle);
        if (it == textureStorage.end()){
            return;
        }
        
        OpenGlWrapper::OpenGl::GenerateTextureMipmap(it->second.texture);
    }
    void OpenGlRenderer::DestroyTexture2D(TextureHandle &textureHandle)
    {
        auto it = textureStorage.find(textureHandle);
        if (it == textureStorage.end())
        {
            return;
        }
        OpenGlWrapper::OpenGl::DestroyTexture(it->second.texture);
        textureStorage.erase(textureHandle);
    }

    void OpenGlRenderer::BindTexture(TextureHandle &textureHandle, uint32_t unit)
    {
        auto it = textureStorage.find(textureHandle);
        if (it == textureStorage.end())
        {
            return;
        }
        OpenGlWrapper::OpenGl::BindTexture(it->second.texture, unit);
    }

    void OpenGlRenderer::UnbindTexture(uint32_t unit)
    {
        OpenGlWrapper::OpenGl::UnbindTexture(unit);
    }
}
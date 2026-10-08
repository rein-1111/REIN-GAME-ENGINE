#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

namespace RGE
{
    struct Color
    {
        float r;
        float g;
        float b;
        float a;
    };

    struct DepthStencilParams
    {
        bool depthTest;
        bool stencilTest;
    };

    struct ClearParams
    {
        bool color;
        bool depth;
        bool stencil;
    };

    struct ShaderHandle
    {
        uint32_t handle;

        bool operator<(const ShaderHandle &other) const
        {
            return handle < other.handle;
        }
    };

    struct ShaderSource
    {
        std::string vertSource;
        std::string fragSource;
    };

    struct MeshHandle
    {
        uint32_t handle;

        bool operator<(const MeshHandle &other) const
        {
            return handle < other.handle;
        }
    };

    struct VertexAttribute
    {
        uint32_t index;
        uint32_t size;
        uint32_t relative;
    };

    struct VertexLayout
    {
        uint32_t index;
        uint32_t offset;
        uint32_t stride;
        std::vector<VertexAttribute> attributes;
    };

    struct MeshSource
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        VertexLayout layout;
    };

    struct TextureHandle
    {
        uint32_t handle;

        bool operator<(const TextureHandle &other) const
        {
            return handle < other.handle;
        }
    };

    enum class TextureFormat
    {
        R8,
        RG8,
        RGB8,
        RGBA8,
    };
    enum class TextureFilter
    {
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear,
    };
    enum class TextureWrap
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder,
    };
    struct TextureSource
    {
        uint32_t width;
        uint32_t height;
        TextureFormat format;
        std::vector<uint8_t> data;
    };
    struct Texture2DFilter
    {
        TextureFilter min;
        TextureFilter mag;
    };

    struct Texture2DWrap
    {
        TextureWrap s;
        TextureWrap t;
    };

    class I_Renderer
    {
    private:
    public:
        virtual void Init() = 0;

        virtual void SetClearColor(Color &color) = 0;
        virtual void SetDepthStencil(DepthStencilParams &params) = 0;
        virtual void Clear(ClearParams &params) = 0;

        virtual void CreateShader(ShaderHandle &meshHandle, ShaderSource &source) = 0;
        virtual void DestroyShader(ShaderHandle &meshHandle) = 0;
        virtual void UseShader(ShaderHandle &shaderHandle) = 0;

        virtual void CreateMesh(MeshHandle &meshHandle, MeshSource &source) = 0;
        virtual void DestroyMesh(MeshHandle &meshHandle) = 0;
        virtual void BindMesh(MeshHandle &meshHandle) = 0;
        virtual void UnbindMesh() = 0;
        virtual void DrawMesh(MeshHandle &meshHandle) = 0;


        virtual void CreateTexture2D(TextureHandle &textureHandle, TextureSource &textureSource) = 0;
        virtual void SetTexture2DFilter(TextureHandle &textureHandle, Texture2DFilter &texture2DFilter) = 0;
        virtual void SetTexture2DWrap(TextureHandle &textureHandle, Texture2DWrap &texture2DWrap) = 0;
        virtual void DestroyTexture2D(TextureHandle &textureHandle) = 0;
        virtual void BindTexture(TextureHandle &textureHandle, uint32_t unit) = 0;
        virtual void UnbindTexture(uint32_t unit) = 0;
        virtual void GenerateTextureMipmap(TextureHandle &textureHandle) = 0;
    };
}
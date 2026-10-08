#pragma once

#include <memory>
#include "I_Renderer.hpp"

namespace RGE
{
    enum class Backend
    {
        OpenGl,
        Dawn
    };

    class Renderer
    {
    private:
        inline static std::unique_ptr<I_Renderer> renderer;

    public:
        inline static Backend backend;

        static void Init();

        static void SetClearColor(Color &color);
        static void SetDepthStencil(DepthStencilParams &params);
        static void Clear(ClearParams &params);

        static void CreateShader(ShaderHandle &handle, ShaderSource &source);
        static void DestroyShader(ShaderHandle &handle);
        static void UseShader(ShaderHandle &shaderHandle);

        static void CreateMesh(MeshHandle &handle, MeshSource &source);
        static void DestroyMesh(MeshHandle &handle);
        static void BindMesh(MeshHandle &handle);
        static void UnbindMesh();
        static void DrawMesh(MeshHandle &handle);

        static void CreateTexture2D(TextureHandle &textureHandle, TextureSource &textureSouce);
        static void SetTexture2DFilter(TextureHandle &textureHandle, Texture2DFilter &texture2DFilter);
        static void SetTexture2DWrap(TextureHandle &textureHandle, Texture2DWrap &texture2DWrap);
        static void DestroyTexture2D(TextureHandle &textureHandle);
        static void BindTexture(TextureHandle &textureHandle, uint32_t unit);
        static void UnbindTexture(uint32_t unit);
        static void GenerateTextureMipmap(TextureHandle &textureHandle);
    };
}
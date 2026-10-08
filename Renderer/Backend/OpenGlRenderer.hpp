#pragma once

#include <map>
#include "../I_Renderer.hpp"
#include "Wrapper/OpenGl.hpp"

namespace RGE
{
    struct OpenGlShader
    {
        OpenGlWrapper::ShaderProgram program;
    };

    struct OpenGlMesh
    {
        OpenGlWrapper::VertexArrayBuffer vao;
        OpenGlWrapper::VertexBuffer vbo;
        OpenGlWrapper::ElementBuffer ebo;
    };

    struct OpenGlTexture
    {
        OpenGlWrapper::TextureBuffer texture;
    };

    class OpenGlRenderer : public I_Renderer
    {
    private:
        std::map<ShaderHandle, OpenGlShader> shaderStorage;
        int nextShaderId = 0;

        std::map<MeshHandle, OpenGlMesh> meshStorage;
        int nextMeshId = 0;

        std::map<TextureHandle, OpenGlTexture> textureStorage;
        int nextTextureId = 0;

    public:
        void Init() override;

        void SetClearColor(Color &color) override;
        void SetDepthStencil(DepthStencilParams &params) override;
        void Clear(ClearParams &Clear) override;

        void CreateShader(ShaderHandle &handle, ShaderSource &source) override;
        void DestroyShader(ShaderHandle &handle) override;
        void UseShader(ShaderHandle &shaderHandle) override;

        void CreateMesh(MeshHandle &handle, MeshSource &source) override;
        void DestroyMesh(MeshHandle &handle) override;
        void BindMesh(MeshHandle &handle) override;
        void UnbindMesh() override;
        void DrawMesh(MeshHandle &meshHandle) override;

        void CreateTexture2D(TextureHandle &textureHandle, TextureSource &textureSource) override;
        void SetTexture2DFilter(TextureHandle &textureHandle, Texture2DFilter &texture2DFilter) override;
        void SetTexture2DWrap(TextureHandle &textureHandle, Texture2DWrap &texture2DWrap) override;
        void DestroyTexture2D(TextureHandle &textureHandle) override;
        void BindTexture(TextureHandle &textureHandle, uint32_t unit) override;
        void UnbindTexture(uint32_t unit) override;
        void GenerateTextureMipmap(TextureHandle &textureHandle) override;
    };
}
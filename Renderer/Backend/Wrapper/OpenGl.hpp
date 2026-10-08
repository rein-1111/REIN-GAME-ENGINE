#pragma once

#include <iostream>
#include <glad/glad.h>
#include <vector>

namespace OpenGlWrapper
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

    struct ShaderProgram
    {
        unsigned int program;
    };

    struct ShaderSource
    {
        std::string vertSource;
        std::string fragSource;
    };

    struct VertexArrayBuffer
    {
        unsigned int buffer;
    };

    struct VertexBuffer
    {
        unsigned int buffer;
        std::vector<float> vertices;
        GLenum type = GL_STATIC_DRAW;
    };

    struct VertexAttribute
    {
        int index;
        int size;
        int relative;
    };

    struct VertexLayout
    {
        int index;
        int offset;
        int stride;
    };

    struct ElementBuffer
    {
        unsigned int buffer;
        std::vector<unsigned int> indices;
        GLenum type = GL_STATIC_DRAW;
    };

    struct TextureBuffer
    {
        unsigned int buffer;
    };

    struct TextureAttribute
    {
        int width;
        int height;
        int levels;
        GLenum internalFormat;
        GLenum format;
        GLenum dataType;
        GLenum textureType;
        int xOffset;
        int yOffset;
        int unit;
    };

    struct TextureFilter{
        GLenum min;
        GLenum mag;
    };

    struct TextureWrap{
        GLenum s;
        GLenum t;
        GLenum r;
    };
    
    struct TextureSource
    {
        const void *source;
    };

    class OpenGl
    {
    private:
    public:
        static bool Init();

        static void SetClearColor(Color &color);
        static void SetDepthStencil(DepthStencilParams &params);
        static void Clear(bool color, bool depth, bool stencil);

        static void CreateShader(ShaderSource &source, ShaderProgram &program);
        static void DestroyShader(ShaderProgram &program);
        static void UseShaderProgram(ShaderProgram &shader);

        static void CreateVertexArrayBuffer(VertexArrayBuffer &arrayBuffer);
        static void CreateVertexBuffer(VertexBuffer &vertexBuffer);
        static void CreateElementBuffer(ElementBuffer &elementBuffer);
        static void SetupVertexArrayVertexBuffer(VertexArrayBuffer &arrayBuffer, VertexBuffer &VertexBuffer, VertexLayout &layout, VertexAttribute &attribute);
        static void SetupVertexArrayElementBuffer(VertexArrayBuffer &arrayBuffer, ElementBuffer &elementBuffer);
        static void BindVertexArrayBuffer(VertexArrayBuffer &arrayBuffer);
        static void UnbindVertexArrayBuffer();
        static void DestroyVertexArrayVertexBufferElementBuffer(VertexArrayBuffer &arrayBuffer, VertexBuffer &vertexBuffer, ElementBuffer &elementBuffer);
        static void DrawArrayElement(ElementBuffer &element);

        static void CreateTexture(TextureBuffer &textureBuffer, TextureAttribute &textureAttribute);
        static void SetupTexture(TextureBuffer &textureBuffer, TextureAttribute &textureAttribute, TextureSource &source);
        static void SetTextureFilter(TextureBuffer &textureBuffer, TextureFilter &textureFiler);
        static void SetTextureWrap(TextureBuffer &textureBuffer, TextureWrap &textureWrap);
        static void GenerateTextureMipmap(TextureBuffer &textureBuffer);
        static void DestroyTexture(TextureBuffer &texture);
        static void BindTexture(TextureBuffer &textureBuffer, uint32_t unit);
        static void UnbindTexture(uint32_t unit);
    };
}
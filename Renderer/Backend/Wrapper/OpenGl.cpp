#include "DebugLog.hpp"
#include "OpenGl.hpp"

namespace OpenGlWrapper
{
    // LOCAL IMPLEMENTATION
    static bool CheckShaderPipeline(unsigned int vertex, unsigned int fragment, unsigned int program)
    {
        int success;
        char infoLog[512];

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            ERROR_LOG_OPENGLBACKEND("VERTEX SHADER")
            ERROR_LOG_OPENGLBACKEND(infoLog)
            return false;
        }
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            ERROR_LOG_OPENGLBACKEND("FRAGMENT SHADER")
            ERROR_LOG_OPENGLBACKEND(infoLog)
            return false;
        }
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            ERROR_LOG_OPENGLBACKEND("SHADER PROGRAM")
            ERROR_LOG_OPENGLBACKEND(infoLog);
            return false;
        }
        return true;
    };

    // CLASS IMPLEMENTATION
    bool OpenGl::Init()
    {
        if (!gladLoadGL())
        {
            std::cout << "OPENGL::INIT::FAILED" << std::endl;
            return false;
        };
        return true;
    }

    void OpenGl::SetClearColor(Color &color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    };
    void OpenGl::SetDepthStencil(DepthStencilParams &params)
    {
        int mask = 0;
        if (params.depthTest)
            mask |= GL_DEPTH_TEST;
        if (params.stencilTest)
            mask |= GL_STENCIL_TEST;

        if (mask != 0)
        {
            glEnable(mask);
        }
    }
    void OpenGl::Clear(bool color, bool depth, bool stencil)
    {
        int mask = 0;
        if (color)
            mask |= GL_COLOR_BUFFER_BIT;
        if (depth)
            mask |= GL_DEPTH_BUFFER_BIT;
        if (stencil)
            mask |= GL_STENCIL_BUFFER_BIT;

        if (mask != 0)
        {
            glClear(mask);
        }
    }

    void OpenGl::CreateShader(ShaderSource &source, ShaderProgram &program)
    {
        unsigned int shaderVertex = glCreateShader(GL_VERTEX_SHADER);
        unsigned int shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);

        const char *vertSource = source.vertSource.c_str();
        const char *fragSource = source.fragSource.c_str();

        glShaderSource(shaderVertex, 1, &vertSource, nullptr);
        glShaderSource(shaderFragment, 1, &fragSource, nullptr);

        glCompileShader(shaderVertex);
        glCompileShader(shaderFragment);

        unsigned int shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, shaderVertex);
        glAttachShader(shaderProgram, shaderFragment);

        glLinkProgram(shaderProgram);

        if (!CheckShaderPipeline(shaderVertex, shaderFragment, shaderProgram))
        {
            glDeleteShader(shaderVertex);
            glDeleteShader(shaderFragment);
            glDeleteProgram(shaderProgram);
            return;
        }

        glDeleteShader(shaderVertex);
        glDeleteShader(shaderFragment);
        program.program = shaderProgram;
    }

    void OpenGl::DestroyShader(ShaderProgram &program)
    {
        glDeleteProgram(program.program);
    }

    void OpenGl::CreateVertexArrayBuffer(VertexArrayBuffer &arrayBuffer)
    {
        glCreateVertexArrays(1, &arrayBuffer.buffer);
    }
    void OpenGl::CreateVertexBuffer(VertexBuffer &vertexBuffer)
    {
        glCreateBuffers(1, &vertexBuffer.buffer);
        glNamedBufferData(vertexBuffer.buffer, vertexBuffer.vertices.size() * sizeof(float), vertexBuffer.vertices.data(), vertexBuffer.type);
    }
    void OpenGl::SetupVertexArrayVertexBuffer(VertexArrayBuffer &arrayBuffer, VertexBuffer &vertexBuffer, VertexLayout &layout, VertexAttribute &attribute)
    {
        glVertexArrayVertexBuffer(arrayBuffer.buffer, layout.index, vertexBuffer.buffer, layout.offset * sizeof(float), layout.stride * sizeof(float));
        glEnableVertexArrayAttrib(arrayBuffer.buffer, attribute.index);
        glVertexArrayAttribFormat(arrayBuffer.buffer, attribute.index, attribute.size, GL_FLOAT, GL_FALSE, attribute.relative * sizeof(float));
        glVertexArrayAttribBinding(arrayBuffer.buffer, attribute.index, layout.index);
    }
    void OpenGl::CreateElementBuffer(ElementBuffer &elementBuffer)
    {
        glCreateBuffers(1, &elementBuffer.buffer);
        glNamedBufferData(elementBuffer.buffer, elementBuffer.indices.size() * sizeof(unsigned int), elementBuffer.indices.data(), elementBuffer.type);
    }
    void OpenGl::SetupVertexArrayElementBuffer(VertexArrayBuffer &arrayBuffer, ElementBuffer &elementBuffer)
    {
        glVertexArrayElementBuffer(arrayBuffer.buffer, elementBuffer.buffer);
    }
    void OpenGl::BindVertexArrayBuffer(VertexArrayBuffer &arrayBuffer)
    {
        glBindVertexArray(arrayBuffer.buffer);
    }
    void OpenGl::UnbindVertexArrayBuffer()
    {
        glBindVertexArray(0);
    }
    void OpenGl::DestroyVertexArrayVertexBufferElementBuffer(VertexArrayBuffer &arrayBuffer, VertexBuffer &vertexBuffer, ElementBuffer &elementBuffer)
    {
        glDeleteVertexArrays(1, &arrayBuffer.buffer);
        glDeleteBuffers(1, &vertexBuffer.buffer);
        glDeleteBuffers(1, &elementBuffer.buffer);
    }

    void OpenGl::UseShaderProgram(ShaderProgram &shader)
    {
        glUseProgram(shader.program);
    }

    void OpenGl::DrawArrayElement(ElementBuffer &element)
    {
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(element.indices.size()), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGl::CreateTexture(TextureBuffer &textureBuffer, TextureAttribute &textureAttribute)
    {
        glCreateTextures(textureAttribute.textureType, 1, &textureBuffer.buffer);
    }
    void OpenGl::SetupTexture(TextureBuffer &textureBuffer, TextureAttribute &textureAttribute, TextureSource &textureSource)
    {
        glTextureStorage2D(textureBuffer.buffer, textureAttribute.levels, textureAttribute.internalFormat, textureAttribute.width, textureAttribute.height);
        glTextureSubImage2D(textureBuffer.buffer, 0, textureAttribute.xOffset, textureAttribute.yOffset, textureAttribute.width, textureAttribute.height, textureAttribute.format, textureAttribute.dataType, textureSource.source);
    }
    void OpenGl::SetTextureFilter(TextureBuffer &textureBuffer, TextureFilter &textureFilter){
        glTextureParameteri(textureBuffer.buffer, GL_TEXTURE_MIN_FILTER, textureFilter.min);
        glTextureParameteri(textureBuffer.buffer, GL_TEXTURE_MAG_FILTER, textureFilter.mag);
    }
    void OpenGl::SetTextureWrap(TextureBuffer &textureBuffer, TextureWrap &textureWrap){
        glTextureParameteri(textureBuffer.buffer, GL_TEXTURE_WRAP_S, textureWrap.s);
        glTextureParameteri(textureBuffer.buffer, GL_TEXTURE_WRAP_T, textureWrap.t);
        if (textureWrap.r != GL_NONE){
            glTextureParameteri(textureBuffer.buffer, GL_TEXTURE_WRAP_R, textureWrap.r);
        }
    }
    void OpenGl::GenerateTextureMipmap(TextureBuffer &textureBuffer){
        glGenerateTextureMipmap(textureBuffer.buffer);
    }
    void OpenGl::DestroyTexture(TextureBuffer &textureBuffer)
    {
        glDeleteTextures(1, &textureBuffer.buffer);
    }
    void OpenGl::BindTexture(TextureBuffer &textureBuffer, uint32_t unit)
    {
        glBindTextureUnit(unit, textureBuffer.buffer);
    }
    void OpenGl::UnbindTexture(uint32_t unit)
    {
        glBindTextureUnit(unit, 0);
    }
}
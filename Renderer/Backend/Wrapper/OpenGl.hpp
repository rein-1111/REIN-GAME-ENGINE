#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>

namespace OpenGlWrapper
{
    class OpenGl
    {
    public:
        static bool Init();
        static void SetClearColor(float r, float g, float b, float a);
        static void ClearBufferBit(int mask);
        static void Enable(GLenum mode);

        static void SetViewport(int x, int y, unsigned int width, unsigned int height);

        static void CreateShader(unsigned int &shader, const char *shaderSource, GLenum shaderType);
        static void CompileShader(unsigned int &shader);
        static void CreateProgram(unsigned int &program, unsigned int &vertexShader, unsigned int &fragmentShader);
        static void DeleteShader(unsigned int &shader);
        static void UseProgram(unsigned int &program);

        static void CreateVertexArray(unsigned int &vertexArray);
        static void CreateBuffer(unsigned int &buffers);
        static void SetBufferData(unsigned int &buffer, size_t size, const void *data, GLenum drawType);
        static void SetVertexLayout(unsigned int &vertexArray, unsigned int &vertexBuffer, unsigned int bindingIndex, unsigned int location, int count, unsigned int offset, size_t stride, GLenum dataType);
        static void SetVertexArrayIndexBuffer(unsigned int &vertexArray, unsigned int &indexBuffer);
        static void BindVertexArray(unsigned int &vertexArray);
        static void Draw(GLenum mode, unsigned int count);
        static void DrawIndexed(GLenum mode, GLenum type, const void *data, unsigned int count);

        static void BindUniformBuffer(unsigned int &program, unsigned int &uniformBuffer, const char *name, unsigned int binding);

        static void DeleteVertexArray(unsigned int &vertexArray);
        static void DeleteBuffer(unsigned int &buffer);
        static void DeleteProgram(unsigned int &program);

        static void CreateTexture(unsigned int &textureBuffer, GLenum textureType, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei levels, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, GLint wrapR);
        static void SetTextureData(unsigned int &textureBuffer, GLenum textureType, int mipLevel, int x, int y, int z, int width, int height, int depth, GLenum format, GLenum type, const void *data);
        static void GenerateTextureMipmap(unsigned int &textureBuffer);
        static void BindTexture(unsigned int &textureBuffer, int unit);
        static void DestroyTexture(unsigned int &textureBuffer);

        static GLint GetUniformLocation(unsigned int &program, const char *name);

        static void SetProgramUniform1i(unsigned int &program, int location, int value);
        static void SetProgramUniform1f(unsigned int &program, int location, float value);
        static void SetProgramUniformVec2f(unsigned int &program, int location, const float *value);
        static void SetProgramUniformVec3f(unsigned int &program, int location, const float *value);
        static void SetProgramUniformVec4f(unsigned int &program, int location, const float *value);
        static void SetProgramUniformMat3f(unsigned int &program, int location, const float *value);
        static void SetProgramUniformMat4f(unsigned int &program, int location, const float *value);
        static void SetProgramUniformTexture(unsigned int &program, int location, unsigned int &texture, int unit);

        static void CreateRenderbuffer(unsigned int &renderBuffer, GLenum format, unsigned int width, unsigned int height);
        static void ResizeRenderbuffer(unsigned int &renderBuffer, GLenum fotmat, unsigned int width, unsigned int height);
        static void DeleteRenderBuffer(unsigned int &renderBuffer);

        static void CreateFramebuffer(unsigned int &frameBuffer);
        static void SetFramebufferDrawBuffers(unsigned int &frameBuffer, const std::vector<GLenum> &attachments);
        static void AttachTexture(unsigned int &frameBuffer, unsigned int &texture, GLenum attachment, unsigned int mipLevel);
        static void AttachRenderbuffer(unsigned int &frameBuffer, unsigned int &renderBuffer, GLenum attachment);
        static bool CheckFramebuffer(unsigned int &frameBuffer);
        static void BindFramebuffer(unsigned int &frameBuffer);
        static void BindDefaultFramebuffer();
        static void DestroyFramebuffer(unsigned int &frameBuffer);
    };

    inline bool OpenGl::Init()
    {
        if (!gladLoadGL())
        {
            return false;
        }
        else
            return true;
    }

    inline void OpenGl::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    inline void OpenGl::ClearBufferBit(int mask)
    {
        glClear(mask);
    }

    inline void OpenGl::Enable(GLenum mode)
    {
        glEnable(mode);
    }

    inline void OpenGl::SetViewport(int x, int y, unsigned int width, unsigned int height)
    {
        glViewport(x, y, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    }

    inline void OpenGl::CreateShader(unsigned int &shader, const char *shaderSource, GLenum shaderType)
    {
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, nullptr);
    }
    // inline void OpenGl::CompileShader(unsigned int &shader)
    // {
    //     glCompileShader(shader);
    // }
    inline void OpenGl::CompileShader(unsigned int &shader)
    {
        glCompileShader(shader);
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> log(length);
            glGetShaderInfoLog(shader, length, nullptr, log.data());
            std::cerr << "Shader compilation failed:\n"
                      << log.data() << '\n';
        }
    }
    // inline void OpenGl::CreateProgram(unsigned int &program, unsigned int &vertexShader, unsigned int &fragmentShader)
    // {
    //     program = glCreateProgram();
    //     glAttachShader(program, vertexShader);
    //     glAttachShader(program, fragmentShader);
    //     glLinkProgram(program);
    // }
    inline void OpenGl::CreateProgram(unsigned int &program, unsigned int &vertexShader, unsigned int &fragmentShader)
{
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetProgramInfoLog(program, length, nullptr, log.data());
        std::cerr << "Program linking failed:\n" << log.data() << '\n';
    }
}
    inline void OpenGl::DeleteShader(unsigned int &shader)
    {
        glDeleteShader(shader);
    }
    inline void OpenGl::UseProgram(unsigned int &program)
    {
        glUseProgram(program);
    }
    inline void OpenGl::CreateVertexArray(unsigned int &vertexArray)
    {
        glCreateVertexArrays(1, &vertexArray);
    }
    inline void OpenGl::CreateBuffer(unsigned int &buffer)
    {
        glCreateBuffers(1, &buffer);
    }
    inline void OpenGl::SetBufferData(unsigned int &buffer, size_t size, const void *data, GLenum drawType)
    {
        glNamedBufferData(buffer, size, data, drawType);
    }
    inline void OpenGl::SetVertexLayout(unsigned int &vertexArray, unsigned int &vertexBuffer, unsigned int bindingIndex, unsigned int location, int size, unsigned int offset, size_t stride, GLenum dataType)
    {
        glVertexArrayVertexBuffer(vertexArray, bindingIndex, vertexBuffer, 0, static_cast<GLsizei>(stride));
        glEnableVertexArrayAttrib(vertexArray, location);

        if (dataType == GL_INT)
        {
            glVertexArrayAttribIFormat(vertexArray, location, size, dataType, offset);
        }
        else if (dataType == GL_FLOAT)
        {

            glVertexArrayAttribFormat(vertexArray, location, size, dataType, GL_FALSE, offset);
        }

        glVertexArrayAttribBinding(vertexArray, location, bindingIndex);
    }

    inline void OpenGl::SetVertexArrayIndexBuffer(unsigned int &vertexArray, unsigned int &indexBuffer)
    {
        glVertexArrayElementBuffer(vertexArray, indexBuffer);
    }

    inline void OpenGl::BindVertexArray(unsigned int &vertexArray)
    {
        glBindVertexArray(vertexArray);
    }

    inline void OpenGl::Draw(GLenum mode, unsigned int count)
    {
        glDrawArrays(mode, 0, count);
    }

    inline void OpenGl::DrawIndexed(GLenum mode, GLenum type, const void *data, unsigned int count)
    {
        glDrawElements(mode, count, type, data);
    }

    inline void OpenGl::CreateTexture(unsigned int &textureBuffer, GLenum textureType, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei levels, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, GLint wrapR)
    {
        glCreateTextures(textureType, 1, &textureBuffer);

        if (textureType == GL_TEXTURE_2D)
        {
            glTextureStorage2D(textureBuffer, levels, internalFormat, width, height);
        }
        else if (textureType == GL_TEXTURE_3D)
        {
            glTextureStorage3D(textureBuffer, levels, internalFormat, width, height, depth);
        }

        glTextureParameteri(textureBuffer, GL_TEXTURE_MIN_FILTER, minFilter);
        glTextureParameteri(textureBuffer, GL_TEXTURE_MAG_FILTER, magFilter);
        glTextureParameteri(textureBuffer, GL_TEXTURE_WRAP_S, wrapS);
        glTextureParameteri(textureBuffer, GL_TEXTURE_WRAP_T, wrapT);
        if (textureType == GL_TEXTURE_3D)
        {
            glTextureParameteri(textureBuffer, GL_TEXTURE_WRAP_R, wrapR);
        }
    }

    inline void OpenGl::SetTextureData(unsigned int &textureBuffer, GLenum textureType, int mipLevel, int x, int y, int z, int width, int height, int depth, GLenum format, GLenum type, const void *data)
    {
        if (textureType == GL_TEXTURE_2D)
        {
            glTextureSubImage2D(textureBuffer, mipLevel, x, y, width, height, format, type, data);
        }
        else if (textureType == GL_TEXTURE_3D)
        {
            glTextureSubImage3D(textureBuffer, mipLevel, x, y, z, width, height, depth, format, type, data);
        }
    }

    inline void OpenGl::GenerateTextureMipmap(unsigned int &textureBuffer)
    {
        glGenerateTextureMipmap(textureBuffer);
    }

    inline void OpenGl::BindTexture(unsigned int &textureBuffer, int unit)
    {
        glBindTextureUnit(unit, textureBuffer);
    }

    inline void OpenGl::DestroyTexture(unsigned int &textureBuffer)
    {
        glDeleteTextures(1, &textureBuffer);
    }

    inline void OpenGl::BindUniformBuffer(unsigned int &program, unsigned int &uniformBuffer, const char *name, unsigned int binding)
    {
        unsigned int blockIndex = glGetUniformBlockIndex(program, name);
        if (blockIndex == GL_INVALID_INDEX)
            return;

        glUniformBlockBinding(program, blockIndex, binding);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, uniformBuffer);
    }

    inline void OpenGl::DeleteVertexArray(unsigned int &vertexArray)
    {
        glDeleteVertexArrays(1, &vertexArray);
    }

    inline void OpenGl::DeleteBuffer(unsigned int &buffer)
    {
        glDeleteBuffers(1, &buffer);
    }

    inline void OpenGl::DeleteProgram(unsigned int &program)
    {
        glDeleteProgram(program);
    }

    inline GLint OpenGl::GetUniformLocation(unsigned int &program, const char *name)
    {
        return glGetUniformLocation(program, name);
    }

    inline void OpenGl::SetProgramUniform1i(unsigned int &program, int location, int value)
    {
        glProgramUniform1i(program, location, value);
    }

    inline void OpenGl::SetProgramUniform1f(unsigned int &program, int location, float value)
    {
        glProgramUniform1f(program, location, value);
    }

    inline void OpenGl::SetProgramUniformVec2f(unsigned int &program, int location, const float *value)
    {
        glProgramUniform2fv(program, location, 1, value);
    }

    inline void OpenGl::SetProgramUniformVec3f(unsigned int &program, int location, const float *value)
    {
        glProgramUniform3fv(program, location, 1, value);
    }

    inline void OpenGl::SetProgramUniformVec4f(unsigned int &program, int location, const float *value)
    {
        glProgramUniform4fv(program, location, 1, value);
    }

    inline void OpenGl::SetProgramUniformMat3f(unsigned int &program, int location, const float *value)
    {
        glProgramUniformMatrix3fv(program, location, 1, GL_FALSE, value);
    }

    inline void OpenGl::SetProgramUniformMat4f(unsigned int &program, int location, const float *value)
    {
        glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, value);
    }

    inline void OpenGl::SetProgramUniformTexture(unsigned int &program, int location, unsigned int &texture, int unit)
    {
        glBindTextureUnit(unit, texture);
        glProgramUniform1i(program, location, unit);
    }

    inline void OpenGl::CreateRenderbuffer(unsigned int &renderBuffer, GLenum format, unsigned int width, unsigned int height)
    {
        glCreateRenderbuffers(1, &renderBuffer);
        glNamedRenderbufferStorage(renderBuffer, format, width, height);
    }

    inline void OpenGl::ResizeRenderbuffer(unsigned int &renderBuffer, GLenum format, unsigned int width, unsigned int height)
    {
        glNamedRenderbufferStorage(renderBuffer, format, width, height);
    }

    inline void OpenGl::DeleteRenderBuffer(unsigned int &renderBuffer)
    {
        glDeleteRenderbuffers(1, &renderBuffer);
    }

    inline void OpenGl::CreateFramebuffer(unsigned int &frameBuffer)
    {
        glCreateFramebuffers(1, &frameBuffer);
    }

    inline void OpenGl::SetFramebufferDrawBuffers(unsigned int &frameBuffer, const std::vector<GLenum> &attachments)
    {
        glNamedFramebufferDrawBuffers(frameBuffer, static_cast<GLsizei>(attachments.size()), attachments.data());
    }

    inline void OpenGl::AttachTexture(unsigned int &frameBuffer, unsigned int &texture, GLenum attachment, unsigned int mipLevel)
    {
        glNamedFramebufferTexture(frameBuffer, attachment, texture, mipLevel);
    }

    inline void OpenGl::AttachRenderbuffer(unsigned int &frameBuffer, unsigned int &renderBuffer, GLenum attachment)
    {
        glNamedFramebufferRenderbuffer(frameBuffer, attachment, GL_RENDERBUFFER, renderBuffer);
    }

    inline bool OpenGl::CheckFramebuffer(unsigned int &frameBuffer)
    {
        return glCheckNamedFramebufferStatus(frameBuffer, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }

    inline void OpenGl::BindFramebuffer(unsigned int &frameBuffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    }

    inline void OpenGl::BindDefaultFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    inline void OpenGl::DestroyFramebuffer(unsigned int &frameBuffer)
    {
        glDeleteFramebuffers(1, &frameBuffer);
        frameBuffer = 0;
    }
}
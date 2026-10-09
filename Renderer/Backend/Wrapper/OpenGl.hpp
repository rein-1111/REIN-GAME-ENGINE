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

    inline void OpenGl::CreateShader(unsigned int &shader, const char *shaderSource, GLenum shaderType)
    {
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, nullptr);
    }
    inline void OpenGl::CompileShader(unsigned int &shader)
    {
        glCompileShader(shader);
    }
    inline void OpenGl::CreateProgram(unsigned int &program, unsigned int &vertexShader, unsigned int &fragmentShader)
    {
        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
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
        glVertexArrayAttribFormat(vertexArray, location, size, dataType, GL_FALSE, offset);
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
}
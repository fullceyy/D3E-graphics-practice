#pragma once
#include "glad/glad.h"
#include <vector>

namespace D3EGraphics
{
    class VertexBufferObject
    {
    private:
        GLuint m_VBO;
    public:
        VertexBufferObject(const std::vector<float>& data);
        ~VertexBufferObject();

        void bind() const;
        void unbind() const;
    };
}

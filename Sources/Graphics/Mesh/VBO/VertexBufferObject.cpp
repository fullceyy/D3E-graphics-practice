#include "VertexBufferObject.hpp"

namespace D3EGraphics
{
    VertexBufferObject::VertexBufferObject(const std::vector<float>& data)
    {
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER,
                    data.size() * sizeof(float),
                    data.data(),
                    GL_STATIC_DRAW);
    }

    VertexBufferObject::~VertexBufferObject()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void VertexBufferObject::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }

    void VertexBufferObject::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

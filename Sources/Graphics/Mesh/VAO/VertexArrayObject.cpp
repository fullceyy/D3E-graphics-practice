#include "VertexArrayObject.hpp"

namespace D3EGraphics
{
    VertexArrayObject::VertexArrayObject()
    {
        glGenVertexArrays(1, &m_VAO);
    }

    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &m_VAO);
    }

    void VertexArrayObject::bind() const
    {
        glBindVertexArray(m_VAO);
    }

    void VertexArrayObject::unbind() const
    {
        glBindVertexArray(0);
    }
}

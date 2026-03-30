#include "ElementBufferObject.hpp"
#include <vector>

namespace D3EGraphics
{
    ElementBufferObject::ElementBufferObject(const std::vector<unsigned int>& data)
    {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW);
    }

    ElementBufferObject::~ElementBufferObject()
    {
        glDeleteBuffers(1, &m_EBO);
    }

    void ElementBufferObject::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    }

    void ElementBufferObject::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

#include "Mesh.hpp"
#include "VAO/VertexArrayObject.hpp"
#include "Vertex.hpp"

namespace D3EGraphics
{
    Mesh::Mesh(const VertexLayoutDesc& desc, const std::vector<float>& data, const std::vector<unsigned int>& indices)
    : m_VertexBufferObject(data),
        m_ElementBufferObject(indices),
        m_VertexLayoutDesc(desc),
        m_MeshData(data),
        m_MeshIndices(indices)
    {
    }


    Mesh::~Mesh()
    {
    }

    void Mesh::setup()
    {
        m_VertexArrayObject.bind();
        m_VertexBufferObject.bind();
        m_ElementBufferObject.bind();

        unsigned int idx = 0;
        for(auto& a : m_VertexLayoutDesc)
        {
            glVertexAttribPointer(idx,
                    a.get_count(),
                    AttribTypeToOGLType(a.data_type),
                    a.normalized ? GL_TRUE : GL_FALSE,
                    m_VertexLayoutDesc.get_stride(),
                    (const void*)(a.offset));
            glEnableVertexAttribArray(idx);
            idx++;
        }

        m_VertexArrayObject.unbind();
    }

    void Mesh::draw()
    {
        m_VertexArrayObject.bind();
        glDrawElements(GL_TRIANGLES, m_MeshIndices.size(), GL_UNSIGNED_INT, 0);
        m_VertexArrayObject.unbind();
    }
}

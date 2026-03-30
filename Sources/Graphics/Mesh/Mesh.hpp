#pragma once
#include "glad/glad.h"
#include "Vertex.hpp"
#include "VAO/VertexArrayObject.hpp"
#include "VBO/VertexBufferObject.hpp"
#include "EBO/ElementBufferObject.hpp"


namespace D3EGraphics
{
    class Mesh
    {
        private:
            VertexArrayObject m_VertexArrayObject;
            VertexBufferObject m_VertexBufferObject;
            ElementBufferObject m_ElementBufferObject;

            VertexLayoutDesc m_VertexLayoutDesc;

            std::vector<float> m_MeshData;
            std::vector<unsigned int> m_MeshIndices;
        public:
            Mesh(const VertexLayoutDesc& desc, const std::vector<float>& data, const std::vector<unsigned int>& indices);
            ~Mesh();

            void setup();
            void draw();
    };
}

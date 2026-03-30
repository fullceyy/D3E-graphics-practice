#pragma once
#include "glad/glad.h"
#include <vector>

namespace D3EGraphics
{
    class ElementBufferObject
    {
        private:
            GLuint m_EBO;
        public:
            ElementBufferObject(const std::vector<unsigned int>& data);
            ~ElementBufferObject();

            void bind() const;
            void unbind() const;
    };
}

#pragma once
#include "glad/glad.h"

namespace D3EGraphics
{
    class VertexArrayObject
    {
    	private:
            GLuint m_VAO;
    	public:
    		VertexArrayObject();
    		~VertexArrayObject();

    		void bind() const;
    		void unbind() const;
    };
}

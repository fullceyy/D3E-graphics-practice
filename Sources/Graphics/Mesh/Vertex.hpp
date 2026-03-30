#pragma once
#include <cstddef>
#include <vector>
#include "glad/glad.h"
// a single vertex may consist of up to 5 different data
// e.g. Pos, Normals, UV, Tangent, Bitangent
// struct VertexLayout
// {
//     // it stores indexes to attribs that are available
//     std::vector<Attrib> m_Attribs;
//     // total count of data in singular Vertex
//     unsigned int m_Stride = 0;
// };
enum AttribType
{
    D3E_FLOAT2,
    D3E_FLOAT3,
    D3E_UINT,
    D3E_NONE,
};

namespace D3EGraphics
{
    static GLenum AttribTypeToOGLType(AttribType type)
    {
        switch(type)
        {
            case AttribType::D3E_FLOAT2:
                return GL_FLOAT;
                break;
            case AttribType::D3E_FLOAT3:
                return GL_FLOAT;
                break;
            case AttribType::D3E_UINT:
                return GL_UNSIGNED_INT;
                break;
            case AttribType::D3E_NONE:
                return GL_NONE;
                break;
        }
    }


    static size_t get_size(AttribType type)
    {
        switch(type)
        {
            case AttribType::D3E_FLOAT3:
                return 4 * 3;
                break;
            case AttribType::D3E_FLOAT2:
                return 4 * 2;
                break;
            case AttribType::D3E_UINT:
                return 4;
                break;
            case AttribType::D3E_NONE:
                break;
        }
        return 0;
    }

    struct Attrib
    {
        AttribType data_type = D3E_NONE;
        bool normalized = false;
        unsigned int offset = 0;
        size_t size = 0;

        Attrib(AttribType dt, bool n)
        : data_type(dt), normalized(n), size(get_size(dt))
        {}

        unsigned int get_count()
        {
            switch(data_type)
            {
                case AttribType::D3E_FLOAT2:
                    return 2;
                    break;
                case AttribType::D3E_FLOAT3:
                    return 3;
                    break;
                case AttribType::D3E_UINT:
                    return 1;
                    break;
                case AttribType::D3E_NONE:
                    return 0;
                    break;
            }
        }
    };

    class VertexLayoutDesc
    {
        private:
            unsigned int m_Stride;
            std::vector<Attrib> m_Attribs;

            void CalculateOffsetsAndStride()
            {
                m_Stride = 0;
                for(auto& a : m_Attribs)
                {
                    a.offset = m_Stride;
                    m_Stride += get_size(a.data_type);
                }
            }
        public:
            VertexLayoutDesc() {}
            VertexLayoutDesc(const std::initializer_list<Attrib>& attribs)
            : m_Attribs(attribs)
            {
                // m_Layout.m_Attribs = attribs;
                CalculateOffsetsAndStride();
            }

            ~VertexLayoutDesc() = default;

            const std::vector<Attrib>& get_attribs() { return m_Attribs; }
            const unsigned int get_stride() { return m_Stride; }

            std::vector<Attrib>::iterator begin() { return m_Attribs.begin(); }
            std::vector<Attrib>::iterator end() { return m_Attribs.end(); }
    };
}

/*add({
    {D3E_FLOAT, 3},
    {D3E_FLOAT, 3}
})*/

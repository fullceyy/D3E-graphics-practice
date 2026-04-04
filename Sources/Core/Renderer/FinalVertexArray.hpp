#pragma once
#include "../../Graphics/Mesh/Vertex.hpp"
#include <memory>

#define BINDING_IDX_ZERO 0
#define D3E_CREATE_VB(name, type, data) std::unique_ptr<D3E::VertexBuffer<type>> name = std::make_unique<D3E::VertexBuffer<type>>(data)
#define D3E_CREATE_EB(name, data) std::unique_ptr<D3E::ElementBuffer> name = std::make_unique<D3E::ElementBuffer>(data)

namespace D3E
{
    typedef enum
    {
        ELEMENT,
        VERTEX,
        NONE
    } bufferType;

    class RawBuffer
    {
        protected:
            GLuint mBufferId;
            bufferType mType;
            GLsizei mCount;
        public:
            RawBuffer()
            : mType(NONE)
            {
                glCreateBuffers(1, &mBufferId);
            }

            virtual ~RawBuffer()
            {
                glDeleteBuffers(1, &mBufferId);
            }

            bufferType& get_tag()
            {
                return mType;
            }

            GLsizei& get_count()
            {
                return mCount;
            }

            virtual void setup(GLuint& vaoidx, size_t stride) = 0;
    };

    template<typename T>
    class VertexBuffer : public RawBuffer
    {
        private:
            std::vector<T> mData;
        public:
            VertexBuffer(const std::vector<T>& data)
            : mData(data)
            {
                mCount = mData.size();
                glNamedBufferStorage(mBufferId, mData.size() * sizeof(T), mData.data(), GL_DYNAMIC_STORAGE_BIT);
            }

            void setup(GLuint& vaoidx, size_t stride) override
            {
                glVertexArrayVertexBuffer(vaoidx, 0, mBufferId, 0, stride);
                mType = VERTEX;
            }
    };

    class ElementBuffer : public RawBuffer
    {
        private:
            std::vector<GLuint> mData;
        public:
            ElementBuffer(const std::vector<GLuint>& data)
            : mData(data)
            {
                mCount = mData.size();
                glNamedBufferStorage(mBufferId, mData.size() * sizeof(GLuint), mData.data(), GL_DYNAMIC_STORAGE_BIT);
            }

            void setup(GLuint& vaoidx, size_t stride) override
            {
                glVertexArrayElementBuffer(vaoidx, mBufferId);
                mType = ELEMENT;
            }
    };


    class FinalVertexArray
    {
        public:
            friend class RenderVertexArray;
            FinalVertexArray(D3EGraphics::VertexLayoutDesc layout)
            : mLayout(layout)
            {
                glCreateVertexArrays(1, &mId);
            }

            ~FinalVertexArray()
            {
                glDeleteVertexArrays(1, &mId);
            }

            void PushBuffer(std::unique_ptr<RawBuffer> buffer)
            {
                mBuffers.emplace_back(std::move(buffer));
            }

            void finalize()
            {
                for(auto& b : mBuffers)
                {
                    b->setup(mId, mLayout.get_stride());
                    if(b->get_tag() == ELEMENT) mIndexCount = b->get_count();
                }

                uint32_t idx = 0;
                for(auto& a : mLayout)
                {
                    glEnableVertexArrayAttrib(mId, idx);
                    glVertexArrayAttribFormat(mId,
                                              idx,
                                              a.get_count(),
                                              D3EGraphics::AttribTypeToOGLType(a.data_type),
                                              a.normalized ? GL_TRUE : GL_FALSE,
                                              a.offset);
                    glVertexArrayAttribBinding(mId, idx, 0);
                    idx++;
                }
            }

        private:
            GLuint mId;
            D3EGraphics::VertexLayoutDesc mLayout;
            std::vector<std::unique_ptr<RawBuffer>> mBuffers;
            GLsizei mIndexCount;
    };
};

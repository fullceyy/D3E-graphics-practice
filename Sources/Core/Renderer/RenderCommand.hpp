#pragma once
#include <memory>
#include "FinalVertexArray.hpp"
// #include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Shader/Shader.hpp"
#include "glm/glm.hpp"

namespace D3E
{
    class RenderCommand
    {
    public:
        virtual ~RenderCommand() {}
        virtual void execute() = 0;
    };

    class RenderVertexArray : public RenderCommand
    {
    public:
        RenderVertexArray(std::shared_ptr<FinalVertexArray> fva, std::shared_ptr<D3EGraphics::Shader> shader, glm::mat4& model);
        ~RenderVertexArray() { mFva = nullptr; }

        void execute() override;
    private:
        std::shared_ptr<FinalVertexArray> mFva;
        std::shared_ptr<D3EGraphics::Shader> mShader;
        glm::mat4& mModel;
    };
};

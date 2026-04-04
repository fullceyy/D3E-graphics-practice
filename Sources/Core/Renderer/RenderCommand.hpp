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
            virtual void execute(glm::mat4, glm::mat4, glm::mat4) = 0;
    };

    class RenderVertexArray : public RenderCommand
    {
        public:
            // RenderVertexArray(std::shared_ptr<D3EGraphics::Mesh> mesh, std::shared_ptr<D3EGraphics::Shader> shader);
            RenderVertexArray(FinalVertexArray& fva, std::shared_ptr<D3EGraphics::Shader> shader);
            ~RenderVertexArray() {}

            void execute(glm::mat4 model, glm::mat4 projection, glm::mat4 view) override;
        private:
            // std::shared_ptr<D3EGraphics::Mesh> m_Mesh;
            FinalVertexArray& mFva;
            std::shared_ptr<D3EGraphics::Shader> mShader;
            glm::mat4 mModel;
    };
};

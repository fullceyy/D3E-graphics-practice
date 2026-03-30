#pragma once
#include <memory>
#include "Graphics/Mesh/Mesh.hpp"
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
            RenderVertexArray(std::shared_ptr<D3EGraphics::Mesh> mesh, std::shared_ptr<D3EGraphics::Shader> shader);
            ~RenderVertexArray() {}

            void execute(glm::mat4 model, glm::mat4 projection, glm::mat4 view) override;
        private:
            std::shared_ptr<D3EGraphics::Mesh> m_Mesh;
            std::shared_ptr<D3EGraphics::Shader> m_Shader;
            glm::mat4 m_Model;
    };
};

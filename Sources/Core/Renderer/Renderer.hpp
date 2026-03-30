// Renderer.hpp
#pragma once
#include <vector>
#include <memory>
#include "Core/Renderer/RenderCommand.hpp"
#include "glm/glm.hpp"

namespace D3E
{
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void set_camera_matrices(glm::mat4 view, glm::mat4 projection);
        void submit(std::shared_ptr<RenderCommand> cmd, glm::mat4 model);
        void flush();

    private:
        struct RenderEntry
        {
            std::shared_ptr<RenderCommand> cmd;
            glm::mat4 model;
        };

        std::vector<RenderEntry> m_Queue;
        glm::mat4 m_View;
        glm::mat4 m_Projection;
    };
}

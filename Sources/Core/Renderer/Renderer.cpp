#include "Renderer.hpp"

namespace D3E
{
    void Renderer::set_camera_matrices(glm::mat4 view, glm::mat4 projection)
    {
        m_View = view;
        m_Projection = projection;
    }

    void Renderer::submit(std::shared_ptr<RenderCommand> cmd, glm::mat4 model)
    {
        m_Queue.push_back({cmd, model});
    }

    void Renderer::flush()
    {
        for (auto& [cmd, model] : m_Queue)
            cmd->execute(model, m_Projection, m_View);
        m_Queue.clear();
    }
}

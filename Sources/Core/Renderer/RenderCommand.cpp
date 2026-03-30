#include "RenderCommand.hpp"

#include <memory>

namespace D3E
{
    RenderVertexArray::RenderVertexArray(std::shared_ptr<D3EGraphics::Mesh> mesh, std::shared_ptr<D3EGraphics::Shader> shader)
    : m_Mesh(mesh), m_Shader(shader), m_Model(glm::mat4(1.f))
    {
    }

    void RenderVertexArray::execute(glm::mat4 model, glm::mat4 projection, glm::mat4 view)
    {
        // std::shared_ptr<Mesh> mLocked = m_Mesh.lock();
        // std::shared_ptr<Shader> sLocked = m_Shader.lock();

        // if(mLocked && sLocked)
        // {
            // mLocked->setup();
            m_Shader->bind();
            m_Shader->mat4_uniform("model", model);
            m_Shader->mat4_uniform("view", view);
            m_Shader->mat4_uniform("projection", projection);
            // glUniformMatrix4fv(glGetUniformLocation(m_Shader->get_program(), "model"), 1, GL_FALSE, &model[0][0]);
            // glUniformMatrix4fv(glGetUniformLocation(m_Shader->get_program(), "view"), 1, GL_FALSE, &view[0][0]);
            // glUniformMatrix4fv(glGetUniformLocation(m_Shader->get_program(), "projection"), 1, GL_FALSE, &projection[0][0]);
            m_Mesh->draw();
        // }
    }

};

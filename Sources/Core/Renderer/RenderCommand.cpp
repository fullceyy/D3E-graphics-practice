#include "RenderCommand.hpp"

#include <memory>

namespace D3E
{
    // RenderVertexArray::RenderVertexArray(std::shared_ptr<D3EGraphics::Mesh> mesh, std::shared_ptr<D3EGraphics::Shader> shader)
    // : m_Mesh(mesh), m_Shader(shader), m_Model(glm::mat4(1.f))
    // {
    // }

    RenderVertexArray::RenderVertexArray(FinalVertexArray& fva, std::shared_ptr<D3EGraphics::Shader> shader)
    : mFva(fva), mShader(shader), mModel(glm::mat4(1.f))
    {
    }


    void RenderVertexArray::execute(glm::mat4 model, glm::mat4 projection, glm::mat4 view)
    {
        // m_Shader->bind();
        // m_Shader->mat4_uniform("model", model);
        // m_Shader->mat4_uniform("view", view);
        // m_Shader->mat4_uniform("projection", projection);
        // m_Mesh->draw();
        mShader->bind();
        glBindVertexArray(mFva.mId);
        mShader->mat4_uniform("model", model);
        mShader->mat4_uniform("view", view);
        mShader->mat4_uniform("projection", projection);
        glDrawElements(GL_TRIANGLES, mFva.mIndexCount, GL_UNSIGNED_INT, 0);
    }

};

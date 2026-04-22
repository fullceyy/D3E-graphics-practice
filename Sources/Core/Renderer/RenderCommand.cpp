#include "RenderCommand.hpp"
#include "../Engine/Engine.hpp"
#include <memory>

using namespace D3E;

RenderVertexArray::RenderVertexArray(std::shared_ptr<FinalVertexArray> fva, std::shared_ptr<D3EGraphics::Shader> shader, glm::mat4& model)
: mFva(fva), mShader(shader), mModel(model)
{
}

void RenderVertexArray::execute()
{
    mShader->bind();
    glBindVertexArray(mFva->mId);
    mShader->mat4_uniform("model", mModel);
    mShader->mat4_uniform("view", Engine::GetInstance().GetCamera().ViewMatrix());
    mShader->mat4_uniform("projection", Engine::GetInstance().GetCamera().ProjectionMatrix());
    glDrawElements(GL_TRIANGLES, mFva->mIndexCount, GL_UNSIGNED_INT, 0);
    mShader->unbind();
    glBindVertexArray(0);
}


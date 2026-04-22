#include "Renderer.hpp"

using namespace D3E;

void Renderer::Initialize()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glClearColor(.1f, .1f, .1f, 1.f);
}

void Renderer::Submit(std::unique_ptr<RenderCommand> command)
{
    mCommands.push_back(std::move(command));
}

void Renderer::Flush()
{
    for(auto& cmd : mCommands)
        cmd->execute();
    mCommands.clear();
}

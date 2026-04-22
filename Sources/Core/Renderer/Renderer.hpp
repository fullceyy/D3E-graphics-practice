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
    private:
        std::vector<std::unique_ptr<RenderCommand>> mCommands;
    public:
        Renderer() {}
        ~Renderer() {}

        void Initialize();
        void Submit(std::unique_ptr<RenderCommand> command);
        void Flush();
    };
}


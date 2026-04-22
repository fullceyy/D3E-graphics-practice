#include "Core/Engine/Engine.hpp"
#include "Core/Engine/CubeDisplay.hpp"
#include <stdexcept>
#include <format>

int main(void)
{
    D3E::CubeDisplayApplication* new_app = new D3E::CubeDisplayApplication();
    if(!new_app)
        throw std::runtime_error(std::format("{}", "Could not create application!"));
    D3E::Engine& engine = D3E::Engine::GetInstance();
    engine.Run(new_app);
}
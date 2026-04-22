#pragma once
#include "Application.hpp"
#include "glm/glm.hpp"
#include "../Renderer/FinalVertexArray.hpp"
#include "Graphics/Shader/Shader.hpp"

namespace D3E
{
    class CubeDisplayApplication : public Application
    {
    private:
        std::shared_ptr<FinalVertexArray> mFva;
        std::shared_ptr<D3EGraphics::Shader> mShader;
        glm::mat4 model {1.f};

    public:
        CubeDisplayApplication();
        ~CubeDisplayApplication();

        void Initialize() override;
        void Shutdown() override;

        void Update() override;
        void Render() override;

    };
}
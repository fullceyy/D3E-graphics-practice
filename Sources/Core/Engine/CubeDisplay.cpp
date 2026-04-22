#include "CubeDisplay.hpp"
#include "Engine.hpp"
#include "Graphics/Mesh/StaticMeshShapes/Cube.hpp"
#include "ext/matrix_transform.hpp"

using namespace D3E;

CubeDisplayApplication::CubeDisplayApplication()
{
}

CubeDisplayApplication::~CubeDisplayApplication()
{
}

void CubeDisplayApplication::Initialize()
{
    mShader = std::make_shared<D3EGraphics::Shader>("Assets/Shaders/Basic/Basic.vert", "Assets/Shaders/Basic/Basic.frag");

    D3E_CREATE_VB(vb, float, cube_vertex_values);
    D3E_CREATE_EB(eb, cube_indices_values);
    D3EGraphics::VertexLayoutDesc layout = {
        {D3E_FLOAT3, false},
        {D3E_FLOAT3, false},
        {D3E_FLOAT3, false},
    };
    mFva = std::make_shared<FinalVertexArray>(layout);
    mFva->PushBuffer(std::move(vb));
    mFva->PushBuffer(std::move(eb));
    mFva->finalize();

}

void CubeDisplayApplication::Shutdown()
{
}

void CubeDisplayApplication::Update()
{
    model = glm::rotate(model, glm::radians(45.f) * Engine::GetInstance().GetDeltaTime(), glm::vec3(0.f, 1.f, 0.f));
}

void CubeDisplayApplication::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Engine::GetInstance().GetRenderer().Submit(
        std::make_unique<RenderVertexArray>(mFva, mShader, model)
    );
}
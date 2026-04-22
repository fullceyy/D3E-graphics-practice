#include "Engine.hpp"
#include "../Input/Input.hpp"

using namespace D3E;

Engine& Engine::GetInstance()
{
    static Engine Instance_;
    return Instance_;
}

Renderer& Engine::GetRenderer()
{
    return mRenderer;
}

Camera& Engine::GetCamera()
{
    return mCamera;
}

void Engine::Initialize()
{
    if(mWindow.Initialize(CoreWindowPropeties()))
    {
        mRenderer.Initialize();
        mCamera.SetAspectRatio(static_cast<float>(mWindow.GetWidth()), static_cast<float>(mWindow.GetHeight()));
        Input::Initialize(mWindow.GetWindow());
        mIsRunning = true;
        mApp->Initialize();
    }
}

void Engine::Render()
{
    mApp->Render();
    mRenderer.Flush();
    mWindow.SwapBuffers();
}

void Engine::Update()
{
    float currentFrame = glfwGetTime();
    mDeltaTime = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    mWindow.PollEvents();
    mApp->Update();

    if(Input::isKeyPressed(GLFW_KEY_W)) mCamera.ProcessInput(move_direction::FORWARD,   mDeltaTime);
    if(Input::isKeyPressed(GLFW_KEY_S)) mCamera.ProcessInput(move_direction::BACKWARD,  mDeltaTime);
    if(Input::isKeyPressed(GLFW_KEY_A)) mCamera.ProcessInput(move_direction::LEFT,      mDeltaTime);
    if(Input::isKeyPressed(GLFW_KEY_D)) mCamera.ProcessInput(move_direction::RIGHT,     mDeltaTime);

    if(Input::isKeyPressed(GLFW_KEY_ESCAPE))
        mIsRunning = false;
}

void Engine::Run(Application* app)
{
    if(app)
        mApp = app;

    Engine::Initialize();

    while(mIsRunning)
    {
        Engine::Update();
        Engine::Render();
    }
    Shutdown();
}

void Engine::Shutdown()
{
    mApp->Shutdown();
    delete mApp;
    glfwSetWindowShouldClose(mWindow.GetWindow(), true);
}
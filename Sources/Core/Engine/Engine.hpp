#pragma once
#include "../Window/Window.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Camera/Camera.hpp"
#include "../Input/Input.hpp"
#include "Application.hpp"

namespace D3E
{
    class Engine
    {
    private:
        Engine() = default;
        ~Engine() = default;

        float mLastFrame = 0.f;
        float mDeltaTime = 0.f;

        Window mWindow;
        Renderer mRenderer;
        Camera mCamera;
        
        bool mIsRunning = false;
        Application* mApp = nullptr;
    public:
        static Engine& GetInstance();
        Renderer& GetRenderer();
        Camera& GetCamera();

        void Initialize();
        void Render();

        void Run(Application* app);
        void Update();
        void Shutdown();

        inline float GetDeltaTime() const { return mDeltaTime; }
    };
}
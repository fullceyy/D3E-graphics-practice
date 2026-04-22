#pragma once

namespace D3E
{
    class Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;
    };
}
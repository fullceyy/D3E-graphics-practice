#pragma once
#include "GLFW/glfw3.h"

namespace D3E
{
    struct ImGuiWindowProps
    {
        bool MoveTitleBarOnly = true;
        bool isDockingEnabled = false;
        bool isViewportEnabled = false;

        ImGuiWindowProps(bool mtbo = true, bool ide = false, bool ive = false)
        : MoveTitleBarOnly(mtbo), isDockingEnabled(ide), isViewportEnabled(ive)
        {
        }
    };

    class ImGuiWindow
    {
    private:
        GLFWwindow* mWindow;
    public:
        ImGuiWindow(GLFWwindow* window) : mWindow(window) {}
        ~ImGuiWindow() {}

        void create(const ImGuiWindowProps& props);
        void shutdown();

        void handle_events();

        void begin_render();
        void end_render();

        bool capture_mouse();
        bool capture_keyboard();
    };
};

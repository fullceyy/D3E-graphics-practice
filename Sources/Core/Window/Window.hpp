#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace D3E
{
    struct CoreWindowPropeties
    {
        int m_Width, m_Height, m_MinWidth, m_MinHeight;
        bool m_Resizable;
        const char* title = "D3E App";

        CoreWindowPropeties();
    };

    class Window
    {
	private:
		void SetStartPosition(const GLFWvidmode*);
		void SetViewport(const GLFWvidmode*) const;

		CoreWindowPropeties m_CoreWindowProps;
		GLFWwindow* mWindow = nullptr;
		bool mOpen = false;
	public:
		Window() = default;
		~Window();
		
		[[nodiscard]] bool Initialize(const CoreWindowPropeties& props);

		inline GLFWwindow* GetWindow() const { return mWindow; }
		inline int GetWidth()  const { return m_CoreWindowProps.m_Width; }
		inline int GetHeight() const { return m_CoreWindowProps.m_Height; }
		
		inline bool Open() const { return mOpen; }
		inline void Close() { mOpen = false; glfwWindowShouldClose(mWindow); }

		void PollEvents() const;
		void SwapBuffers() const;
    };
};

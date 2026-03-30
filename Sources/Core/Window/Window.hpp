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
		[[nodiscard]] bool initialize(const CoreWindowPropeties& props);

		void set_start_position(const GLFWvidmode*);
		void set_viewport(const GLFWvidmode*) const;

		CoreWindowPropeties m_CoreWindowProps;
		GLFWwindow* m_Window;
	public:
		Window();
		~Window();

		GLFWwindow* get_window() const { return m_Window; }
		int get_width() const { return m_CoreWindowProps.m_Width; }
		int get_height() const { return m_CoreWindowProps.m_Height; }
    };
};

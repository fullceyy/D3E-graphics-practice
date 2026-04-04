#include "Window.hpp"
#include "glfw3.h"
#include <iostream>

namespace D3E
{
    CoreWindowPropeties::CoreWindowPropeties()
    : m_Width(800), m_Height(600), m_MinWidth(320), m_MinHeight(200), m_Resizable(false)
    {}

    static void resizeCallback(GLFWwindow* window, int width, int height)
    {
    	glViewport(0, 0, width, height);
    }

    Window::Window()
    : m_Window(nullptr)
    {
    	if (!initialize(CoreWindowPropeties()))
    	{
    		std::cout << "WINDOW-CLASS::WINDOW::Window initialization failed!\n";
    		return;
    	}
    }

    Window::~Window()
    {
    	glfwDestroyWindow(m_Window);
    	glfwTerminate();
    }

    bool Window::initialize(const CoreWindowPropeties& props)
    {
        m_CoreWindowProps = props;
    	if(!glfwInit())
        {
            std::cout << "Failed to glfwInit()!\n";
            return -1;
        }

    	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    	glfwWindowHint(GLFW_RESIZABLE, (props.m_Resizable == true ? GLFW_TRUE : GLFW_FALSE));
    	if (m_Window = glfwCreateWindow(props.m_Width, props.m_Height, props.title, nullptr, nullptr); !m_Window)
    	{
    		std::cout << "m_Window == NULL in init()!\n";
    		return false;
    	}

    	glfwMakeContextCurrent(m_Window);

    	set_start_position(glfwGetVideoMode(glfwGetPrimaryMonitor()));

    	glfwSetWindowUserPointer(m_Window, this);

    	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    	{
    		std::cout << "WINDOW-CLASS::INITIALIZEWINDOW::GLAD failed!\n";
    		return false;
    	}

    	// Window::set_viewport(glvm);
    	glfwSetFramebufferSizeCallback(m_Window, resizeCallback);
    	return true;
    }

    void Window::set_start_position(const GLFWvidmode* glvm)
    {
    	int xPos = (glvm->width / 2) - (m_CoreWindowProps.m_Width / 2);
    	int yPos = (glvm->height / 2) - (m_CoreWindowProps.m_Width / 2);
    	glfwSetWindowPos(m_Window, xPos, yPos);
    }

    void Window::set_viewport(const GLFWvidmode* glvm) const
    {
    		glViewport(0, 0, m_CoreWindowProps.m_Width, m_CoreWindowProps.m_Height);
    }
};

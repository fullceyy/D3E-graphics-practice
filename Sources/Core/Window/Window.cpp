#include "Window.hpp"
#include <iostream>

using namespace D3E;

static void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

CoreWindowPropeties::CoreWindowPropeties()
: m_Width(800), m_Height(600), m_MinWidth(320), m_MinHeight(200), m_Resizable(false)
{}

Window::~Window()
{
	if(mWindow)
		glfwDestroyWindow(mWindow);
	glfwTerminate();
}

bool Window::Initialize(const CoreWindowPropeties& props)
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
	if (mWindow = glfwCreateWindow(props.m_Width, props.m_Height, props.title, nullptr, nullptr); !mWindow)
	{
		std::cout << "mWindow == NULL in init()!\n";
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	SetStartPosition(glfwGetVideoMode(glfwGetPrimaryMonitor()));

	glfwSetWindowUserPointer(mWindow, this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "WINDOW-CLASS::INITIALIZEWINDOW::GLAD failed!\n";
		return false;
	}

	// Window::SetViewport(glvm);
	glfwSetFramebufferSizeCallback(mWindow, resizeCallback);
	mOpen = true;
	return true;
}

void Window::SetStartPosition(const GLFWvidmode* glvm)
{
	int xPos = (glvm->width / 2) - (m_CoreWindowProps.m_Width / 2);
	int yPos = (glvm->height / 2) - (m_CoreWindowProps.m_Width / 2);
	glfwSetWindowPos(mWindow, xPos, yPos);
}

void Window::SetViewport(const GLFWvidmode* glvm) const
{
		glViewport(0, 0, m_CoreWindowProps.m_Width, m_CoreWindowProps.m_Height);
}

void Window::PollEvents() const
{
	glfwPollEvents();
}

void Window::SwapBuffers() const
{
	glfwSwapBuffers(mWindow);
}
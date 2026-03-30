#include "InputSystem.hpp"
#include "glfw3.h"
#include <algorithm>

namespace D3E
{
    InputSystem::InputSystem(GLFWwindow* window_ptr)
    : m_WindowPtr(window_ptr)
    {
        glfwSetWindowUserPointer(m_WindowPtr, this);
    }

    bool InputSystem::is_key_pressed(int key)
    {
    	return std::find(m_KeysPressed.begin(), m_KeysPressed.end(), key) != m_KeysPressed.end();
    }

    bool InputSystem::is_key_held(int key)
    {
    	return std::find(m_KeysHolding.begin(), m_KeysHolding.end(), key) != m_KeysHolding.end();
    }

    bool InputSystem::is_key_released(int key)
    {
    	return std::find(m_KeysReleased.begin(), m_KeysReleased.end(), key) != m_KeysReleased.end();
    }

    bool InputSystem::is_mouse_btn_pressed(int button)
    {
    	return std::find(m_MouseBtnsPressed.begin(), m_MouseBtnsPressed.end(), button) != m_MouseBtnsPressed.end();
    }

    bool InputSystem::is_mouse_btn_held(int button)
    {
    	return std::find(m_MouseBtnsHeld.begin(), m_MouseBtnsHeld.end(), button) != m_MouseBtnsHeld.end();
    }

    bool InputSystem::is_mouse_btn_released(int button)
    {
    	return std::find(m_MouseBtnsReleased.begin(), m_MouseBtnsReleased.end(), button) != m_MouseBtnsReleased.end();
    }

    void InputSystem::initialize()
    {

    	glfwSetKeyCallback(m_WindowPtr, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    	{
    		auto is = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));
    		if (is)
    			is->key_callback(window, key, scancode, action, mods);
    	});

    	glfwSetMouseButtonCallback(m_WindowPtr, [](GLFWwindow* window, int button, int action, int mods)
    	{
    		auto is = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));
    		if (is)
    			is->mouse_button_callback(window, button, action, mods);
    	});

    	glfwSetCursorPosCallback(m_WindowPtr, [](GLFWwindow* window, double xpos, double ypos)
    	{
    		auto is = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));
    		if (is) {
    			is->cursor_position_callback(window, xpos, ypos);
    		}
    	});
    }

    void InputSystem::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
    	//if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
    	//}
    	if(action == GLFW_PRESS)
    	{
    		if(std::find(m_KeysPressed.begin(), m_KeysPressed.end(), key) != m_KeysPressed.end())
    		{
    		} else {
    			m_KeysPressed.emplace_back(key);
    			m_KeysHolding.emplace_back(key);
    		}
    	}

    	if(action == GLFW_RELEASE)
    	{
    		for(std::vector<int>::iterator it = m_KeysHolding.begin(); it != m_KeysHolding.end(); it++)
    		{
    			if(*it == key)
    			{
    				m_KeysHolding.erase(it);
    				break;
    			}
    		}
    		m_KeysReleased.emplace_back(key);
    	}
    }

    void InputSystem::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    	if (action == GLFW_PRESS)
    	{
    		if (std::find(m_MouseBtnsHeld.begin(), m_MouseBtnsHeld.end(), button) == m_MouseBtnsHeld.end())
    		{
    			m_MouseBtnsPressed.emplace_back(button);
    			m_MouseBtnsHeld.emplace_back(button);
    		}
    	}

    	if (action == GLFW_RELEASE)
    	{
    		m_MouseBtnsReleased.emplace_back(button);
    		m_MouseBtnsHeld.erase(std::remove(m_MouseBtnsHeld.begin(), m_MouseBtnsHeld.end(), button), m_MouseBtnsHeld.end());
    	}
    }

    void InputSystem::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
    	if (firstMouse)
    	{
    		mouseX = xpos;
    		mouseY = ypos;
    		firstMouse = false;
    	}

    	mouseDeltaX += xpos - mouseX;
    	mouseDeltaY += mouseY - ypos; // Invert Y if needed
    	mouseX = xpos;
    	mouseY = ypos;
    }

    double InputSystem::get_delta_x() const { return mouseDeltaX; }
    double InputSystem::get_delta_y() const { return mouseDeltaY; }


    //Call this at the end of your game loop
    void InputSystem::clear()
    {
    	m_KeysPressed.clear();
    	m_KeysReleased.clear();

    	m_MouseBtnsPressed.clear();
    	m_MouseBtnsReleased.clear();

    	mouseDeltaX = 0.0;
    	mouseDeltaY = 0.0;
    }

    void InputSystem::loop(Camera* camera, float deltaTime)
    {
        if(this->is_key_held(GLFW_KEY_W))
            camera->process_input(move_direction::FORWARD, deltaTime);

        if(this->is_key_held(GLFW_KEY_S))
            camera->process_input(move_direction::BACKWARD, deltaTime);

        if(this->is_key_held(GLFW_KEY_A))
            camera->process_input(move_direction::LEFT, deltaTime);

        if(this->is_key_held(GLFW_KEY_D))
            camera->process_input(move_direction::RIGHT, deltaTime);

        if(this->is_key_held(GLFW_KEY_LEFT_SHIFT))
            camera->process_input(move_direction::DOWN, deltaTime);

        if(this->is_key_held(GLFW_KEY_SPACE))
            camera->process_input(move_direction::UP, deltaTime);

        camera->process_mouse(get_delta_x(), get_delta_y());
    }
}

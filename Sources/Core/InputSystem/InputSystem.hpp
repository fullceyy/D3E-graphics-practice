#pragma once
#include "Core/Camera/Camera.hpp"
#include "GLFW/glfw3.h"
#include <vector>

namespace D3E
{
    class InputSystem
    {
        private:
           	GLFWwindow* m_WindowPtr;
           	std::vector<int> m_KeysPressed;
           	std::vector<int> m_KeysReleased;
           	std::vector<int> m_KeysHolding;

           	std::vector<int> m_MouseBtnsPressed;
           	std::vector<int> m_MouseBtnsReleased;
           	std::vector<int> m_MouseBtnsHeld;

           	double mouseX = 0.0, mouseY = 0.0;
           	double mouseDeltaX = 0.0, mouseDeltaY = 0.0;
           	bool firstMouse = true;
        public:
           	InputSystem(GLFWwindow* window_ptr);
           	void initialize();

           	bool is_key_pressed(int key);
           	bool is_key_held(int key);
           	bool is_key_released(int key);

           	bool is_mouse_btn_pressed(int button);
           	bool is_mouse_btn_held(int button);
           	bool is_mouse_btn_released(int button);

           	double get_delta_x() const;
           	double get_delta_y() const;

           	void clear(); // Optional, if you want to clear every frame
           	void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
           	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
           	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

           	void loop(Camera* camera, float deltaTime);

           	GLFWwindow* get_window_ptr() const { return m_WindowPtr; }
    };
}

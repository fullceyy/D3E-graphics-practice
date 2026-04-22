#pragma once
#include "GLFW/glfw3.h"
#include <vector>

namespace D3E
{
	class Input
	{
	private:
		Input() = default;
		~Input() = default;

		static std::vector<int> mKeysPressed;
		static std::vector<int> mKeysHolding;
		static void InternalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	public:
		static void Initialize(GLFWwindow* window);
		static bool isKeyPressed(int key);
	};
};

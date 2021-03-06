#include "cactus_pch.h"
#include "WindowsInput.h"

#include "Cactus/Core/KeyCodes.h"
#include "Cactus/Core/Application.h"
#include <GLFW/glfw3.h>
namespace Cactus
{
	Input* Input::instance = new WindowsInput();

	/*
	bool WindowsInput::KeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || GLFW_REPEAT;
	}
	bool WindowsInput::MouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		
		auto state = glfwGetMouseButton(window, button);

		return state = GLFW_PRESS;
	}*/

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos ,(float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x,y] = GetMousePositionImpl();

		return x;
		
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();

		return y;
	}

	
	void WindowsInput::UpdateImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		//Basically move 1st bit to 2nd bit, and set 1st bit if input is down
		for (auto& it : keyMap) {
			int keycode = it.first;
			char value = it.second;

			auto state = glfwGetKey(window, keycode);
			int down = state == GLFW_PRESS || state == GLFW_REPEAT;

			int curr = (value >> 0) & 1;
			value = (curr << 1) + down;

			keyMap[keycode] = value;
		}

		for (auto& it : mouseMap) {
			int button = it.first;
			char value = it.second;

			auto state = glfwGetMouseButton(window, button);
			int down = state == GLFW_PRESS;

			int curr = (value >> 0) & 1;
			value = (curr << 1) + down;

			mouseMap[button] = value;
		}

	}
}
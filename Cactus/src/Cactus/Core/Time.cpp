#include "cactus_pch.h"

#include "Cactus/Core/Application.h"

#include "Time.h"

//OOF (should be platform independent)
#include <glfw/glfw3.h>

namespace Cactus {

	float Time::deltaTime = 0.0f;
	float Time::time = 0.0f;
	float Time::lastTime = 0.0f;

	void Time::Update()
	{
		time = (float)glfwGetTime();
		deltaTime = time - lastTime;
		lastTime = time;
	}
}
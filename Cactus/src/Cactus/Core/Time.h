#pragma once

#include "Cactus/Core/Application.h"
namespace Cactus 
{
	//Most dodgy thing I've ever written
	class Time
	{
	public:

		inline static const float GetDeltaTime() { return deltaTime; }
		inline static const float GetTime() { return time; }

	private:
		static void Update();

		//Might change it to Update() and let it handle calculating the diff itself;
		//inline static void SetDeltaTime(float delta) { Time::deltaTime = delta; }

		//	What    The    Fuck    Is    This		
		friend void Application::InternalTimeUpdate();
		static float deltaTime;
		static float time;
		static float lastTime;
	};
}
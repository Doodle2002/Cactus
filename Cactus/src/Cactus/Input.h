#pragma once

#include "Cactus/Core.h"

namespace Cactus {
	class CACTUS_API Input
	{
	public:
		/*
		static bool KeyDown(int keycode);
		static bool KeyPressed(int keycode);
		static bool KeyReleased(int keycode);
		*/
		inline static bool KeyPressed(int keycode) { return instance->KeyPressedImpl(keycode); }

		inline static bool MouseButtonPressed(int button) { return instance->MouseButtonPressedImpl(button); }
		inline static bool GetMouseX() { return instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { return instance->GetMouseYImpl(); }
		inline static std::pair<float,float> GetMousePosition() { return instance->GetMousePositionImpl(); }
		
		//inline static void Update() { instance->UpdateImpl(); }
	protected:
		virtual bool KeyPressedImpl(int keycode) = 0;

		virtual bool MouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		//virtual void UpdateImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;


		std::unordered_map<int, bool> keyQueue;
		std::unordered_map<int, int> keyMap;

		std::unordered_map<int, bool> mouseQueue;
		std::unordered_map<int, int> mouseMap;

	private:
		static Input* instance;
	};
}
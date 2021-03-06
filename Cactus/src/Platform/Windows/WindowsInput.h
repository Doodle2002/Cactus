#pragma once

#include "Cactus/Core/Input.h"

namespace Cactus
{
	class WindowsInput : public Input
	{
	protected:
		//virtual bool KeyPressedImpl(int keycode) override;
		//virtual bool MouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;


		virtual void UpdateImpl() override;
	};

}
#pragma once

#include "Cactus/Core/Layer.h"
#include "Cactus/Events/MouseEvent.h"
#include "Cactus/Events/KeyEvent.h"
#include "Cactus/Events/ApplicationEvent.h"

namespace Cactus
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float time = 0.0f;
	};
}



#pragma once

#include "Cactus/Layer.h"
#include "Cactus/Events/MouseEvent.h"
#include "Cactus/Events/KeyEvent.h"
#include "Cactus/Events/ApplicationEvent.h"

namespace Cactus
{
	class CACTUS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender();

		void Begin();
		void End();

	private:
		float time = 0.0f;
	};
}



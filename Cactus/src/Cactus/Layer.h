#pragma once

#include "Cactus/Core.h"
#include "Cactus/Events/Event.h"

namespace Cactus
{
	class CACTUS_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName; }
	protected:
		std::string debugName;
	};
}


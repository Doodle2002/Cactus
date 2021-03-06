#pragma once

#include "Cactus/Core/Layer.h"

namespace Cactus {
	class DebugLayer : public Layer
	{
	public:
		DebugLayer();
		virtual ~DebugLayer() = default;


		virtual void OnImGuiRender() override;

	};
}
#pragma once

#include "Cactus/Core/Core.h"
#include "Cactus/Core/Layer.h"

#include <vector>
namespace Cactus
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }

	private:
		std::vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;
	};
}


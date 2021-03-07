#include <Cactus.h>
#include <Cactus/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Cactus {

	class CactusEditor : public Application
	{
	public:
		CactusEditor()
			: Application("Cactus Editor")
		{
			PushLayer(new EditorLayer());
		}

		~CactusEditor()
		{
		}
	};

	Application* CreateApplication() {
		return new CactusEditor();
	}

}


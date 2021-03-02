#include "cactus_pch.h"
#include "Input.h"

#include "KeyCodes.h"
#include "MouseButtonCodes.h"
namespace Cactus
{
	
	Input::Input()
	{
		keyMap[CACTUS_KEY_SPACE              ] = 0;
		keyMap[CACTUS_KEY_APOSTROPHE         ] = 0;
		keyMap[CACTUS_KEY_COMMA              ] = 0;
		keyMap[CACTUS_KEY_MINUS              ] = 0;
		keyMap[CACTUS_KEY_PERIOD             ] = 0;
		keyMap[CACTUS_KEY_SLASH              ] = 0;
		keyMap[CACTUS_KEY_0                  ] = 0;
		keyMap[CACTUS_KEY_1                  ] = 0;
		keyMap[CACTUS_KEY_2                  ] = 0;
		keyMap[CACTUS_KEY_3                  ] = 0;
		keyMap[CACTUS_KEY_4                  ] = 0;
		keyMap[CACTUS_KEY_5                  ] = 0;
		keyMap[CACTUS_KEY_6                  ] = 0;
		keyMap[CACTUS_KEY_7                  ] = 0;
		keyMap[CACTUS_KEY_8                  ] = 0;
		keyMap[CACTUS_KEY_9                  ] = 0;
		keyMap[CACTUS_KEY_SEMICOLON          ] = 0;
		keyMap[CACTUS_KEY_EQUAL              ] = 0;
		keyMap[CACTUS_KEY_A                  ] = 0;
		keyMap[CACTUS_KEY_B                  ] = 0;
		keyMap[CACTUS_KEY_C                  ] = 0;
		keyMap[CACTUS_KEY_D                  ] = 0;
		keyMap[CACTUS_KEY_E                  ] = 0;
		keyMap[CACTUS_KEY_F                  ] = 0;
		keyMap[CACTUS_KEY_G                  ] = 0;
		keyMap[CACTUS_KEY_H                  ] = 0;
		keyMap[CACTUS_KEY_I                  ] = 0;
		keyMap[CACTUS_KEY_J                  ] = 0;
		keyMap[CACTUS_KEY_K                  ] = 0;
		keyMap[CACTUS_KEY_L                  ] = 0;
		keyMap[CACTUS_KEY_M                  ] = 0;
		keyMap[CACTUS_KEY_N                  ] = 0;
		keyMap[CACTUS_KEY_O                  ] = 0;
		keyMap[CACTUS_KEY_P                  ] = 0;
		keyMap[CACTUS_KEY_Q                  ] = 0;
		keyMap[CACTUS_KEY_R                  ] = 0;
		keyMap[CACTUS_KEY_S                  ] = 0;
		keyMap[CACTUS_KEY_T                  ] = 0;
		keyMap[CACTUS_KEY_U                  ] = 0;
		keyMap[CACTUS_KEY_V                  ] = 0;
		keyMap[CACTUS_KEY_W                  ] = 0;
		keyMap[CACTUS_KEY_X                  ] = 0;
		keyMap[CACTUS_KEY_Y                  ] = 0;
		keyMap[CACTUS_KEY_Z                  ] = 0;
		keyMap[CACTUS_KEY_LEFT_BRACKET       ] = 0;
		keyMap[CACTUS_KEY_BACKSLASH          ] = 0;
		keyMap[CACTUS_KEY_RIGHT_BRACKET      ] = 0;
		keyMap[CACTUS_KEY_GRAVE_ACCENT       ] = 0;
		keyMap[CACTUS_KEY_WORLD_1            ] = 0;
		keyMap[CACTUS_KEY_WORLD_2            ] = 0;
		keyMap[CACTUS_KEY_ESCAPE             ] = 0;
		keyMap[CACTUS_KEY_ENTER              ] = 0;
		keyMap[CACTUS_KEY_TAB                ] = 0;
		keyMap[CACTUS_KEY_BACKSPACE          ] = 0;
		keyMap[CACTUS_KEY_INSERT             ] = 0;
		keyMap[CACTUS_KEY_DELETE             ] = 0;
		keyMap[CACTUS_KEY_RIGHT              ] = 0;
		keyMap[CACTUS_KEY_LEFT               ] = 0;
		keyMap[CACTUS_KEY_DOWN               ] = 0;
		keyMap[CACTUS_KEY_UP                 ] = 0;
		keyMap[CACTUS_KEY_PAGE_UP            ] = 0;
		keyMap[CACTUS_KEY_PAGE_DOWN          ] = 0;
		keyMap[CACTUS_KEY_HOME               ] = 0;
		keyMap[CACTUS_KEY_END                ] = 0;
		keyMap[CACTUS_KEY_CAPS_LOCK          ] = 0;
		keyMap[CACTUS_KEY_SCROLL_LOCK        ] = 0;
		keyMap[CACTUS_KEY_NUM_LOCK           ] = 0;
		keyMap[CACTUS_KEY_PRINT_SCREEN       ] = 0;
		keyMap[CACTUS_KEY_PAUSE              ] = 0;
		keyMap[CACTUS_KEY_F1                 ] = 0;
		keyMap[CACTUS_KEY_F2                 ] = 0;
		keyMap[CACTUS_KEY_F3                 ] = 0;
		keyMap[CACTUS_KEY_F4                 ] = 0;
		keyMap[CACTUS_KEY_F5                 ] = 0;
		keyMap[CACTUS_KEY_F6                 ] = 0;
		keyMap[CACTUS_KEY_F7                 ] = 0;
		keyMap[CACTUS_KEY_F8                 ] = 0;
		keyMap[CACTUS_KEY_F9                 ] = 0;
		keyMap[CACTUS_KEY_F10                ] = 0;
		keyMap[CACTUS_KEY_F11                ] = 0;
		keyMap[CACTUS_KEY_F12                ] = 0;
		keyMap[CACTUS_KEY_F13                ] = 0;
		keyMap[CACTUS_KEY_F14                ] = 0;
		keyMap[CACTUS_KEY_F15                ] = 0;
		keyMap[CACTUS_KEY_F16                ] = 0;
		keyMap[CACTUS_KEY_F17                ] = 0;
		keyMap[CACTUS_KEY_F18                ] = 0;
		keyMap[CACTUS_KEY_F19                ] = 0;
		keyMap[CACTUS_KEY_F20                ] = 0;
		keyMap[CACTUS_KEY_F21                ] = 0;
		keyMap[CACTUS_KEY_F22                ] = 0;
		keyMap[CACTUS_KEY_F23                ] = 0;
		keyMap[CACTUS_KEY_F24                ] = 0;
		keyMap[CACTUS_KEY_F25                ] = 0;
		keyMap[CACTUS_KEY_KP_0               ] = 0;
		keyMap[CACTUS_KEY_KP_1               ] = 0;
		keyMap[CACTUS_KEY_KP_2               ] = 0;
		keyMap[CACTUS_KEY_KP_3               ] = 0;
		keyMap[CACTUS_KEY_KP_4               ] = 0;
		keyMap[CACTUS_KEY_KP_5               ] = 0;
		keyMap[CACTUS_KEY_KP_6               ] = 0;
		keyMap[CACTUS_KEY_KP_7               ] = 0;
		keyMap[CACTUS_KEY_KP_8               ] = 0;
		keyMap[CACTUS_KEY_KP_9               ] = 0;
		keyMap[CACTUS_KEY_KP_DECIMAL         ] = 0;
		keyMap[CACTUS_KEY_KP_DIVIDE          ] = 0;
		keyMap[CACTUS_KEY_KP_MULTIPLY        ] = 0;
		keyMap[CACTUS_KEY_KP_SUBTRACT        ] = 0;
		keyMap[CACTUS_KEY_KP_ADD             ] = 0;
		keyMap[CACTUS_KEY_KP_ENTER           ] = 0;
		keyMap[CACTUS_KEY_KP_EQUAL           ] = 0;
		keyMap[CACTUS_KEY_LEFT_SHIFT         ] = 0;
		keyMap[CACTUS_KEY_LEFT_CONTROL       ] = 0;
		keyMap[CACTUS_KEY_LEFT_ALT           ] = 0;
		keyMap[CACTUS_KEY_LEFT_SUPER         ] = 0;
		keyMap[CACTUS_KEY_RIGHT_SHIFT        ] = 0;
		keyMap[CACTUS_KEY_RIGHT_CONTROL      ] = 0;
		keyMap[CACTUS_KEY_RIGHT_ALT          ] = 0;
		keyMap[CACTUS_KEY_RIGHT_SUPER        ] = 0;
		keyMap[CACTUS_KEY_MENU               ] = 0;

		mouseMap[CACTUS_MOUSE_BUTTON_LAST      ] = 0;
		mouseMap[CACTUS_MOUSE_BUTTON_LEFT      ] = 0;
		mouseMap[CACTUS_MOUSE_BUTTON_RIGHT     ] = 0;
		mouseMap[CACTUS_MOUSE_BUTTON_MIDDLE    ] = 0;
	}

	bool Input::KeyDown(int keycode)
	{
		return instance->keyMap[keycode] % 2;
	}

	bool Input::KeyPressed(int keycode)
	{
		return instance->keyMap[keycode] == 1;
	}

	bool Input::KeyReleased(int keycode)
	{
		return instance->keyMap[keycode] == 2;
	}


	bool Input::MouseButtonDown(int button)
	{
		return instance->mouseMap[button] % 2;
	}

	bool Input::MouseButtonPressed(int button)
	{
		return instance->mouseMap[button] == 1;
	}

	bool Input::MouseButtonReleased(int button)
	{
		return instance->mouseMap[button] == 2;
	}

	


}
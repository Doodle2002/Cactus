#include "cactus_pch.h"
#include "WindowsWindow.h"

#include "Cactus/Events/MouseEvent.h"
#include "Cactus/Events/KeyEvent.h"
#include "Cactus/Events/ApplicationEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Cactus 
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		CACTUS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}
	Scope<Window> Window::Create(const WindowProps& props) 
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) 
	{

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		CACTUS_PROFILE_FUNCTION();
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		

		CACTUS_CORE_INFO("Creating window: {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			//CACTUS_CORE_ASSERT(success, "Could not initialize GLFW");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr,nullptr);
		context = new OpenGLContext(window);
		context->Init();

		

		glfwSetWindowUserPointer(window, &data);

		SetVSync(true);

		//Set callbacks

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				CACTUS_CORE_WARN("{0}, {1}", width, height);
				data.eventCallback(event);
				
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.eventCallback(event);

			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) 
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.eventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key,1);
						data.eventCallback(event);
						break;
					}
				}
				WindowCloseEvent event;
				

			});
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);

				data.eventCallback(event);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.eventCallback(event);
						break;
					}
				}

			});

		glfwSetScrollCallback(window, [](GLFWwindow* window,double x, double y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)x,(float)y);
				data.eventCallback(event);

			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)x, (float)y);
				data.eventCallback(event);

			});

	}

	void WindowsWindow::Shutdown()
	{
		CACTUS_PROFILE_FUNCTION();
		glfwDestroyWindow(window);
	}

	void WindowsWindow::OnUpdate()
	{
		CACTUS_PROFILE_FUNCTION();
		glfwPollEvents();
		context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		CACTUS_PROFILE_FUNCTION();
		if (enabled) {
			glfwSwapInterval(1);
		}
		else 
		{
			glfwSwapInterval(0);
		}

		data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data.vSync;
	}
}
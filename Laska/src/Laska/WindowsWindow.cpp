#include "WindowsWindow.h"
#include <cassert>

namespace Laska 
{
	WindowsWindow::WindowsWindow(const WindowSpecification& specs)
		: Window(specs)
	{
		Init(specs);
	}
	
	WindowsWindow::~WindowsWindow()
	{
		Destroy();
	}

	void WindowsWindow::Init(const WindowSpecification& specs)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_handle = glfwCreateWindow(m_width, m_height, specs.Title.c_str(), NULL, NULL);
		
		assert(m_handle && "Failed to create GLFW window.");

		glfwSetWindowUserPointer(m_handle, specs.UserData);
		glfwSwapInterval(specs.VSync);

		glfwSetWindowSizeCallback(m_handle, Window::WindowResizeCallback);
		glfwSetWindowCloseCallback(m_handle, Window::WindowCloseCallback);
		glfwSetKeyCallback(m_handle, Window::WindowKeyCallback);
	}

	void WindowsWindow::Destroy()
	{
		glfwDestroyWindow(m_handle);
	}

	bool WindowsWindow::VSync() const
	{
		return m_vsync;
	}

	void WindowsWindow::SetVSync(bool vsync)
	{
		glfwSwapInterval(vsync);
		
		m_vsync = vsync;
	}

	GLFWwindow* WindowsWindow::GetHandle() const
	{
		return m_handle;
	}
}

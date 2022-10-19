#pragma once

#include "Core.h"
#include "events/Event.h"
#include <string>
#include "events/EventQueue.h"

namespace Laska
{
	struct WindowSpecification
	{
		std::string Title = "Laska Engine";
		uint32_t Width = 1280;
		uint32_t Height = 720;
		void* UserData = nullptr;
		bool VSync;
	};

	class Window
	{
	public:
		static void WindowCloseCallback(GLFWwindow* window)
		{
			EventQueue* queue = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));

			queue->Enqueue(Event(EventType::WindowClose));
		}

		static void WindowResizeCallback(GLFWwindow* window, int width, int height)
		{
			EventQueue* queue = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));

			queue->Enqueue(Event(EventType::WindowResize, { width, height}));
		}

		static void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			EventQueue* queue = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));

  			queue->Enqueue(Event(EventType::Invalid, { key, action, mods }));
		}

	protected:
		uint32_t m_width;
		uint32_t m_height;

	public:
		Window(const WindowSpecification& specs)
		{
			m_width = specs.Width;
			m_height = specs.Height;
		}

		virtual ~Window() 
		{

		}

		uint32_t Width() const
		{
			return m_width;
		}

		uint32_t Height() const
		{
			return m_width;
		}

		virtual bool VSync() const = 0;
		virtual void SetVSync(bool vsync) = 0;
		virtual GLFWwindow* GetHandle() const = 0;
	};
}

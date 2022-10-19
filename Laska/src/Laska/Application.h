#pragma once

#include "game/Game.h"
#include "Window.h"
#include "WindowsWindow.h"
#include "events/Event.h"
#include "events/EventQueue.h"

namespace Laska
{
	struct ApplicationSpecification
	{
		uint32_t WindowHeight;
		uint32_t WindowWidth;
		bool FullScreen;
		bool VSync;
	};

	class Application
	{
	private:
		Game* m_game;
		Window* m_window;
		EventQueue* m_eventQueue;

	private:
		void InitOpenGL(const WindowSpecification& specs);

	public:
		Application(const ApplicationSpecification& specs);
		~Application();

		Game* GetGame() const;

		void Start();
	};
}

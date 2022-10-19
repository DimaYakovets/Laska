#include "Application.h"
#include "Window.h"
#include "dotnet/Dotnet.h"

namespace Laska
{
	Application::Application(const ApplicationSpecification& appSpecs)
	{
		m_eventQueue = new EventQueue();

		WindowSpecification windowSpecs{};
		windowSpecs.Height = appSpecs.WindowHeight;
		windowSpecs.Width = appSpecs.WindowWidth;
		windowSpecs.VSync = appSpecs.VSync;
		windowSpecs.UserData = m_eventQueue;

		m_window = new WindowsWindow(windowSpecs);

		GameSpecification gameSpecs{};
		gameSpecs.FixedTimeStep = 1 / 60.0f;
		gameSpecs.Window = m_window->GetHandle();
		gameSpecs.EventQueue = m_eventQueue;

		m_game = new Game(gameSpecs);
	}

	Application::~Application()
	{
		delete m_game;
		delete m_window;
		delete m_eventQueue;
	}

	Game* Application::GetGame() const
	{
		return m_game;
	}

	void Application::InitOpenGL(const WindowSpecification& specs)
	{
		m_window = static_cast<Window*>(new WindowsWindow(specs));
	}

	void Application::Start()
	{
		m_game->Run();
	}
}

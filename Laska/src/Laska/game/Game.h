#pragma once

#include "../Core.h"
#include "../events/EventQueue.h"
#include "Scene.h"

namespace Laska
{
	struct GameSpecification
	{
		GLFWwindow* Window;
		float FixedTimeStep;
		EventQueue* EventQueue;
	};

	class Game
	{
	private:
		bool m_running;
		float m_fixedTimeStep;
		GLFWwindow* m_window;
		Scene* m_activeScene;
		EventQueue* m_events;

	public:
		Game(const GameSpecification& specs);
		~Game();

		void Run();
		void Close();

		bool LoadScene(int64_t index);
		bool LoadSceneAsync(int64_t index);
	};
}

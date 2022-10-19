#include <Laska/Core.h>
#include "Game.h"
#include <memory>

namespace Laska
{
	Game::Game(const GameSpecification& specs) :
		m_window(specs.Window),
		m_fixedTimeStep(specs.FixedTimeStep),
		m_running(true),
		m_events(specs.EventQueue)
	{
		Component proto_1_components[]
		{
			BuiltInComponent(Transform),
			BuiltInComponent(SpriteRenderer),
			BuiltInComponent(RigidBody)
		};

		Component proto_2_components[]
		{
			BuiltInComponent(Transform),
			BuiltInComponent(SpriteRenderer),
			BuiltInComponent(Camera)
		};

		Component proto_3_components[]
		{
			BuiltInComponent(Transform),
			BuiltInComponent(SpriteRenderer),
			BuiltInComponent(RigidBody),
			BuiltInComponent(Grid)
		};

		PrototypeInfo proto_1{};
		proto_1.Components.Items = proto_1_components;
		proto_1.Components.Length = sizeof(proto_1_components) / sizeof(Component);

		PrototypeInfo proto_2{};
		proto_2.Components.Items = proto_2_components;
		proto_2.Components.Length = sizeof(proto_2_components) / sizeof(Component);

		PrototypeInfo proto_3{};
		proto_3.Components.Items = proto_3_components;
		proto_3.Components.Length = sizeof(proto_3_components) / sizeof(Component);

		PrototypeInfo prototypes[3] { proto_1, proto_2, proto_3 };

		SceneConfiguration sceneConfig{};
		sceneConfig.RegsitryConfig.AllocatorCapacity = 4;

		sceneConfig.RegsitryConfig.Prototypes.Length = 3;
		sceneConfig.RegsitryConfig.Prototypes.Items = prototypes;

		m_activeScene = new Scene(sceneConfig);
	}

	Game::~Game()
	{
		delete m_activeScene;
	}

	void Game::Run()
	{
		double oldtime = 0;
		double curtime = 0;
		double delta = 0;
		double acc = 0;

		while (m_running)
		{
			glfwPollEvents();

			while (m_events->HasEvents())
			{
				Event& event = m_events->Dispatch();

				if (event.Type == EventType::WindowClose)
				{
					m_running = false;
					break;
				}

				m_activeScene->OnEvent(event);
			}

			curtime = glfwGetTime();
			delta = oldtime - curtime;
			oldtime = curtime;
			acc += delta;

			m_activeScene->UpdateCamera();

			m_activeScene->EarlyUpdate();

			while (acc > m_fixedTimeStep)
			{
				m_activeScene->FixedUpdate();

				acc -= m_fixedTimeStep;
			}

			m_activeScene->Update();
			m_activeScene->LateUpdate();

			m_activeScene->Render();

			glfwSwapBuffers(m_window);
		}
	}

	void Game::Close()
	{
		m_running = false;
	}

	bool Game::LoadScene(int64_t index)
	{
		return false;
	}

	bool Game::LoadSceneAsync(int64_t index)
	{
		return false;
	}
}

#include "Scene.h"
#include "Entity.h"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>

namespace Laska
{
	Scene::Scene(const SceneConfiguration& config)
		: m_primaryCamera(), m_registry(config.RegsitryConfig)
	{
		uint64_t cmps[2] = { TypeIndex(Transform), TypeIndex(SpriteRenderer) };

		m_query_TransformSpriteRenderer = m_registry.QueryDynamic(2, cmps);
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(Prototype prototype)
	{
		uint64_t id = m_registry.CreateEntity(prototype);

		return { id, &m_registry };
	}

	void Scene::SetPrimaryCamera(Entity camera)
	{
		m_primaryCamera.CameraPos = &camera.GetComponent<Transform>();
		m_primaryCamera.CameraSpecs = &camera.GetComponent<Camera>();
	}

	void Scene::OnEvent(const Event& event)
	{
		if (event.Type == EventType::WindowResize)
		{
			if (m_primaryCamera.CameraSpecs)
			{
				m_primaryCamera.CameraSpecs->Width = (float)event.Args.WindowResize.Width;
				m_primaryCamera.CameraSpecs->Height = (float)event.Args.WindowResize.Height;
			}
		}
	}

	void Scene::Load()
	{

	}

	void Scene::UpdateCamera()
	{
		if (m_primaryCamera.CameraSpecs)
		{
			float w, h, f, n, s;

			w = m_primaryCamera.CameraSpecs->Width;
			h = m_primaryCamera.CameraSpecs->Height;
			f = m_primaryCamera.CameraSpecs->Far;
			n = m_primaryCamera.CameraSpecs->Near;
			s = m_primaryCamera.CameraSpecs->Scale;

			glm::mat4 proj = glm::ortho(-w / 2, w / 2, -h / 2, h / 2, n, f);

			glm::mat4 view = glm::identity<glm::mat4>();
			view = glm::scale(view, { s, s, 1.0f });
			view = glm::rotate(view, m_primaryCamera.CameraPos->Angle, { 0, 0, 1 });
			view = glm::translate(view, -m_primaryCamera.CameraPos->Position);
		}
	}

	void Scene::EarlyUpdate()
	{

	}

	void Scene::FixedUpdate()
	{

	}

	void Scene::Update()
	{

	}

	void Scene::LateUpdate()
	{

	}

	void Scene::Render()
	{
		//Upadate SpriteRenderers
		{
			m_query_TransformSpriteRenderer.Reset();

			while (m_query_TransformSpriteRenderer.Next())
			{

			}
		}
	}
}

#pragma once

#include <cmath>

#include "../Core.h"
#include "Entity.h"
#include "../ecs/Registry.h"
#include "../events/Event.h"

namespace Laska
{
	struct SceneConfiguration
	{
		RegistryConfiguration RegsitryConfig;
	};

	struct CameraTransfromGroup
	{
		Transform* CameraPos;
		Camera* CameraSpecs;
	};

	class Scene
	{
		friend class Entity;

	private:
		//Registry
		Registry m_registry;

		//Queries
		RegistryQuery m_query_TransformSpriteRenderer;

		//Camera stuff
		CameraTransfromGroup m_primaryCamera;

	public:
		Scene(const SceneConfiguration& config);
		~Scene();

		Entity CreateEntity(Prototype prototype);

		void SetPrimaryCamera(Entity camera);

		void OnEvent(const Event& event);

		void Load();

		void UpdateCamera();
		void EarlyUpdate();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render();

	private:
		template<typename TComponent>
		void OnComponentAdd(TComponent& ptr);
	};
}

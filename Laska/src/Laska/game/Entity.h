#pragma once

#include <Laska/ecs/Registry.h>

#include <stdint.h>

namespace Laska
{
	class Entity
	{
	private:
		uint64_t m_id;
		Registry* m_registry;

	public:
		Entity() = default;
		Entity(Entity&) = default;
		Entity(uint64_t id, Registry* registry);
		
		inline uint64_t GetId() { return m_id; }

		template<typename TComponent>
		TComponent& GetComponent()
		{
			return m_registry->GetComponent<TComponent>(m_id);
		}

		template<typename TComponent>
		bool HasComponent()
		{
			return m_registry->HasComponent<TComponent>(m_id);
		}

		void* GetComponentDynamic(uint64_t component);
		bool HasComponentDynamic(uint64_t component);

		void Destroy();

		Entity& operator=(const Entity& entity) = default;
		
		bool operator==(Entity& e)
		{
			return this->m_id == e.m_id;
		}

		bool operator!=(Entity& e)
		{
			return this->m_id != e.m_id;
		}
	};
}

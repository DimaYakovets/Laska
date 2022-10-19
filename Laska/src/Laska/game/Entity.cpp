#include "Entity.h"

namespace Laska
{
	Entity::Entity(uint64_t id, Registry* registry)
	{
		m_id = id;
		m_registry = registry;
	}
	
	void* Entity::GetComponentDynamic(uint64_t component)
	{
		return m_registry->GetComponentDynamic(m_id, component);
	}

	bool Entity::HasComponentDynamic(uint64_t component)
	{
		return m_registry->HasComponentDynamic(m_id, component);
	}

	void Entity::Destroy()
	{
		m_registry->DeleteEntity(m_id);

		m_id = 0;
		m_registry = nullptr;
	}
}

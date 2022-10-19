#pragma once

#include <unordered_map>

#include "../Core.h"
#include "../memory/PageAllocator.h"
#include "../memory/Containers/List.h"
#include "Components.h"
#include "EntityMatrix.h"
#include "Prototype.h"
#include "RegistryQuery.h"

#include "Components.h"

#include <Laska/memory/LinearAllocator.h>

namespace Laska
{
	struct IndexList
	{
		uint32_t Max;
		uint32_t Length;
		uint32_t* Indices;
	};

	struct RegistryConfiguration
	{
		uint32_t AllocatorCapacity = 4;
		Span<PrototypeInfo> Prototypes;
	};

	struct EntityInfo
	{
		Prototype Proto;
		uint32_t Index;
	};

	class Registry
	{
	private:
		std::vector<std::vector<uint32_t>> m_components;
		std::vector<PrototypeData> m_prototypes;
		std::unordered_map<uint64_t, EntityInfo> m_idToIndex;
		LinearAllocator m_queryTempAllocator;
		LinearAllocator m_queryArrayAllocator;

	public:
		Registry(const RegistryConfiguration& config);
		~Registry();

		void* GetComponentDynamic(uint64_t entity, int64_t cmp);
		bool HasComponentDynamic(uint64_t entity, int64_t cmp);

		uint64_t CreateEntity(Prototype proto);
		void DeleteEntity(uint64_t entity);

		RegistryQuery QueryDynamic(uint32_t count, uint64_t* components);

		template<typename TComponent>
		TComponent& GetComponent(uint64_t entity)
		{
			return *(TComponent*)GetComponentDynamic(entity, TypeIndex(TComponent));
		}

		template<typename TComponent>
		bool HasComponent(uint64_t entity)
		{
			return HasComponentDynamic(entity, TypeIndex(TComponent));
		}
	};
}

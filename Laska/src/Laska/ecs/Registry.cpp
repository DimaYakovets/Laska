#include "Registry.h"
#include <random>

namespace Laska
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_Destribution;

	Registry::Registry(const RegistryConfiguration& config)
		: m_prototypes(), m_components(),
		m_queryTempAllocator(new uint8_t[config.Prototypes.Length * 32], config.Prototypes.Length * 32),
		m_queryArrayAllocator(new uint8_t[sizeof(void*) * 1024 * 32], sizeof(void*) * 1024 * 32)
	{
		m_prototypes.resize(config.Prototypes.Length);

		for (uint32_t i = 0; i < config.Prototypes.Length; i++)
		{
			const PrototypeInfo& protoInfo = config.Prototypes[i];

			m_prototypes[i].Allocators = Span<PageAllocator>::Allocate(protoInfo.Components.Length);

			new (&m_prototypes[i].Matrix) EntityMatrix(m_prototypes[i].Allocators.Length, config.AllocatorCapacity);

			// Allocators
			size_t mapArraySize = 0;

			for (uint32_t j = 0; j < protoInfo.Components.Length; j++)
			{
				new (&m_prototypes[i].Allocators[j]) PageAllocator(protoInfo.Components[j].Size);

				if (protoInfo.Components[j].Index >= mapArraySize)
				{
					mapArraySize = protoInfo.Components[j].Index + 1;
				}

				if (protoInfo.Components[j].Index >= m_components.size())
				{
					m_components.resize(protoInfo.Components[j].Index + 1);
				}

				m_components[protoInfo.Components[j].Index].push_back(i);
			}

			// Mappers
			m_prototypes[i].Mappers = Span<uint16_t>::Allocate(mapArraySize);

			for (uint32_t j = 0; j < protoInfo.Components.Length; j++)
			{
				m_prototypes[i].Mappers[protoInfo.Components[j].Index] = (uint16_t)j;
			}
		}
	}

	Registry::~Registry()
	{

	}

	RegistryQuery Registry::QueryDynamic(uint32_t count, uint64_t* components)
	{
		uint32_t* indices = m_queryTempAllocator.Allocate<uint32_t>(m_prototypes.size());

		memset(indices, 0, m_prototypes.size() * sizeof(uint32_t));

		for (size_t i = 0; i < count; i++)
		{
			std::vector<uint32_t>& idx = m_components[components[i]];

			for (size_t j = 0; j < idx.size(); j++)
			{
				indices[idx[j]]++;
			}
		}

		int foundProtosIndicesCount = 0;
		uint32_t* foundProtosIndices = m_queryTempAllocator.Allocate<uint32_t>(m_prototypes.size());

		for (size_t i = 0; i < m_prototypes.size(); i++)
		{
			if (indices[i] == count)
			{
				foundProtosIndices[foundProtosIndicesCount++] = i;
			}
		}

		Span<PrototypeData*> protoptrs = Span<PrototypeData*>::Allocate(foundProtosIndicesCount, m_queryArrayAllocator);

		for (size_t i = 0; i < foundProtosIndicesCount; i++)
		{
			protoptrs[i] = m_prototypes.data() + foundProtosIndices[i];
		}

		m_queryTempAllocator.Reset();

		Span<uint64_t> cmps = Span<uint64_t>::Allocate(count, m_queryArrayAllocator);
		memcpy(cmps.Items, components, sizeof(uint64_t) * count);

		return RegistryQuery(protoptrs, cmps);
	}

	uint64_t Registry::CreateEntity(Prototype proto)
	{
		PrototypeData& data = m_prototypes[proto];

		uint64_t id = s_Destribution(s_Engine);
		uint32_t index = data.Matrix.CreateRow();
		void** row = data.Matrix[index];

		for (size_t i = 0; i < data.Allocators.Length; i++)
		{
			row[i] = data.Allocators[i].Allocate(0);
		}

		EntityInfo info = { proto, index };

		m_idToIndex.emplace(id, info);

		return id;
	}

	void Registry::DeleteEntity(uint64_t entity)
	{
		EntityInfo info = m_idToIndex.at(entity);
		PrototypeData& data = m_prototypes[info.Proto];
		void** row = data.Matrix[info.Index];

		for (size_t i = 0; i < data.Allocators.Length; i++)
		{
			data.Allocators[i].Free(row[i]);
		}

		data.Matrix.DeleteRow(info.Index);
		m_idToIndex.erase(entity);
	}

	void* Registry::GetComponentDynamic(uint64_t entity, int64_t cmp)
	{
		EntityInfo info = m_idToIndex.at(entity);

		return m_prototypes[info.Proto].Matrix[info.Index][cmp];
	}

	bool Registry::HasComponentDynamic(uint64_t entity, int64_t cmp)
	{
		return GetComponentDynamic(entity, cmp) != nullptr;
	}
}

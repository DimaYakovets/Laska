#include "RegistryQuery.h"
#include <Laska/Core.h>

namespace Laska
{
	RegistryQuery::RegistryQuery(Span<PrototypeData*> protos, Span<uint64_t> cmps)
		: m_componentsCount(cmps.Length), m_allocatorsCount(protos.Length)
	{
		m_allocators = reinterpret_cast<PageAllocator**>(new void* [cmps.Length * protos.Length]);

		for (size_t i = 0; i < cmps.Length; i++)
		{
			for (size_t j = 0; j < protos.Length; j++)
			{
				m_allocators[i * protos.Length + j] = &protos[j]->Allocators[protos[j]->Mappers[cmps[i]]];
			}
		}
	}

	RegistryQuery::~RegistryQuery()
	{

	}

	bool RegistryQuery::Next()
	{
		return false;
	}

	void RegistryQuery::Reset()
	{

	}
}

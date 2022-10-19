#pragma once

#include <stdint.h>
#include "Prototype.h"

namespace Laska
{
	class RegistryQuery
	{
	private:
		PageAllocator** m_allocators;
		size_t m_componentsCount;
		size_t m_allocatorsCount;

	public:
		RegistryQuery() = default;
		RegistryQuery(Span<PrototypeData*> protos, Span<uint64_t> cmps);
		~RegistryQuery();
		
		bool Next();
		void Reset();
	};
}

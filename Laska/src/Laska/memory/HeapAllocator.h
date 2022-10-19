#pragma once

#include "Allocator.h"
#include <stdlib.h>

namespace Laska
{
	class HeapAllocator : public Allocator
	{
		virtual void* Allocate(size_t size) override;
		virtual void Free(void* ptr) override;
	};
}

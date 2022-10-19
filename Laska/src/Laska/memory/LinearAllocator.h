#pragma once

#include <stdint.h>

#include "Allocator.h"

namespace Laska
{
	class LinearAllocator : public Allocator
	{
	private:
		void* m_buffer;
		void* m_pointer;
		void* m_end;

	public:
		LinearAllocator(void* buffer, size_t size);
		~LinearAllocator();

		void* Allocate(size_t size) override;
		void Free(void* ptr) {}
		void Reset();

		template<typename T>
		T* Allocate(size_t count)
		{
			return (T*)Allocate(sizeof(T) * count);
		}
	};
}

#pragma once
#include <Laska/memory/MemoryUtils.h>
#include <stdint.h>

namespace Laska
{
	using byte = unsigned char;

	struct MemoryRange
	{
	public:
		byte* m_ptr;
		byte* m_pen;
		byte* m_end;
	};

	class CellAllocator
	{
	private:
		static const int KB = 1024;
		static const int MB = 1024 * 1024;

		Span<MemoryRange> m_pages;
		size_t m_cellSize;
		size_t m_cellsPerPage;
		size_t m_maxIndex;

	public:
		CellAllocator();
		~CellAllocator();

		void* Allocate(uint32_t* index);
		void Free(uint32_t index);
	};
}

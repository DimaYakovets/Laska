#pragma once

#include <Laska/memory/Allocator.h>
#include <stdint.h>

namespace Laska
{
	template<typename T>
	struct Span
	{
	public:
		static Span<T> Allocate(size_t length)
		{
			Span<T> span{};
			span.Length = length;
			span.Items = reinterpret_cast<T*>(new int8_t[sizeof(T) * length]);

			return span;
		}

		static Span<T> Create(size_t length, T* ptr)
		{
			return { length, ptr };
		}

		static Span<T> Allocate(size_t length, Allocator& allocator)
		{
			Span<T> span{};
			span.Length = length;
			span.Items = static_cast<T*>(allocator.Allocate(sizeof(T) * length));

			return span;
		}

	public:
		size_t Length;
		T* Items;

		inline T& operator[](uint32_t index)
		{
			return Items[index];
		}

		inline const T& operator[](uint32_t index) const
		{
			return Items[index];
		}
	};

	template<typename T, uint32_t length>
	struct StaticSpan
	{
		const uint32_t Length = length;
		T Items[length];

		inline T& operator[](uint32_t index)
		{
			return Items[index];
		}
	};
}

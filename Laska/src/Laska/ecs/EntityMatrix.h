#pragma once

#include <stack>

namespace Laska
{
	class EntityMatrix
	{
	private:
		std::stack<uint32_t> m_freeSlots;
		void** m_matrix;
		uint32_t m_stride;
		uint32_t m_capcity;
		uint32_t m_count;

	public:
		inline uint32_t Count() { return m_count; }
		inline uint32_t Capacity() { return m_capcity; }
		inline uint32_t UpperBound() { return m_capcity; }

	public:
		EntityMatrix() = default;
		EntityMatrix(const EntityMatrix&) = default;
		EntityMatrix(uint32_t stride, const uint32_t capacity = 64)
			: m_capcity(capacity), m_count(0), m_stride(stride), m_freeSlots()
		{
			m_matrix = new void* [m_stride * m_capcity];
		}

		~EntityMatrix()
		{
			delete[] m_matrix;
		}

		uint32_t CreateRow()
		{
			if (m_freeSlots.size() > 0)
			{
				uint32_t result = m_freeSlots.top();
				m_freeSlots.pop();

				return result;
			}

			if (m_count == m_capcity)
			{
				m_capcity = (uint32_t)(m_capcity * 1.5);
				void** old = m_matrix;
				m_matrix = new void* [m_capcity];

				memcpy(m_matrix, old, sizeof(void*) * m_count);

				delete old;
			}

			return m_count++;
		}

		void DeleteRow(uint32_t index)
		{
			memset(m_matrix + index * m_stride, 0, m_stride * sizeof(void*));
			
			if (index + 1 == m_count)
			{
				m_count--;
				return;
			}

			m_count--;
			m_freeSlots.push(index);
		}

		inline void** operator[](uint32_t index)
		{
			return m_matrix + (size_t)index * m_stride;
		}
	};
}

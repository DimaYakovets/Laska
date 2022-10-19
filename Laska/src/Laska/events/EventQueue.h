#pragma once

#include <stdint.h>
#include "Event.h"

namespace Laska
{
	class EventQueue
	{
	private:
		static const int32_t s_poolSize = 64;

	private:
		Event* m_queue;
		
		int32_t m_tail;
		int32_t m_head;
		int32_t m_count;

	public:
		EventQueue();

		bool HasEvents();

		void Enqueue(Event event);
		Event& Dispatch();
	};
}

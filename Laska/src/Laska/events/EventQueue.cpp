#include "EventQueue.h"

namespace Laska
{
	EventQueue::EventQueue()
		: m_count(0), m_head(0), m_tail(0)
	{
		m_queue = new Event[EventQueue::s_poolSize];
	}

	void EventQueue::Enqueue(Event event)
	{
		m_count++;
		m_queue[m_head] = event;

		m_head = (m_head + 1) % s_poolSize;
	}

	bool EventQueue::HasEvents()
	{
		return m_count > 0;
	}

	Event& EventQueue::Dispatch()
	{
		Event& event = m_queue[m_tail];
				
		m_tail = (m_tail + 1) % s_poolSize;
		m_count--;

		return event;
	}
}

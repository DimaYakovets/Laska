#pragma once

namespace Laska
{
	struct EventArgs
	{
		union
		{
			struct
			{
				int X;
				int Y;
			}
			WindowMove;

			struct
			{
				int Width;
				int Height;
			}
			WindowResize;
		};
	};

	static const size_t s = sizeof(EventArgs);

	enum class EventType
	{
		WindowClose,
		WindowResize,
		WindowMove,

		Invalid
	};

	class Event
	{
	public:
		EventType Type;
		EventArgs Args;

	public:
		Event(Event&) = default;
		Event(EventType type = EventType::Invalid, EventArgs args = {})
			: Type(type), Args(args) { }

		Event& operator=(Event& event)
		{
			this->Type = event.Type;
			this->Args.WindowMove.Height = event.Args.WindowMove.Height;
			this->Args.WindowMove.Width = event.Args.WindowMove.Width;

			return *this;
		}
	};
}

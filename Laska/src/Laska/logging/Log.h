#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Laska
{
	class Logger
	{
	public:
		static bool Init();

		static spdlog::logger* Laska::Logger::GetLogger();
	};
}

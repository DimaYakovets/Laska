#include "Log.h"

namespace Laska
{
	static spdlog::logger* s_logger;

	bool Logger::Init()
	{
		spdlog::set_pattern("[%D %T:%e] [%n] %^[%l]%$ %v");

		s_logger = spdlog::stdout_color_mt("LASKA").get();
		s_logger->set_level(spdlog::level::level_enum::trace);

		s_logger->info("Logging module has been initialized successfully");

		return true;
	}

	spdlog::logger* Logger::GetLogger()
	{
		return s_logger;
	}
}

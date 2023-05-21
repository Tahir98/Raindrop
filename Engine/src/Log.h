#pragma once 

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace Engine {

	class Log {
	public:
		static void init();
		static std::shared_ptr<spdlog::logger> engineLogger;
		static std::shared_ptr<spdlog::logger> appLogger;
	};

#define ENG_LOG_INFO(...) Engine::Log::engineLogger->info(__VA_ARGS__)
#define ENG_LOG_WARN(...) Engine::Log::engineLogger->warn(__VA_ARGS__)
#define ENG_LOG_ERROR(...) Engine::Log::engineLogger->error(__VA_ARGS__)
#define ENG_LOG_TRACE(...) Engine::Log::engineLogger->trace(__VA_ARGS__)

#define APP_LOG_INFO(...) Engine::Log::appLogger->info(__VA_ARGS__)
#define APP_LOG_WARN(...) Engine::Log::appLogger->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) Engine::Log::appLogger->error(__VA_ARGS__)
#define APP_LOG_TRACE(...) Engine::Log::appLogger->trace(__VA_ARGS__)
}
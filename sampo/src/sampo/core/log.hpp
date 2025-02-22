#pragma once
#include "sampo/core/core_definitions.hpp"

#pragma warning(push, 0)
	#include <spdlog/spdlog.h>
	#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Sampo {

	class Log
	{
	public:
		static void Create();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define SAMPO_CORE_TRACE(...)    ::Sampo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SAMPO_CORE_INFO(...)     ::Sampo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SAMPO_CORE_WARN(...)     ::Sampo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SAMPO_CORE_ERROR(...)    ::Sampo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SAMPO_CORE_CRITICAL(...) ::Sampo::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SAMPO_TRACE(...)         ::Sampo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SAMPO_INFO(...)          ::Sampo::Log::GetClientLogger()->info(__VA_ARGS__)
#define SAMPO_WARN(...)          ::Sampo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SAMPO_ERROR(...)         ::Sampo::Log::GetClientLogger()->error(__VA_ARGS__)
#define SAMPO_CRITICAL(...)      ::Sampo::Log::GetClientLogger()->critical(__VA_ARGS__)
#include "sampo_pch.hpp"
#include "log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Sampo {

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Create()
    {
        if (s_CoreLogger || s_ClientLogger)
            return;

        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(Sampo::CreateRef<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(Sampo::CreateRef<spdlog::sinks::basic_file_sink_mt>("Sampo.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_CoreLogger = Sampo::CreateRef<spdlog::logger>("SAMPO", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);

        s_ClientLogger = Sampo::CreateRef<spdlog::logger>("APP", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::trace);
    }

}

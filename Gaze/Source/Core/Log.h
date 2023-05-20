#ifndef GAZEENGINE_LOG_H
#define GAZEENGINE_LOG_H

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Gaze {
    class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define GZ_CORE_TRACE(...)    ::Gaze::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GZ_CORE_INFO(...)     ::Gaze::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GZ_CORE_WARN(...)     ::Gaze::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GZ_CORE_ERROR(...)    ::Gaze::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GZ_CORE_CRITICAL(...) ::Gaze::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GZ_TRACE(...)         ::Gaze::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GZ_INFO(...)          ::Gaze::Log::GetClientLogger()->info(__VA_ARGS__)
#define GZ_WARN(...)          ::Gaze::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GZ_ERROR(...)         ::Gaze::Log::GetClientLogger()->error(__VA_ARGS__)
#define GZ_CRITICAL(...)      ::Gaze::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif //GAZEENGINE_LOG_H

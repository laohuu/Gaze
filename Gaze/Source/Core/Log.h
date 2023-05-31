#ifndef GAZEENGINE_LOG_H
#define GAZEENGINE_LOG_H

#include "Core.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/string_cast.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Gaze {
    class Log {
    public:
        static void Init();

        static Gaze::Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

        static Gaze::Ref<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static Gaze::Ref<spdlog::logger> s_CoreLogger;
        static Gaze::Ref<spdlog::logger> s_ClientLogger;
    };
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::vec<L, T, Q> &vector) {
    return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::mat<C, R, T, Q> &matrix) {
    return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, glm::qua<T, Q> quaternion) {
    return os << glm::to_string(quaternion);
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

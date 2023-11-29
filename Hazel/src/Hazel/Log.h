#pragma once

#include "spdlog/spdlog.h"

#include "Core.h"

namespace Hazel {

class HAZEL_API Log{
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger; };
	inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; };

private:
	static std::shared_ptr<spdlog::logger> s_core_logger;
	static std::shared_ptr<spdlog::logger> s_client_logger;

};

}// namespace Hazel

// Core Log Macros
#define HZ_CORE_ERROR(...) ::Hazel::Log::get_core_logger()->error(__VA_ARGS__)
#define HZ_CORE_WARN(...)  ::Hazel::Log::get_core_logger()->warn(__VA_ARGS__)
#define HZ_CORE_INFO(...)  ::Hazel::Log::get_core_logger()->info(__VA_ARGS__)
#define HZ_CORE_TRACE(...) ::Hazel::Log::get_core_logger()->trace(__VA_ARGS__)
#define HZ_CORE_FATAL(...) ::Hazel::Log::get_core_logger()->fatal(__VA_ARGS__)

// Client Log Macros
#define HZ_ERROR(...) ::Hazel::Log::get_client_logger()->error(__VA_ARGS__)
#define HZ_WARN(...)  ::Hazel::Log::get_client_logger()->warn(__VA_ARGS__)
#define HZ_INFO(...)  ::Hazel::Log::get_client_logger()->info(__VA_ARGS__)
#define HZ_TRACE(...) ::Hazel::Log::get_client_logger()->trace(__VA_ARGS__)
#define HZ_FATAL(...) ::Hazel::Log::get_client_logger()->fatal(__VA_ARGS__)
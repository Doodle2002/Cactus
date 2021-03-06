#pragma once

#include "Cactus/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Cactus {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;  
	};
}

#define CACTUS_CORE_TRACE(...) ::Cactus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CACTUS_CORE_INFO(...) ::Cactus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CACTUS_CORE_WARN(...) ::Cactus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CACTUS_CORE_ERROR(...) ::Cactus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CACTUS_CORE_FATAL(...) ::Cactus::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define CACTUS_TRACE(...) ::Cactus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CACTUS_INFO(...) ::Cactus::Log::GetClientLogger()->info(__VA_ARGS__)
#define CACTUS_WARN(...) ::Cactus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CACTUS_ERROR(...) ::Cactus::Log::GetClientLogger()->error(__VA_ARGS__)
#define CACTUS_FATAL(...) ::Cactus::Log::GetClientLogger()->fatal(__VA_ARGS__)


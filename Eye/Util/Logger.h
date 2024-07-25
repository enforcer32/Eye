#pragma once

#include <spdlog/spdlog.h>

#include <string>
#include <memory>
#include <vector>
#include <sstream>

namespace EYE
{
	class Logger
	{
	public:
		static void Init(const std::string& name = "EYELogger");
		static void Destroy();
		inline static std::shared_ptr<spdlog::logger> GetLogger() { return s_Logger; }

		static void SaveLastLog();
		static void Clear();
		static const std::vector<std::string>& GetLogs();

	private:
		inline static std::shared_ptr<spdlog::logger> s_Logger;
		inline static std::vector<std::string> s_Logs;
		inline static std::ostringstream s_Stream;
	};
}

#define EYE_LOG_INFO(...)		(EYE::Logger::GetLogger()->info(__VA_ARGS__), EYE::Logger::SaveLastLog())
#define EYE_LOG_WARN(...)		(EYE::Logger::GetLogger()->warn(__VA_ARGS__), EYE::Logger::SaveLastLog())
#ifdef EYE_DEBUG
	#define EYE_LOG_DEBUG(...)		(EYE::Logger::GetLogger()->debug(__VA_ARGS__), EYE::Logger::SaveLastLog())
#else
	#define EYE_LOG_DEBUG(...)
#endif
#define EYE_LOG_ERROR(...)		(EYE::Logger::GetLogger()->error(__VA_ARGS__), EYE::Logger::SaveLastLog())
#define EYE_LOG_CRITICAL(...)	(EYE::Logger::GetLogger()->critical(__VA_ARGS__), EYE::Logger::SaveLastLog(), throw)
#define EYE_LOG_TRACE(...)		(EYE::Logger::GetLogger()->trace(__VA_ARGS__), EYE::Logger::SaveLastLog(), __VA_ARGS__))

#pragma once

#include <spdlog/spdlog.h>

#include <string>
#include <sstream>
#include <memory>

namespace Eye
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

#define EYE_LOG_INFO(...)		(Eye::Logger::GetLogger()->info(__VA_ARGS__), Eye::Logger::SaveLastLog())
#define EYE_LOG_WARN(...)		(Eye::Logger::GetLogger()->warn(__VA_ARGS__), Eye::Logger::SaveLastLog())
#ifdef EYE_DEBUG
	#define EYE_LOG_DEBUG(...)		(Eye::Logger::GetLogger()->debug(__VA_ARGS__), Eye::Logger::SaveLastLog())
#else
	#define EYE_LOG_DEBUG(...)
#endif
#define EYE_LOG_ERROR(...)		(Eye::Logger::GetLogger()->error(__VA_ARGS__), Eye::Logger::SaveLastLog())
#define EYE_LOG_CRITICAL(...)	(Eye::Logger::GetLogger()->critical(__VA_ARGS__), Eye::Logger::SaveLastLog(), throw)
#define EYE_LOG_TRACE(...)		(Eye::Logger::GetLogger()->trace(__VA_ARGS__), Eye::Logger::SaveLastLog(), __VA_ARGS__))

#pragma once

#include "cpputils/stringutils.hpp"
#include "cpputils/simplemacros.hpp"

#if CXX_MSVC || CXX_CLANG
#define __SIMPLE_LOG(format_str, log_level, ...) logger::console_print(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__)
#define __ADVANCED_LOG(format_str, log_level, ...) logger::console_print(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__, ##__FILE__)
#if CXX_LEVEL_DEBUG
#define __LOG_FULL_ASSERT(format_str, log_level, ...) { logger::console_print(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__, ##__FILE__); exit(EXIT_FAILURE); }
#else
#define __LOG_FULL_ASSERT(format_str, log_level, ...) { logger::console_print(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__, ##__FILE__); __debugbreak(); exit(EXIT_FAILURE); }
#endif
#elif CXX_GCC
#define __SIMPLE_LOG(format_str, log_level, ...) logger::console_print(log_level, stringutils::format(format_str, ##__VA_ARGS__), __FUNCTION__, __LINE__)
#define __ADVANCED_LOG(format_str, log_level, ...) logger::console_print(log_level, stringutils::format(format_str, ##__VA_ARGS__), __FUNCTION__, __LINE__, __FILE__)
#define __LOG_FULL_ASSERT(format_str, log_level, ...) { logger::console_print(log_level, stringutils::format(format_str, ##__VA_ARGS__), __FUNCTION__, __LINE__, __FILE__); exit(EXIT_FAILURE); }
#endif

#if CXX_MSVC
#define LOG_FATAL(format_str, ...) __LOG_FULL_ASSERT(format_str, logger::LogType::LOG_LEVEL_FATAL, __VA_ARGS__)
#define LOG_VALIDATE(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_VALIDATE, __VA_ARGS__)
#define LOG_ERROR(format_str, ...) __ADVANCED_LOG(format_str, logger::LogType::LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG_WARNING(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_WARNING, __VA_ARGS__)
#define LOG_INFO(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_DEBUG(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_DEBUG, __VA_ARGS__)
#elif CXX_GCC
#define LOG_FATAL(format_str, ...) __LOG_FULL_ASSERT(format_str, logger::LogType::LOG_LEVEL_FATAL, ##__VA_ARGS__)
#define LOG_VALIDATE(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_VALIDATE, ##__VA_ARGS__)
#define LOG_ERROR(format_str, ...) __ADVANCED_LOG(format_str, logger::LogType::LOG_LEVEL_ERROR, ##__VA_ARGS__)
#define LOG_WARNING(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_WARNING, ##__VA_ARGS__)
#define LOG_INFO(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_INFO, ##__VA_ARGS__)
#define LOG_DEBUG(format_str, ...) __SIMPLE_LOG(format_str, logger::LogType::LOG_LEVEL_DEBUG, ##__VA_ARGS__)
#endif

namespace logger
{
	enum LogType {
		LOG_LEVEL_FATAL = 1 << 0,
		LOG_LEVEL_VALIDATE = 1 << 1,
		LOG_LEVEL_ERROR = 1 << 2,
		LOG_LEVEL_WARNING = 1 << 3,
		LOG_LEVEL_INFO = 1 << 4,
		LOG_LEVEL_DEBUG = 1 << 5,
	};

	/**
	 * print a log to terminal stdout (with colors)
	 */
	void console_print(LogType log_type, const std::string& message, const char* function = nullptr, size_t line = 0, const char* file = nullptr);

	/**
	 * Threads can be identified with a custom ID.
	 * return 255 if thread is unknown.
	 *
	 * ie : logger_set_thread_identifier_func([] () -> uint8_t { return is_worker_thread() ? return get_worker_thread_id() : 255 });
	 */
	void set_thread_identifier_func(uint8_t(*getter)());


	[[nodiscard]] inline char get_log_level_char(const logger::LogType log_level)
	{
		switch (log_level)
		{
		case logger::LogType::LOG_LEVEL_VALIDATE:
			return 'V';
		case logger::LogType::LOG_LEVEL_ERROR:
			return 'E';
		case logger::LogType::LOG_LEVEL_WARNING:
			return 'W';
		case logger::LogType::LOG_LEVEL_INFO:
			return 'I';
		case logger::LogType::LOG_LEVEL_DEBUG:
			return 'D';
		case logger::LogType::LOG_LEVEL_FATAL:
			return 'F';
		}
		return 'X';
	}
}

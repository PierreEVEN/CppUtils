#pragma once

#include "cpputils/stringutils.hpp"
#include "cpputils/simplemacros.hpp"

#include <filesystem>

#if CXX_MSVC || CXX_CLANG
#if CXX_LEVEL_DEBUG
#define __SIMPLE_LOG(format_str, log_level, ...) logger::log(logger::LogItem(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__))
#define __ADVANCED_LOG(format_str, log_level, ...) logger::log(logger::LogItem(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__, ##__FILE__))
#define __LOG_FULL_ASSERT(format_str, log_level, ...) { logger::log(logger::LogItem(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__, ##__FILE__)); __debugbreak(); exit(EXIT_FAILURE); }
#else
#define __SIMPLE_LOG(format_str, log_level, ...) logger::log(logger::LogItem(log_level, stringutils::format(format_str, __VA_ARGS__))
#define __ADVANCED_LOG(format_str, log_level, ...) logger::log(logger::LogItem(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__, ##__FILE__)
#define __LOG_FULL_ASSERT(format_str, log_level, ...) { logger::log(logger::LogItem(log_level, stringutils::format(format_str, __VA_ARGS__), ##__FUNCTION__, __LINE__, ##__FILE__); exit(EXIT_FAILURE); }
#endif
#elif CXX_GCC
#define __SIMPLE_LOG(format_str, log_level, ...) logger::log(logger::LogItem(log_level, stringutils::format(format_str, ##__VA_ARGS__), __FUNCTION__, __LINE__))
#define __ADVANCED_LOG(format_str, log_level, ...) logger::log(logger::LogItem(log_level, stringutils::format(format_str, ##__VA_ARGS__), __FUNCTION__, __LINE__, __FILE__))
#define __LOG_FULL_ASSERT(format_str, log_level, ...) { logger::log(logger::LogItem(log_level, stringutils::format(format_str, ##__VA_ARGS__), __FUNCTION__, __LINE__, __FILE__)); exit(EXIT_FAILURE); }
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

	
	struct LogItem
	{
		LogItem(LogType in_log_level, const std::string& in_message, const char* in_function = nullptr, size_t in_line = 0, const char* in_file = nullptr)
			: log_level(in_log_level), message(in_message), function(in_function), line(in_line), file(in_file) {}

		LogType log_level;
		std::string message;
		const char* function;
		size_t line;
		const char* file;
	};
	
	typedef void(*LogFunctionType)(const LogItem& in_log);
	typedef uint8_t(*ThreadIdentifierFunctionType)();


	[[nodiscard]] LogFunctionType get_log_function();
	void set_log_function(LogFunctionType in_function);
	void set_log_file(const std::string& file);
	
	/**
	 * print a log to terminal stdout (with colors)
	 */
	void log(const LogItem& in_log);

	void console_print(const LogItem& in_log);
	void file_print(const LogItem& in_log);
	
	/**
	 * Threads can be identified with a custom ID.
	 * return 255 if thread is unknown.
	 *
	 * ie : logger_set_thread_identifier_func([] () -> uint8_t { return is_worker_thread() ? return get_worker_thread_id() : 255 });
	 */
	void set_thread_identifier(ThreadIdentifierFunctionType func);
	[[nodiscard]] ThreadIdentifierFunctionType get_thread_identifier();

	[[nodiscard]] char get_log_level_char(const logger::LogType log_level);	
}
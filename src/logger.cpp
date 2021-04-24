

#include "cpputils/logger.hpp"

#include <filesystem>
#include <fstream>
#include <mutex>


static logger::ThreadIdentifierFunctionType thread_identifier;
extern logger::LogFunctionType log_function;

char logger::get_log_level_char(const LogType log_level)
{
	switch (log_level)
	{
	case LOG_LEVEL_VALIDATE:
		return 'V';
	case LOG_LEVEL_ERROR:
		return 'E';
	case LOG_LEVEL_WARNING:
		return 'W';
	case LOG_LEVEL_INFO:
		return 'I';
	case LOG_LEVEL_DEBUG:
		return 'D';
	case LOG_LEVEL_FATAL:
		return 'F';
	}
	return 'X';
}

logger::LogFunctionType logger::get_log_function()
{
	return log_function;
}

void logger::set_log_function(LogFunctionType in_function)
{
	log_function = in_function;
}

void logger::log(const LogItem& in_log)
{
	if (get_log_function()) get_log_function()(in_log);
}

logger::LogFunctionType get_log_function()
{
	return log_function;
}

void logger::set_thread_identifier(ThreadIdentifierFunctionType func)
{
	thread_identifier = func;
}

logger::ThreadIdentifierFunctionType logger::get_thread_identifier()
{
	return thread_identifier;
}

struct LogFileManager
{
	LogFileManager(std::string log_file = "./saved/log/Log - %s.log")
	{
		const auto log_folder = std::filesystem::path(log_file).parent_path();
		if (!exists(log_folder)) create_directories(log_folder);

		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
#if OS_WINDOWS
		localtime_s(&tstruct, &now);
#else
		localtime_r(&now, &tstruct);
#endif
		strftime(buf, sizeof(buf), "%Y-%m-%d.%H.%M.%S", &tstruct);
		
		file = std::ofstream(stringutils::format(log_file.c_str(), buf));
	}

	void concatenate(const std::string& value)
	{
		file << value;
		file.flush();
	}

	~LogFileManager()
	{
		if (file) file.close();
	}

	std::ofstream file;
};
std::unique_ptr<LogFileManager> file_manager;


void logger::set_log_file(const std::string& file)
{
	file_manager = std::make_unique<LogFileManager>(file);
}
void logger::file_print(const LogItem& in_log)
{
	if (!file_manager || !file_manager->file) return;

	file_manager->concatenate("test : " + in_log.message + "\n");
}

std::mutex logger_lock;

logger::LogFunctionType log_function = [](const logger::LogItem& in_log)
{
	std::lock_guard<std::mutex> lock(logger_lock);
	file_print(in_log);
	console_print(in_log);
};
#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <vector>

namespace stringutils
{
	/**
	 * Format string.
	 * stringutils::format("%d is not a string, %s is a string, 10, "this");
	 * \param format format
	 * \param ...args arguments
	 * \return string
	 */
	template<typename... Params>
	[[nodiscard]] std::string format(const char* format, const Params... args) {
		const int size = snprintf(nullptr, 0, format, args...) + 1;
		if (size <= 0) return format;
		const std::unique_ptr<char[]> buffer(new char[size]);
		snprintf(buffer.get(), size, format, args ...);
		return std::string(buffer.get());
	}

	typedef bool(*trim_filter_func)(char);

	[[nodiscard]] inline bool default_trim_func(char chr)
	{
		return chr == ' ' || chr == '\t' || chr == '\n' || chr == '\r';
	}
	
	[[nodiscard]] inline std::string trim(const std::string& source, const trim_filter_func filter = default_trim_func)
	{
		if (source.empty()) return "";
		assert(filter);
		size_t start = 0, end = source.size();

		while (filter(source[start]))
		{
			if (start == end - 1) return "";
			start++;
		}

		while (filter(source[--end])) {}
		return std::string(source.begin() + start, source.begin() + end + 1);
	}

	[[nodiscard]] inline std::vector<std::string> split(const std::string& source, const std::vector<char>& delimiters)
	{
		return {};
	}
	
	
}


#include <cpputils/logger.hpp>
#include <cpputils/stringutils.hpp>
#include <thread>

int main(int argc, char* agv[])
{
	logger::set_log_file("./saved/log/Log - %s.log");
	
	std::string res = "|" + stringutils::trim(" \t\r\n		  un beau string au bon format \r\t\n	 ") + "|";
	
    std::thread([] () {
        LOG_INFO("THREAD_TEST");
    }).join();
    std::thread([] () {
        LOG_INFO("THREAD_TEST 2");
    }).join();

    logger::set_thread_identifier([] () -> uint8_t { return rand() % 255; });

	LOG_VALIDATE("validate");
	LOG_VALIDATE("coucou : %s", res.c_str());

	LOG_INFO("%s : %s", stringutils::array_to_string<int>({ 1, 2, 3, 4 }).c_str(), stringutils::array_to_string<std::string>({ "1", "deux", "3" }).c_str());

	
	LOG_ERROR("error");
	LOG_ERROR("coucou : %s", res.c_str());

	LOG_WARNING("warning");
	LOG_WARNING("coucou : %s", res.c_str());

	LOG_INFO("info");
	LOG_INFO("coucou : %s", res.c_str());

	LOG_DEBUG("debug");
	LOG_DEBUG("coucou : %s", res.c_str());

	LOG_FATAL("fatal");
	LOG_FATAL("coucou : %s", res.c_str());	
}


#include <cpputils/logger.hpp>
#include <cpputils/stringutils.hpp>
#include <thread>

int main(int argc, char* agv[])
{
	std::string res = "|" + stringutils::trim("a  azdz  a  a") + "|";


    std::thread([] () {
        LOG_INFO("THREAD_TEST");
    }).join();
    std::thread([] () {
        LOG_INFO("THREAD_TEST 2");
    }).join();

    logger::set_thread_identifier_func([] () -> uint8_t { return rand() % 255; });

	LOG_VALIDATE("validate");
	LOG_VALIDATE("coucou : %s", res.c_str());

	LOG_ERROR("error");
	LOG_ERROR("coucou : %s", res.c_str());

	LOG_WARNING("warning");
	LOG_WARNING("coucou : %s", res.c_str());

	LOG_INFO("info");
	LOG_INFO("coucou : %s", res.c_str());

	LOG_DEBUG("debug");
	LOG_DEBUG("debug : %s", res.c_str());

	LOG_FATAL("fatal");
	LOG_FATAL("fatal : %s", res.c_str());


}

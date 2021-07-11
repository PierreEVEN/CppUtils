
#include <cpputils/eventmanager.hpp>
#include <cpputils/logger.hpp>
#include <cpputils/stringutils.hpp>
#include <thread>

DECLARE_DELEGATE_MULTICAST(MyDelegate, float, bool);
DECLARE_DELEGATE_MULTICAST(MyDelegate2, const float, const bool);
DECLARE_DELEGATE_MULTICAST(MyDelegate3, const float&, const bool&);
DECLARE_DELEGATE_MULTICAST(MyDelegate4, float&, bool&);

struct InputAction
{
    
};

DECLARE_DELEGATE_MULTICAST(InputCall, const InputAction&, const double);

class TestFoo
{
  public:
    void test_foo(float test_fl)
    {
        my_delegate.add_object(this, &TestFoo::delega);
        my_delegate.add_lambda([](float a, bool b) {
            LOG_INFO("ok lambda a %f, %d", a, b);
        });
        my_delegate.execute(test_fl, false);

        my_delegateb.add_object(this, &TestFoo::delegb);
        my_delegateb.add_lambda([](const float a, const bool b) {
            LOG_INFO("ok lambda a %f, %d", a, b);
        });
        my_delegateb.execute(test_fl, false);

        my_delegatec.add_object(this, &TestFoo::delegc);
        my_delegatec.add_lambda([](const float& a, const bool& b) {
            LOG_INFO("ok lambda a %f, %d", a, b);
        });
        my_delegatec.execute(test_fl, false);

        my_delegated.add_object(this, &TestFoo::delegd);
        my_delegated.add_lambda([](float& a, bool& b) {
            LOG_INFO("ok lambda a %f, %d", a, b);
        });

        float val  = 0.5;
        bool  val2 = false;
        my_delegated.execute(val, val2);

        input_call.add_object(this, &TestFoo::inp);
        input_call.execute(InputAction(), 2.0);
    }

  private:
    void delega(float a, bool b)
    {
        LOG_INFO("ok a %f, %d", a, b);
    }

    void delegb(const float a, const bool b)
    {
        LOG_INFO("ok b %f, %d", a, b);
    }
    void delegc(const float& a, const bool& b)
    {
        LOG_INFO("ok c %f, %d", a, b);
    }
    void delegd(float& a, bool& b)
    {
        LOG_INFO("ok c %f, %d", a, b);
    }

    void inp(const InputAction& a, const double b)
    {
        LOG_INFO("ok inp %lf", b);
    }

    MyDelegate  my_delegate;
    MyDelegate2 my_delegateb;
    MyDelegate3 my_delegatec;
    MyDelegate4 my_delegated;
    InputCall   input_call;
};

int main(int argc, char* agv[])
{

    Logger::get().set_log_file("./saved/log/Log - %s.log");
    Logger::get().enable_logs(Logger::LOG_LEVEL_TRACE | Logger::LOG_LEVEL_DEBUG | Logger::LOG_LEVEL_INFO);

    Logger::get().set_thread_identifier([]() -> uint8_t {
        return rand() % 255;
    });

    TestFoo test_foo;
    test_foo.test_foo(5.68f);

    std::string res = "|" + stringutils::trim(" \t\r\n		  un beau string au bon format \r\t\n	 ") + "|";

    std::thread([]() {
        LOG_INFO("THREAD_TEST");
    }).join();
    std::thread([]() {
        LOG_INFO("THREAD_TEST 2");
    }).join();

    LOG_VALIDATE("validate");
    LOG_VALIDATE("coucou : %s", res.c_str());

    LOG_INFO("%s : %s", stringutils::array_to_string<int>({1, 2, 3, 4}).c_str(), stringutils::array_to_string<std::string>({"1", "deux", "3"}).c_str());

    LOG_ERROR("error");
    LOG_ERROR("coucou : %s", res.c_str());

    LOG_WARNING("warning");
    LOG_WARNING("coucou : %s", res.c_str());

    LOG_INFO("info");
    LOG_INFO("coucou : %s", res.c_str());

    LOG_DEBUG("debug");
    LOG_DEBUG("coucou : %s", res.c_str());

    LOG_TRACE("Trace");
    LOG_TRACE("coucou : %s", res.c_str());

    LOG_FATAL("fatal");
    LOG_FATAL("coucou : %s", res.c_str());
}
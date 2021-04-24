

#include <cpputils>


class TestObject
{
public:
	void test_func()
	{
        logger_log("1");
	}
};


int main(int argc, char* agv[])
{
	TestObject test_obj;

	std::string res = "|" + stringutils::trim("a  azdz  a  a") + "|";
	
	logger_fail(res.c_str());

	
	logger_log("test : %d", 10);
}

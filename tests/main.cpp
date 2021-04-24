

#include <cpputils>

DECLARE_DELEGATE_SINGLECAST(TestDelegate);

TestDelegate MyDelegate;

class TestObject
{
public:
	void test_func()
	{
		logger_log("called test func");
	}
};


int main(int argc, char* agv[])
{
	TestObject test_obj;
	
	MyDelegate.Bind(&test_obj, &TestObject::test_func);

	MyDelegate.Execute();

	std::string res = "|" + stringutils::trim("a  azdz  a  a") + "|";
	
	logger_log("%s", res.c_str());

	
	logger_log("test : %d", 10);
}

#include <iostream>

class TestClass
{
public:
	void TestFunc(void (*cb)())
	{
		printf("in func");
		cb();
	}
};

class TestClass2
{
public:
	int i = 2;
	void TestFunc()
	{
		printf(i);
	}
}

int
main()
{
	TestClass testClass;
	TestClass2 testClass2;
	testClass.TestFunc([&]() { testclass2.TestFunc(); });
	return 0;
}
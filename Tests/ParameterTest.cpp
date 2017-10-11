#include <iostream>
#include <assert.h>
#include "TestParameterObject.h"
#include <math.h>

void paramTest();

using namespace std;
using namespace GenParam;

// main 
int main( int argc, char **argv )
{
	paramTest();

	return 0;
}

void paramTest()
{
	TestParameterObject tc;
	assert(tc.numParameters() == 3);

	auto boolParam = std::static_pointer_cast<BoolParameter>(tc.getParameter(TestParameterObject::MY_BOOL_PARAMETER));
	assert(boolParam->getValue() == true);
	assert(tc.getBool(TestParameterObject::MY_BOOL_PARAMETER) == true);

	auto intParam = std::static_pointer_cast<IntParameter>(tc.getParameter(TestParameterObject::MY_INT_PARAMETER));
	std::cout << intParam->getValue() << "\n";
	assert(intParam->getValue() == 3);
	assert(tc.getInt(TestParameterObject::MY_INT_PARAMETER) == 3);


	std::cout << "Success\n";
}

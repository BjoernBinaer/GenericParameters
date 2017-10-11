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
	assert(intParam->getValue() == 3);
	assert(tc.getInt(TestParameterObject::MY_INT_PARAMETER) == 3);

	auto doubleParam = std::static_pointer_cast<DoubleParameter>(tc.getParameter(TestParameterObject::MY_DOUBLE_PARAMETER));
	assert(doubleParam->getValue() == 3.123);
	assert(tc.getDouble(TestParameterObject::MY_DOUBLE_PARAMETER) == 3.123);
	tc.setDouble(TestParameterObject::MY_DOUBLE_PARAMETER, 4.85);
	assert(tc.getDouble(TestParameterObject::MY_DOUBLE_PARAMETER) == 4.85);


	std::cout << "Success\n";
}

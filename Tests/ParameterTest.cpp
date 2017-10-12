#include <iostream>
#include <assert.h>
#include "TestParameterObject.h"
#include <math.h>
#include "GenericParameters/EnumParameter.h"

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
	assert(tc.numParameters() == 4);

	auto boolParam = std::static_pointer_cast<BoolParameter>(tc.getParameter(TestParameterObject::MY_BOOL_PARAMETER));
	assert(boolParam->getValue() == true);
	assert(tc.getValue<bool>(TestParameterObject::MY_BOOL_PARAMETER) == true);

	auto intParam = std::static_pointer_cast<IntParameter>(tc.getParameter(TestParameterObject::MY_INT_PARAMETER));
	assert(intParam->getValue() == 3);
	assert(tc.getValue<int>(TestParameterObject::MY_INT_PARAMETER) == 3);

	auto doubleParam = std::static_pointer_cast<DoubleParameter>(tc.getParameter(TestParameterObject::MY_DOUBLE_PARAMETER));
	assert(doubleParam->getValue() == 3.123);
	assert(tc.getValue<double>(TestParameterObject::MY_DOUBLE_PARAMETER) == 3.123);
	tc.setValue<double>(TestParameterObject::MY_DOUBLE_PARAMETER, 4.85);
	assert(tc.getValue<double>(TestParameterObject::MY_DOUBLE_PARAMETER) == 4.85);

	auto enumParam = std::static_pointer_cast<EnumParameter>(tc.getParameter(TestParameterObject::MY_ENUM_PARAMETER));
	assert(enumParam->getValue() == TestParameterObject::MY_ENUM_VALUE2);
	assert(tc.getValue<int>(TestParameterObject::MY_ENUM_PARAMETER) == TestParameterObject::MY_ENUM_VALUE2);

	const std::vector<EnumParameter::EnumValue>& enumValues = enumParam->getEnumValues();
	assert(enumValues[0].name == "enum1");
	assert(enumValues[1].name == "enum2");


	std::cout << "Success\n";
}

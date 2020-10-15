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
	assert(tc.numParameters() == 9);

	auto boolParam = static_cast<BoolParameter*>(tc.getParameter(TestParameterObject::MY_BOOL_PARAMETER));
	assert(boolParam->getValue() == true);
	assert(tc.getValue<bool>(TestParameterObject::MY_BOOL_PARAMETER) == true);
	assert(tc.getType(TestParameterObject::MY_BOOL_PARAMETER) == ParameterBase::BOOL);

	auto intParam = static_cast<IntParameter*>(tc.getParameter(TestParameterObject::MY_INT_PARAMETER));
	assert(intParam->getValue() == 3);
	assert(tc.getValue<int>(TestParameterObject::MY_INT_PARAMETER) == 3);
	assert(tc.getType(TestParameterObject::MY_INT_PARAMETER) == ParameterBase::INT32);
	// check max
	tc.setValue<int>(TestParameterObject::MY_INT_PARAMETER, 5);
	assert(tc.getValue<int>(TestParameterObject::MY_INT_PARAMETER) == 4);
	// check min
	tc.setValue<int>(TestParameterObject::MY_INT_PARAMETER, -2);
	assert(tc.getValue<int>(TestParameterObject::MY_INT_PARAMETER) == 2);

	auto doubleParam = static_cast<DoubleParameter*>(tc.getParameter(TestParameterObject::MY_DOUBLE_PARAMETER));
	assert(doubleParam->getValue() == 3.123);
	assert(tc.getValue<double>(TestParameterObject::MY_DOUBLE_PARAMETER) == 3.123);
	tc.setValue<double>(TestParameterObject::MY_DOUBLE_PARAMETER, 4.85);
	assert(tc.getValue<double>(TestParameterObject::MY_DOUBLE_PARAMETER) == 4.85);

	assert(doubleParam->getMinValue() == 0.1);
	assert(doubleParam->getMaxValue() == 0.9);
	assert(tc.getType(TestParameterObject::MY_DOUBLE_PARAMETER) == ParameterBase::DOUBLE);

	auto enumParam = static_cast<EnumParameter*>(tc.getParameter(TestParameterObject::MY_ENUM_PARAMETER));
	assert(enumParam->getValue() == TestParameterObject::MY_ENUM_VALUE2);
	assert(tc.getValue<int>(TestParameterObject::MY_ENUM_PARAMETER) == TestParameterObject::MY_ENUM_VALUE2);
	const std::vector<EnumParameter::EnumValue>& enumValues = enumParam->getEnumValues();
	assert(enumValues[0].name == "enum1");
	assert(enumValues[1].name == "enum2");
	assert(tc.getGroup(TestParameterObject::MY_ENUM_PARAMETER) == "EnumGroup");
	assert(tc.getType(TestParameterObject::MY_ENUM_PARAMETER) == ParameterBase::ENUM);


 	auto enumParam2 = static_cast<EnumParameter*>(tc.getParameter(TestParameterObject::MY_ENUM_PARAMETER2));
 	assert(enumParam2->getValue() == TestParameterObject::MY_ENUM2_VALUE1);
 	assert(tc.getValue<int>(TestParameterObject::MY_ENUM_PARAMETER2) == TestParameterObject::MY_ENUM2_VALUE1);
 	const std::vector<EnumParameter::EnumValue>& enumValues2 = enumParam2->getEnumValues();
 	assert(enumValues2[0].name == "enum3");
 	assert(enumValues2[1].name == "enum4");
 	assert(tc.getGroup(TestParameterObject::MY_ENUM_PARAMETER2) == "ParameterGroup");
 	assert(tc.getType(TestParameterObject::MY_ENUM_PARAMETER2) == ParameterBase::ENUM);
	assert(tc.getReadOnly(TestParameterObject::MY_ENUM_PARAMETER2) == true);
	tc.setValue<int>(TestParameterObject::MY_ENUM_PARAMETER2, TestParameterObject::MY_ENUM2_VALUE2);
	assert(tc.getValue<int>(TestParameterObject::MY_ENUM_PARAMETER2) == TestParameterObject::MY_ENUM2_VALUE1);


	auto strParam = static_cast<StringParameter*>(tc.getParameter(TestParameterObject::MY_STRING_PARAMETER));
	assert(tc.getValue<std::string>(TestParameterObject::MY_STRING_PARAMETER) == "test string");
    strParam->setValue("other test string");
    assert(tc.getValue<std::string>(TestParameterObject::MY_STRING_PARAMETER) == "other test string");
	assert(tc.getType(TestParameterObject::MY_STRING_PARAMETER) == ParameterBase::STRING);

	auto vec3Param = static_cast<DoubleVectorParameter*>(tc.getParameter(TestParameterObject::MY_VEC3_PARAMETER));
	double *vecValue;
	vecValue = vec3Param->getValue();
	assert(vecValue[0] == 1.1);
	assert(vecValue[1] == 2.2);
	assert(vecValue[2] == -3.5);
	assert(vecValue == tc.getVecValue<double>(TestParameterObject::MY_VEC3_PARAMETER));
	double newVec[3] = { 2,3,4.5 };
 	tc.setVecValue<double>(TestParameterObject::MY_VEC3_PARAMETER, newVec);
	vecValue = vec3Param->getValue();
	assert(vecValue[0] == 2.0);
	assert(vecValue[1] == 3);
	assert(vecValue[2] == 4.5);
 	assert(tc.getType(TestParameterObject::MY_VEC3_PARAMETER) == ParameterBase::VEC_DOUBLE);


 	auto structParam = dynamic_cast<StructParameter*>(tc.getParameter(TestParameterObject::MY_STRUCT_PARAMETER));
    {
        auto param = dynamic_cast<Parameter<int>*>(structParam->getParameter(TestParameterObject::MY_STRUCT_PARAMETERS[0]));
        assert(param->getValue() == 1);
        param->setValue(20);
        assert(param->getValue() == 20);
        param->setValue(1);
        assert(param->getValue() == 1);
    }
    {
        auto param = dynamic_cast<DoubleParameter*>(structParam->getParameter(TestParameterObject::MY_STRUCT_PARAMETERS[1]));
        assert(param->getValue() == 2.3);
        param->setValue(35.2);
        assert(param->getValue() == 35.2);
        param->setValue(2.3);
        assert(param->getValue() == 2.3);
    }
    {
        auto param = dynamic_cast<StringParameter*>(structParam->getParameter(TestParameterObject::MY_STRUCT_PARAMETERS[2]));
        assert(param->getValue() == "Hello GenericParams");
        param->setValue("Hello someone else");
        assert(param->getValue() == "Hello someone else");
        param->setValue("Hello GenericParams");
        assert(param->getValue() == "Hello GenericParams");
    }
    {
        auto param = dynamic_cast<DoubleVectorParameter*>(structParam->getParameter(TestParameterObject::MY_STRUCT_PARAMETERS[3]));
        assert(param->getValue()[0] == 3.2); assert(param->getValue()[1] == 4.5); assert(param->getValue()[2] == 3.3);
        double other_vals[3] = {5.5, 6.6, 7.7};
        param->setValue(other_vals);
        assert(param->getValue()[0] == 5.5); assert(param->getValue()[1] == 6.6); assert(param->getValue()[2] == 7.7);
        other_vals[0] = 3.2; other_vals[1] = 4.5; other_vals[2] = 3.3;
        param->setValue(other_vals);
        assert(param->getValue()[0] == 3.2); assert(param->getValue()[1] == 4.5); assert(param->getValue()[2] == 3.3);
    }


    auto listParam = dynamic_cast<ListParameter*>(tc.getParameter(TestParameterObject::MY_LIST_PARAMETER));
    assert(listParam->size() == 2);
    {
        auto param = dynamic_cast<Parameter<int>*>(listParam->getParameter(TestParameterObject::MY_LIST_PARAMETERS[0]));
        listParam->setIndex(0); assert(param->getValue() == 1);
        listParam->setIndex(1); assert(param->getValue() == 2);
    }
    {
        auto param = dynamic_cast<DoubleParameter*>(listParam->getParameter(TestParameterObject::MY_LIST_PARAMETERS[1]));
        listParam->setIndex(0); assert(param->getValue() == 2.3);
        listParam->setIndex(1); assert(param->getValue() == 4.2);
    }
    {
        auto param = dynamic_cast<StringParameter*>(listParam->getParameter(TestParameterObject::MY_LIST_PARAMETERS[2]));
        listParam->setIndex(0); assert(param->getValue() == "Hello GenericParams");
        listParam->setIndex(1); assert(param->getValue() == "GenericParams");
    }
    {
        auto param = dynamic_cast<VectorParameter<double>*>(listParam->getParameter(TestParameterObject::MY_LIST_PARAMETERS[3]));
        listParam->setIndex(0);
        assert(param->getValue()[0] == 3.2); assert(param->getValue()[1] == 4.5); assert(param->getValue()[2] == 3.3);
        listParam->setIndex(1);
        assert(param->getValue()[0] == 1.2); assert(param->getValue()[1] == 4.2); assert(param->getValue()[2] == 6.3);
    }


	std::cout << "Success\n";
}

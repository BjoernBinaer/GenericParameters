
#include "TestParameterObject.h"
#include "GenericParameters/EnumParameter.h"
#include <memory>

using namespace GenParam;

int GenParam::TestParameterObject::MY_BOOL_PARAMETER = -1;
int GenParam::TestParameterObject::MY_INT_PARAMETER = -1;
int GenParam::TestParameterObject::MY_DOUBLE_PARAMETER = -1;
int GenParam::TestParameterObject::MY_ENUM_PARAMETER = -1;
int GenParam::TestParameterObject::MY_ENUM_PARAMETER2 = -1;
int GenParam::TestParameterObject::MY_STRING_PARAMETER = -1;

int GenParam::TestParameterObject::MY_ENUM_VALUE1 = -1;
int GenParam::TestParameterObject::MY_ENUM_VALUE2 = -1;
int GenParam::TestParameterObject::MY_ENUM2_VALUE1 = -1;
int GenParam::TestParameterObject::MY_ENUM2_VALUE2 = -1;

void TestParameterObject::initParameters()
{
	ParameterObject::initParameters();

	m_boolValue = true;
	MY_BOOL_PARAMETER = createBoolParameter("boolParam", "Bool param", &m_boolValue);
	setGroup(MY_BOOL_PARAMETER, "ParameterGroup");
	setDescription(MY_BOOL_PARAMETER, "Help text");

	m_intValue = 3;
	MY_INT_PARAMETER = createNumericParameter("intParam", "Int param", &m_intValue);
	setGroup(MY_INT_PARAMETER, "ParameterGroup");
	setDescription(MY_INT_PARAMETER, "Help text");

	setDoubleValue(3.123);
	ParameterBase::GetFunc<double> getFct = std::bind(&TestParameterObject::getDoubleValue, this);
	ParameterBase::SetFunc<double> setFct = std::bind(&TestParameterObject::setDoubleValue, this, std::placeholders::_1);
	MY_DOUBLE_PARAMETER = createNumericParameter("doubleParam", "Double param", getFct, setFct);
	setGroup(MY_DOUBLE_PARAMETER, "ParameterGroup");
	setDescription(MY_DOUBLE_PARAMETER, "Help text");
	DoubleParameter* doubleParam = static_cast<DoubleParameter*>(getParameter(MY_DOUBLE_PARAMETER));
	doubleParam->setMinValue(0.1);
	doubleParam->setMaxValue(0.9);

	m_enumValue = 1;
	MY_ENUM_PARAMETER = createEnumParameter("enumParam", "Enum param", &m_enumValue);
	EnumParameter* enumParam = static_cast<EnumParameter*>(getParameter(MY_ENUM_PARAMETER));
	enumParam->addEnumValue("enum1", MY_ENUM_VALUE1);
	enumParam->addEnumValue("enum2", MY_ENUM_VALUE2);
	enumParam->setGroup("EnumGroup");
	enumParam->setDescription("This is an enum.");

	m_enumValue2 = 0;
	ParameterBase::GetFunc<int> getFct2 = std::bind(&TestParameterObject::getEnumValue2, this);
	MY_ENUM_PARAMETER2 = createEnumParameter("enumParam2", "Enum param 2", getFct2);
	EnumParameter* enumParam2 = static_cast<EnumParameter*>(getParameter(MY_ENUM_PARAMETER2));
	enumParam2->addEnumValue("enum3", MY_ENUM2_VALUE1);
	enumParam2->addEnumValue("enum4", MY_ENUM2_VALUE2);
	enumParam2->setGroup("EnumGroup");
	setGroup(MY_ENUM_PARAMETER2, "ParameterGroup");
	setDescription(MY_ENUM_PARAMETER2, "Help text");
	setReadOnly(MY_ENUM_PARAMETER2, false);		// Has no influence. Since there is no set function, this must be read-only.

	m_strValue = "test string";
	MY_STRING_PARAMETER = createStringParameter("strParam", "String param", &m_strValue);
	setGroup(MY_STRING_PARAMETER, "ParameterGroup");
	setDescription(MY_STRING_PARAMETER, "Help text");
}



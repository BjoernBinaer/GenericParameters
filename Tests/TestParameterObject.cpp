
#include "TestParameterObject.h"
#include "GenericParameters/EnumParameter.h"
#include <memory>

using namespace GenParam;

int GenParam::TestParameterObject::MY_BOOL_PARAMETER = -1;
int GenParam::TestParameterObject::MY_INT_PARAMETER = -1;
int GenParam::TestParameterObject::MY_DOUBLE_PARAMETER = -1;
int GenParam::TestParameterObject::MY_ENUM_PARAMETER = -1;
int GenParam::TestParameterObject::MY_ENUM_PARAMETER2 = -1;
int GenParam::TestParameterObject::MY_ENUM_VALUE1 = -1;
int GenParam::TestParameterObject::MY_ENUM_VALUE2 = -1;
int GenParam::TestParameterObject::MY_ENUM2_VALUE1 = -1;
int GenParam::TestParameterObject::MY_ENUM2_VALUE2 = -1;

void TestParameterObject::initParameters()
{
	ParameterObject::initParameters();

	m_boolValue = true;
	MY_BOOL_PARAMETER = createParameter("boolParam", "Bool param", ParameterBase::BOOL, &m_boolValue);
	setGroup(MY_BOOL_PARAMETER, "ParameterGroup");
	setDescription(MY_BOOL_PARAMETER, "Help text");

	m_intValue = 3;
	MY_INT_PARAMETER = createParameter("intParam", "Int param", ParameterBase::INT32, &m_intValue);
	setGroup(MY_INT_PARAMETER, "ParameterGroup");
	setDescription(MY_INT_PARAMETER, "Help text");

	setDoubleValue(3.123);
	ParameterBase::GetFunc<double> getFct = std::bind(&TestParameterObject::getDoubleValue, this);
	ParameterBase::SetFunc<double> setFct = std::bind(&TestParameterObject::setDoubleValue, this, std::placeholders::_1);
	MY_DOUBLE_PARAMETER = createParameter("doubleParam", "Double param", ParameterBase::DOUBLE, getFct, setFct);
	setGroup(MY_DOUBLE_PARAMETER, "ParameterGroup");
	setDescription(MY_DOUBLE_PARAMETER, "Help text");
	DoubleParameter::Ptr doubleParam = std::static_pointer_cast<DoubleParameter>(getParameter(MY_DOUBLE_PARAMETER));
	doubleParam->setMinValue(0.1);
	doubleParam->setMaxValue(0.9);

	m_enumValue = 1;
	MY_ENUM_PARAMETER = createParameter("enumParam", "Enum param", ParameterBase::ENUM, &m_enumValue);
	EnumParameter::Ptr enumParam = std::static_pointer_cast<EnumParameter>(getParameter(MY_ENUM_PARAMETER));
	enumParam->addEnumValue("enum1", MY_ENUM_VALUE1);
	enumParam->addEnumValue("enum2", MY_ENUM_VALUE2);
	enumParam->setGroup("EnumGroup");
	enumParam->setDescription("This is an enum.");

	m_enumValue2 = 0;
	ParameterBase::GetFunc<int> getFct2 = std::bind(&TestParameterObject::getEnumValue2, this);
	ParameterBase::SetFunc<int> setFct2 = std::bind(&TestParameterObject::setEnumValue2, this, std::placeholders::_1);
	MY_ENUM_PARAMETER2 = createParameter("enumParam", "Enum param", ParameterBase::ENUM, getFct2, setFct2);
	EnumParameter::Ptr enumParam2 = std::static_pointer_cast<EnumParameter>(getParameter(MY_ENUM_PARAMETER));
	enumParam2->addEnumValue("enum1", MY_ENUM2_VALUE1);
	enumParam2->addEnumValue("enum2", MY_ENUM2_VALUE2);
	enumParam2->setGroup("EnumGroup");
	setGroup(MY_ENUM_PARAMETER2, "ParameterGroup");
	setDescription(MY_ENUM_PARAMETER2, "Help text");
}



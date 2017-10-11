
#include "TestParameterObject.h"

using namespace GenParam;

int GenParam::TestParameterObject::MY_BOOL_PARAMETER = -1;
int GenParam::TestParameterObject::MY_INT_PARAMETER = -1;
int GenParam::TestParameterObject::MY_DOUBLE_PARAMETER = -1;


void TestParameterObject::initParameters()
{
	ParameterObject::initParameters();

	m_boolValue = true;
	MY_BOOL_PARAMETER = createParameter("boolParam", "Bool param", "ParameterGroup", "Help text", ParameterBase::BOOL, &m_boolValue);

	m_intValue = 3;
	MY_INT_PARAMETER = createParameter("intParam", "Int param", "ParameterGroup", "Help text", ParameterBase::INT32, &m_intValue);

	setDoubleValue(3.123);
	ParameterBase::GetFunc<double> getFct = std::bind(&TestParameterObject::getDoubleValue, this);
	ParameterBase::SetFunc<double> setFct = std::bind(&TestParameterObject::setDoubleValue, this, std::placeholders::_1);
	MY_DOUBLE_PARAMETER = createParameter("doubleParam", "Double param", "ParameterGroup", "Help text", ParameterBase::DOUBLE, getFct, setFct);

}



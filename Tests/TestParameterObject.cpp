
#include "TestParameterObject.h"

using namespace GenParam;

int GenParam::TestParameterObject::MY_BOOL_PARAMETER = -1;
int GenParam::TestParameterObject::MY_INT_PARAMETER = -1;
int GenParam::TestParameterObject::MY_DOUBLE_PARAMETER = -1;


void TestParameterObject::initParameters()
{
	ParameterObject::initParameters();

	m_boolValue = true;
	MY_BOOL_PARAMETER = createBoolParameter("boolParam", "Bool param", "ParameterGroup", "Help text", &m_boolValue);

	m_intValue = 3;
	MY_INT_PARAMETER = createIntParameter("intParam", "Int param", "ParameterGroup", "Help text", &m_intValue);

	m_doubleValue = 3;
	MY_DOUBLE_PARAMETER = createDoubleParameter("doubleParam", "Double param", "ParameterGroup", "Help text", &m_doubleValue);

}



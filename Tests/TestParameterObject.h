#ifndef __TestParameterObject_h__
#define __TestParameterObject_h__

#include "GenericParameters/ParameterObject.h"

namespace GenParam
{
	class TestParameterObject : public ParameterObject
	{
	protected:
		bool m_boolValue;
		int m_intValue;
		double m_doubleValue;

	public:
		static int MY_BOOL_PARAMETER;
		static int MY_INT_PARAMETER;
		static int MY_DOUBLE_PARAMETER;
		
		TestParameterObject() { initParameters();  };
		~TestParameterObject() {};

		virtual void initParameters();
	};
}

#endif
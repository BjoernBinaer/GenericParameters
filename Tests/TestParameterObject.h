#ifndef __TestParameterObject_h__
#define __TestParameterObject_h__

#include "GenericParameters/ParameterObject.h"

namespace GenParam
{
	class TestParameterObject : public ParameterObject
	{
	public:
        struct Struct{
            int a;
            double b;
            std::string c;
            double d[3];
        };

	protected:
		bool m_boolValue;
		int m_intValue;		
		double m_doubleValue;
		int m_enumValue;
		int m_enumValue2;
		std::string m_strValue;
		double m_vec3Value[3];
		int m_counter;
		std::vector<Struct> m_struct;

	public:
		static int MY_BOOL_PARAMETER;
		static int MY_INT_PARAMETER;
		static int MY_DOUBLE_PARAMETER;
		static int MY_ENUM_PARAMETER;
		static int MY_ENUM_PARAMETER2;
		static int MY_STRING_PARAMETER;
		static int MY_VEC3_PARAMETER;
		static int MY_FUNCTION_PARAMETER;
        static int MY_STRUCT_PARAMETER;
        static int MY_STRUCT_PARAMETERS[4];
        static int MY_LIST_PARAMETER;
        static int MY_LIST_PARAMETERS[4];

		static int MY_ENUM_VALUE1;
		static int MY_ENUM_VALUE2;
		static int MY_ENUM2_VALUE1;
		static int MY_ENUM2_VALUE2;
		
		TestParameterObject() { initParameters(); m_counter = 0; };
		~TestParameterObject() {};

		virtual void initParameters();
		
		double getDoubleValue() { return m_doubleValue; }
		void setDoubleValue(double val) { m_doubleValue = val; }

		double getIntValue() { return m_intValue; }
		void setIntValue(int val) { m_intValue = val; }

		int getEnumValue2() const { return m_enumValue2; }
	
		int getCounter() const { return m_counter; }
		void setCounter(int val) { m_counter = val; }
	};
}

#endif
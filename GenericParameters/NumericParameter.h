#ifndef __NumericParameter_h__
#define __NumericParameter_h__

#include <functional>
#include <memory>
#include "Parameter.h"
#include <iostream>
#include <float.h>
#include <algorithm>

namespace GenParam
{
	template<typename T>
	class NumericParameter : public Parameter<T>
	{
	protected:
		T m_minValue;
		T m_maxValue;

	public:
		NumericParameter(const std::string& name, const std::string& label,	T* valuePtr)
			: Parameter<T>(name, label, ParameterBase::INT32, valuePtr)
		{
			setType(m_minValue);
			m_maxValue = std::numeric_limits<T>::max();
			m_minValue = std::numeric_limits<T>::lowest();
			m_setValue = [&, valuePtr](T value) { *valuePtr = std::max(std::min(value, m_maxValue), m_minValue); };
		}

		NumericParameter(const std::string& name, const std::string& label, GetFunc<T> getValue, SetFunc<T> setValue)
			: Parameter<T>(name, label, ParameterBase::INT32, getValue, setValue)
		{
			setType(m_minValue);
			m_maxValue = std::numeric_limits<T>::max(); 
			m_minValue = std::numeric_limits<T>::lowest();
		}

		virtual ~NumericParameter() {}
		
		T getMinValue() const { return m_minValue; }
		void setMinValue(const T val) { m_minValue = val; }
		
		T getMaxValue() const { return m_maxValue; }
		void setMaxValue(const T val) { m_maxValue = val; }

		template<typename TN>
		void setType(TN v) {}

		template<>	void setType<char>(char v) { m_type = DataTypes::INT8; }
		template<>	void setType<short>(short v) { m_type = DataTypes::INT16; }
		template<>	void setType<int>(int v) { m_type = DataTypes::INT32; }
		template<>	void setType<unsigned char>(unsigned char v) { m_type = DataTypes::UINT8; }
		template<>	void setType<unsigned short>(unsigned short v) { m_type = DataTypes::UINT16; }
		template<>	void setType<unsigned int>(unsigned int v) { m_type = DataTypes::UINT32; }
		template<>	void setType<float>(float v) { m_type = DataTypes::FLOAT; }
		template<>	void setType<double>(double v) { m_type = DataTypes::DOUBLE; }
	};

	using FloatParameter = NumericParameter<float>;
	using DoubleParameter = NumericParameter<double>;
	using LongDoubleParameter = NumericParameter<long double>;
	using CharParameter = NumericParameter<unsigned char>;
	using UnsignedShortParameter = NumericParameter<unsigned short>;
	using UnsignedIntParameter = NumericParameter<unsigned int>;
	using UnsignedLongParameter = NumericParameter<unsigned long>;
	using SignedCharParameter = NumericParameter<signed char>;
	using ShortParameter = NumericParameter<signed short>;
	using IntParameter = NumericParameter<signed int>;
	using LongParameter = NumericParameter<signed long>;
}

#endif

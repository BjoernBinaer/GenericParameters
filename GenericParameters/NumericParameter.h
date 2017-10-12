#ifndef __NumericParameter_h__
#define __NumericParameter_h__

#include <functional>
#include <memory>
#include "Parameter.h"

namespace GenParam
{
	template<typename T>
	class NumericParameter : public Parameter<T>
	{
	protected:
		T m_minValue;
		T m_maxValue;

	public:
		using Ptr = std::shared_ptr<NumericParameter<T>>;

		NumericParameter(const std::string& name, const std::string& label,	ParameterBase::DataTypes type, T* valuePtr)
			: Parameter<T>(name, label, type, valuePtr)
		{
		}

		NumericParameter(const std::string& name, const std::string& label, ParameterBase::DataTypes type, GetFunc<T> getValue,	SetFunc<T> setValue)
			: Parameter<T>(name, label, type, getValue, setValue)
		{
		}

		virtual ~NumericParameter() {}
		
		T getMinValue() const { return m_minValue; }
		void setMinValue(const T val) { m_minValue = val; }
		
		T getMaxValue() const { return m_maxValue; }
		void setMaxValue(const T val) { m_maxValue = val; }
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

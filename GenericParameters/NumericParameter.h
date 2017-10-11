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
	public:
		NumericParameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, ParameterBase::DataTypes type, T* valuePtr, const bool readOnly)
			: Parameter<T>(name, label, group, description, type, valuePtr, readOnly)
		{
		}

		NumericParameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, ParameterBase::DataTypes type, GetFunc<T> getValue,	SetFunc<T> setValue, const bool readOnly)
			: Parameter<T>(name, label, group, description, type, getValue, setValue, readOnly)
		{
		}

		virtual ~NumericParameter() {}
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

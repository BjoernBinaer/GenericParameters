#ifndef __NumericParameter_h__
#define __NumericParameter_h__

#include <functional>
#include <memory>
#include "Parameter.h"

namespace GenParam
{
	template<typename T>
	class NumericParameter : public Parameter
	{
	protected: 
		GetFunc<T> m_getValue;
		SetFunc<T> m_setValue;

	public:
		NumericParameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, T* valuePtr, const bool readOnly)
			: Parameter(name, label, group, description, readOnly)
		{
			m_getValue = [valuePtr]() { return *valuePtr; };
			m_setValue = [valuePtr](T value) { *valuePtr = value; };
		}

		NumericParameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, GetFunc<T> getValue,	SetFunc<T> setValue, const bool readOnly)
			: Parameter(name, label, group, description, readOnly),
			m_getValue(getValue), m_setValue(setValue)
		{
		}

		void setValue(const T v) { m_setValue(v); }
		T getValue() const { return m_getValue(); }

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

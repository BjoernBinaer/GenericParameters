#ifndef __VectorParameter_h__
#define __VectorParameter_h__

#include <functional>
#include <memory>
#include "Parameter.h"
#include <iostream>

namespace GenParam
{
	template<typename T>
	class VectorParameter : public ParameterBase
	{
	protected:
		GetVecFunc<T> m_getVecValue;
		SetVecFunc<T> m_setVecValue;
		int m_dim;

	public:
		VectorParameter(const std::string& name, const std::string& label, const unsigned int dim, T* valuePtr)
			: ParameterBase(name, label, ParameterBase::INT32),
			m_dim(dim)
		{
			setType(valuePtr[0]);
			m_getVecValue = [valuePtr]() { return valuePtr; };
			m_setVecValue = [valuePtr, dim](T* value)
			{
				std::copy(value, value + dim, valuePtr);
			};
		}

		VectorParameter(const std::string& name, const std::string& label, const unsigned int dim, GetVecFunc<T> getValue,	SetVecFunc<T> setValue)
			: ParameterBase(name, label, ParameterBase::INT32),
			m_dim(dim),
			m_getVecValue(getValue),
			m_setVecValue(setValue)
		{
			setType(valuePtr[0]);
		}

		virtual ~VectorParameter() {}
		
		template<typename TN>
		void setType(TN v) {}

		unsigned int get_dim() const { return m_dim; }

		template<>	void setType<char>(char v) { m_type = DataTypes::INT8; }
		template<>	void setType<short>(short v) { m_type = DataTypes::INT16; }
		template<>	void setType<int>(int v) { m_type = DataTypes::INT32; }
		template<>	void setType<unsigned char>(unsigned char v) { m_type = DataTypes::UINT8; }
		template<>	void setType<unsigned short>(unsigned short v) { m_type = DataTypes::UINT16; }
		template<>	void setType<unsigned int>(unsigned int v) { m_type = DataTypes::UINT32; }
		template<>	void setType<float>(float v) { m_type = DataTypes::FLOAT; }
		template<>	void setType<double>(double v) { m_type = DataTypes::DOUBLE; }
	};

	using FloatVectorParameter = VectorParameter<float>;
	using DoubleVectorParameter = VectorParameter<double>;
	using LongDoubleVectorParameter = VectorParameter<long double>;
	using CharVectorParameter = VectorParameter<unsigned char>;
	using UnsignedShortVectorParameter = VectorParameter<unsigned short>;
	using UnsignedIntVectorParameter = VectorParameter<unsigned int>;
	using UnsignedLongVectorParameter = VectorParameter<unsigned long>;
	using SignedCharVectorParameter = VectorParameter<signed char>;
	using ShortVectorParameter = VectorParameter<signed short>;
	using IntVectorParameter = VectorParameter<signed int>;
	using LongVectorParameter = VectorParameter<signed long>;
}

#endif

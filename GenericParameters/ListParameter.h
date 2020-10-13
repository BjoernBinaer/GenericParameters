#ifndef GENERICPARAMETERS_LISTPARAMETER_H
#define GENERICPARAMETERS_LISTPARAMETER_H

#include <functional>
#include <memory>
#include <cstring>
#include "Parameter.h"
#include <iostream>

namespace GenParam
{
    /** Class of a vector parameter.
    */
    template<typename T>
    class ListParameter : public ParameterBase
    {
        using GetListFunc = std::function<T (unsigned int)>;
        using SetListFunc = std::function<void (unsigned int, T)>;

    protected:
        GetListFunc m_getListValue;
        SetListFunc m_setListValue;
        int m_dim;
        ssize_t m_offset;

    public:
        ListParameter(const std::string& name, const std::string& label, T* valuePtr, ssize_t offset)
                : ParameterBase(name, label, ParameterBase::INT32),
                  m_offset(offset)
        {
            setType(valuePtr[0]);
            m_getListValue = [valuePtr]() { return valuePtr; };
            m_setListValue = [valuePtr, dim](T* value)
            {
                memcpy(valuePtr, value, dim*sizeof(T));
            };
        }

        ListParameter(const std::string& name, const std::string& label, const unsigned int dim, ParameterBase::GetVecFunc<T> getValue, ParameterBase::SetVecFunc<T> setValue)
                : ParameterBase(name, label, ParameterBase::INT32),
                  m_dim(dim),
                  m_getListValue(getValue),
                  m_setListValue(setValue)
        {
            setType(getValue()[0]);
        }

        virtual ~ListParameter() {}

        void setValue(T *v)
        {
            if (m_setListValue != nullptr)
                m_setListValue(v);
        }
        T* getValue() const { return m_getListValue(); }

        virtual void setReadOnly(const bool val)
        {
            m_readOnly = val;
            if (m_setListValue == nullptr)
                m_readOnly = true;
        }

        template<typename TN>
        void setType(TN v) {}

        void setType(char v) { m_type = DataTypes::VEC_INT8; }
        void setType(short v) { m_type = DataTypes::VEC_INT16; }
        void setType(int v) { m_type = DataTypes::VEC_INT32; }
        void setType(unsigned char v) { m_type = DataTypes::VEC_UINT8; }
        void setType(unsigned short v) { m_type = DataTypes::VEC_UINT16; }
        void setType(unsigned int v) { m_type = DataTypes::VEC_UINT32; }
        void setType(float v) { m_type = DataTypes::VEC_FLOAT; }
        void setType(double v) { m_type = DataTypes::VEC_DOUBLE; }

        unsigned int getDim() const { return m_dim; }
    };

    using FloatListParameter = ListParameter<float>;
    using DoubleListParameter = ListParameter<double>;
    using LongDoubleListParameter = ListParameter<long double>;
    using CharListParameter = ListParameter<unsigned char>;
    using UnsignedShortListParameter = ListParameter<unsigned short>;
    using UnsignedIntListParameter = ListParameter<unsigned int>;
    using UnsignedLongListParameter = ListParameter<unsigned long>;
    using SignedCharListParameter = ListParameter<signed char>;
    using ShortListParameter = ListParameter<signed short>;
    using IntListParameter = ListParameter<signed int>;
    using LongListParameter = ListParameter<signed long>;
}
#endif //GENERICPARAMETERS_LISTPARAMETER_H

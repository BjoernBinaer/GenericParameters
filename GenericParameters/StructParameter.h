#ifndef GENERICPARAMETERS_STRUCTPARAMTER_H
#define GENERICPARAMETERS_STRUCTPARAMTER_H

#include <functional>
#include <memory>
#include <cstring>
#include "Parameter.h"
#include <iostream>

namespace GenParam
{
    /** Class of a vector parameter.
    */
    template<typename... Ts>
    class StructParameter : public ParameterBase
    {
    protected:
        std::tuple<Ts*...> m_values;
        std::array<std::string, sizeof...(Ts)> m_names;
        std::array<DataTypes, sizeof...(Ts)> m_types;
        int m_dim;

    public:
        StructParameter(const std::string& name, const std::string& label, std::array<std::string, sizeof...(Ts)> names, Ts * ... valuePtrs)
                : ParameterBase(name, label, ParameterBase::STRUCT)
        {
            m_values = std::make_tuple(valuePtrs...);
            m_names = names;
            m_types = {getType(*valuePtrs)...};
            m_dim = static_cast<int>(sizeof...(Ts));
        }

        virtual ~StructParameter() {}

        template<int index, typename T>
        void setValue(T v)
        {
            if (index >= m_dim){
                std::cout << "Invalid index";
                return;
            }
            if (getType(v) != m_types[index]){
                std::cout << "Invalid datatype";
                return;
            }
            *std::get<index>(m_values) = v;
        }

        template<int index>
        std::tuple_element<index, std::tuple<Ts*...>> getValue() const { return *std::get<index>(m_values); }

        // virtual void setReadOnly(const bool val)
        // {
        //     m_readOnly = val;
        //     if (m_setVecValue == nullptr)
        //         m_readOnly = true;
        // }

        template<typename TN>
        DataTypes getType(TN v) { return DataTypes::NPARAMS; }

        DataTypes getType(char v) { return DataTypes::INT8; }
        DataTypes getType(short v) { return DataTypes::INT16; }
        DataTypes getType(int v) { return DataTypes::INT32; }
        DataTypes getType(unsigned char v) { return DataTypes::UINT8; }
        DataTypes getType(unsigned short v) { return DataTypes::UINT16; }
        DataTypes getType(unsigned int v) { return DataTypes::UINT32; }
        DataTypes getType(float v) { return DataTypes::FLOAT; }
        DataTypes getType(double v) { return DataTypes::DOUBLE; }

        unsigned int getDim() const { return m_dim; }
    };

}
#endif //GENERICPARAMETERS_STRUCTPARAMTER_H

#ifndef GENERICPARAMETERS_STRUCTLISTPARAMETER_H
#define GENERICPARAMETERS_STRUCTLISTPARAMETER_H

#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <cstring>
#include "Parameter.h"
#include "NumericParameter.h"
#include "EnumParameter.h"
#include "VectorParameter.h"
#include "StructParameter.h"
#include <iostream>
#include <assert.h>

namespace GenParam {
    /** Class of a list of struct parameters.
     *  Lists can store multiple GenParam instances of the same struct parameter template.
     *  They do not store the data, but store a void pointer to the beginning of the data in m_basePtr.
     *
    */
    class StructListParameter : public ParameterBase {
    public:
        using GetListFunc = std::function<void*(unsigned int)>;  // Get a single parameter from the list
        using SetListFunc = std::function<void(unsigned int, void*)>;  // Set a single parameter from the list
        using ResizeFunc = std::function<void(
                unsigned int)>;  // Resize the list, only needed when the generic parameters are initializing objects

    protected:
        std::vector<std::vector<ParameterBase::Ptr>> m_parameters;
        /*std::vector<ParameterBase::DataTypes> m_templateStruct;*/     // Template for a list element (Only needed if dynamic resizing becomes desirable)
        unsigned int m_numParametersPerStruct;                          // Number of parameters inside the struct
        unsigned int m_numListElements;                                 // Number of list elements
        unsigned int m_idx;                                             // Index of the currently selected struct

    public:
        StructListParameter(const std::string &name, const std::string &label, const unsigned int numElems)
                : ParameterBase(name, label, ParameterBase::STRUCT_LIST) {
            m_parameters.resize(numElems);
            m_numListElements = numElems;
            m_idx = 0;
        }

        virtual ~StructListParameter() {
            for (auto& param : m_parameters)
                param.clear();
            m_parameters.clear();
        }

        /**
         *  T* valuePtr should hide an array / vector-like datatype
         */
        template<typename T> // T can be any numerical data type like float or double
        std::vector<int> createNumericParameters(const std::string &name, const std::string &label, T* valuePtr) {
            std::vector<int> parameterIndices;

            for (unsigned int i = 0; i < m_numListElements; i++)
            {
                ParameterBase::GetFunc<T> getFuncIndex = [&, valuePtr](){ return *(T*)((char*)valuePtr + sizeof(T) * m_idx);};
                ParameterBase::SetFunc<T> setFuncIndex = [&, valuePtr](T value){ *(T*)((char*)valuePtr + sizeof(T) * m_idx) = value;};

                m_parameters[i].push_back(std::unique_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, std::move(getFuncIndex), std::move(setFuncIndex))));
                parameterIndices.push_back(static_cast<int>(m_parameters[i].size() - 1));
            }

            return parameterIndices;
        }

        std::vector<int> createBoolParameters(const std::string &name, const std::string &label, bool* valuePtr) {
            std::vector<int> parameterIndices;

            for (unsigned int i = 0; i < m_numListElements; i++)
            {
                Parameter<bool>::GetFunc<bool> getFuncIndex = [&, valuePtr](){ return *(bool*)((char*)valuePtr + sizeof(bool) * m_idx);};
                Parameter<bool>::SetFunc<bool> setFuncIndex = [&, valuePtr](bool value){ *(bool*)((char*)valuePtr + sizeof(bool) * m_idx) = value;};
                m_parameters[i].push_back(std::unique_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, std::move(getFuncIndex), std::move(setFuncIndex))));
                parameterIndices.push_back(static_cast<int>(m_parameters[i].size() - 1));
            }

            return parameterIndices;
        }

        std::vector<int> createEnumParameters(const std::string &name, const std::string &label, int *valuePtr) {
            std::vector<int> parameterIndices;

            for (int i = 0; i < m_numListElements; i++)
            {
                ParameterBase::GetFunc<int> getFuncIndex = [&, valuePtr](){ return *(int*)((char*)valuePtr + sizeof(int) * m_idx);};
                ParameterBase::SetFunc<int> setFuncIndex = [&, valuePtr](int value){ *(int*)((char*)valuePtr + sizeof(int) * m_idx) = value;};
                m_parameters[i].push_back(std::unique_ptr<EnumParameter>(new EnumParameter(name, label, std::move(getFuncIndex), std::move(setFuncIndex))));
                parameterIndices.push_back(static_cast<int>(m_parameters[i].size() - 1));
            }

            return parameterIndices;
        }

        std::vector<int> createStringParameters(const std::string &name, const std::string &label, std::string *valuePtr) {
            std::vector<int> parameterIndices;

            for (int i = 0; i < m_numListElements; i++)
            {
                Parameter<std::string>::GetFunc<std::string> getFuncIndex = [&, valuePtr](){ return *(std::string*)((char*)valuePtr + sizeof(std::string) * m_idx);};
                Parameter<std::string>::SetFunc<std::string> setFuncIndex = [&, valuePtr](std::string value){ *(std::string*)((char*)valuePtr + sizeof(std::string) * m_idx) = std::move(value);};
                m_parameters[i].push_back(std::unique_ptr<Parameter<std::string>>(new Parameter<std::string>(name, label, ParameterBase::STRING, std::move(getFuncIndex), std::move(setFuncIndex))));
                parameterIndices.push_back(static_cast<int>(m_parameters[i].size() - 1));
            }
            
            return parameterIndices;
        }

        template<typename T>
        std::vector<int> createVectorParameters(const std::string &name, const std::string &label, const unsigned int dim, T *valuePtr) {
            std::vector<int> parameterIndices;

            for (int i = 0; i < m_numListElements; i++)
            {
                ParameterBase::GetVecFunc<T> getFuncIndex = [&, valuePtr]()->T*{ return (T*)((char*)valuePtr + dim * sizeof(T) * m_idx);};
                ParameterBase::SetVecFunc<T> setFuncIndex = [&, valuePtr, dim](T* value){
                    auto curPtr = (T*)((char*)valuePtr + dim * sizeof(T) * m_idx);
                    memcpy(curPtr, value, dim*sizeof(T));
                };
                m_parameters[i].push_back(
                        std::unique_ptr<VectorParameter<T>>(new VectorParameter<T>(name, label, dim, std::move(getFuncIndex), std::move(setFuncIndex))));
                parameterIndices.push_back(static_cast<int>(m_parameters[i].size() - 1));
            }

            return parameterIndices;
        }

        /** Get the parameter value by its id and list index. */
        template<typename T>
        T getValue(const unsigned int listIndex, const unsigned int parameterId) {
            if (listIndex >= m_numListElements){
                std::cout << "GenParam::StructListParameter: Access at invalid index";
                return T();
            }
            m_idx = listIndex;
            Parameter<T> *param = static_cast<Parameter<T> *>(m_parameters[listIndex][parameterId].get());
            return param->getValue();
        }

        /** Set the parameter value by its id. */
        template<typename T>
        void setValue(const unsigned int listIndex, const unsigned int parameterId, const T& v) {
            if (listIndex >= m_numListElements){
                std::cout << "GenParam::StructListParameter: Access at invalid index";
            }
            m_idx = listIndex;
            ParameterBase *paramBase = m_parameters[listIndex][parameterId].get();
            if (paramBase->checkType(v))
                static_cast<Parameter<T> *>(paramBase)->setValue(v);
            else
                std::cerr << "GenParam::StructListParameter: Type mismatch in setValue!" << std::endl;
        }

        /** Get the parameter value by its id. */
        template<typename T>
        T *getVecValue(const unsigned int listIndex, const unsigned int parameterId) {
            if (listIndex >= m_numListElements){
                std::cout << "GenParam::StructListParameter: Access at invalid index";
                return nullptr;
            }
            m_idx = listIndex;
            VectorParameter<T> *param = static_cast<VectorParameter<T> *>(m_parameters[listIndex][parameterId].get());
            return param->getValue();
        }

        /** Set the parameter value by its id. */
        template<typename T>
        void setVecValue(const unsigned int listIndex, const unsigned int parameterId, T *v) {
            if (listIndex >= m_numListElements){
                std::cout << "GenParam::StructListParameter: Access at invalid index";
                return T();
            }
            m_idx = listIndex;
            ParameterBase *paramBase = m_parameters[listIndex][parameterId].get();
            if (paramBase->checkType(v))
                static_cast<VectorParameter<T> *>(paramBase)->setValue(v);
            else
                std::cerr << "GenParam::StructListParameter: Type mismatch in setValue!" << std::endl;
        }

        /*void setVisible(const unsigned int parameterId, const bool v) { m_parameters[parameterId]->setVisible(v); }

        bool getVisible(const unsigned int parameterId) { return m_parameters[parameterId]->getVisible(); }

        void setReadOnly(const unsigned int parameterId, const bool v) { m_parameters[parameterId]->setReadOnly(v); }

        bool getReadOnly(const unsigned int parameterId) { return m_parameters[parameterId]->getReadOnly(); }

        void setName(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setName(v); }

        std::string getName(const unsigned int parameterId) { return m_parameters[parameterId]->getName(); }

        void setLabel(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setLabel(v); }

        std::string getLabel(const unsigned int parameterId) { return m_parameters[parameterId]->getLabel(); }

        void setGroup(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setGroup(v); }

        std::string getGroup(const unsigned int parameterId) { return m_parameters[parameterId]->getGroup(); }

        void setDescription(const unsigned int parameterId,
                            const std::string &v) { m_parameters[parameterId]->setDescription(v); }

        std::string
        getDescription(const unsigned int parameterId) { return m_parameters[parameterId]->getDescription(); }

        void setHotKey(const unsigned int parameterId, const std::string &v) {
            m_parameters[parameterId]->setHotKey(v);
        }

        std::string getHotKey(const unsigned int parameterId) { return m_parameters[parameterId]->getHotKey(); }

        GenParam::ParameterBase::DataTypes
        getType(const unsigned int parameterId) const { return m_parameters[parameterId]->getType(); }*/

    };
}

#endif //GENERICPARAMETERS_STRUCTLISTPARAMETER_H

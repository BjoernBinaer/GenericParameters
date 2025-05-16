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
        template<typename T>
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

        template<typename T>
        std::vector<int> createNumericParameters(const std::string &name, const std::string &label, std::vector<T> *valuePtr) {
            std::vector<int> parameterIndices;

            for (unsigned int i = 0; i < m_numListElements; i++)
            {
                ParameterBase::GetFunc<T> getFuncIndex = [&, valuePtr](){ return *(T*)((char*)valuePtr + sizeof(T) * m_idx);};
                ParameterBase::SetFunc<T> setFuncIndex = [&, valuePtr](T value){ *(T*)((char*)valuePtr + sizeof(T) * m_idx) = value;};

                m_parameters[i].push_back(std::unique_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, std::move(getFuncIndex), std::move(setFuncIndex))));
                parameterIndices.push_back(m_parameters[i].size() - 1);
            }

            return parameterIndices;
        }

        template<typename T, typename U>
        int createNumericParameter(const std::string &name, const std::string &label, void* valuePtr, std::function<T(U*)> unboundGetFunc, std::function<void(U*, T)> unboundSetFunc = {}) {
            assert(sizeof(U) == m_offset);
            ParameterBase::GetFunc<T> getFunc = [&, valuePtr, unboundGetFunc] () { return unboundGetFunc(reinterpret_cast<U*>(static_cast<char*>(valuePtr) + m_idx * m_offset)); };
            ParameterBase::SetFunc<T> setFunc = [&, valuePtr, unboundSetFunc] (bool v) { unboundSetFunc(reinterpret_cast<U*>(static_cast<char*>(valuePtr) + m_idx * m_offset), v); };
            m_parameters.push_back(
                    std::unique_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, std::move(getFunc), std::move(setFunc))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        int createBoolParameter(const std::string &name, const std::string &label, bool *valuePtr) {
            Parameter<bool>::GetFunc<bool> getFuncIndex = [&, valuePtr](){ return *(bool*)((char*)valuePtr + m_offset * m_idx);};
            Parameter<bool>::SetFunc<bool> setFuncIndex = [&, valuePtr](bool value){ *(bool*)((char*)valuePtr + m_offset * m_idx) = value;};
            m_parameters.push_back(
                    std::unique_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        template <typename T>
        int createBoolParameter(const std::string &name, const std::string &label, void* valuePtr, std::function<bool(T*)> unboundGetFunc, std::function<void(T*, bool)> unboundSetFunc = {}) {
            assert(sizeof(T) == m_offset);
            ParameterBase::GetFunc<bool> getFunc = [&, valuePtr, unboundGetFunc] () { return unboundGetFunc(reinterpret_cast<T*>(static_cast<char*>(valuePtr) + m_idx * m_offset)); };
            ParameterBase::SetFunc<bool> setFunc = [&, valuePtr, unboundSetFunc] (bool v) { unboundSetFunc(reinterpret_cast<T*>(static_cast<char*>(valuePtr) + m_idx * m_offset), v); };
            m_parameters.push_back(
                    std::unique_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, std::move(getFunc), std::move(setFunc))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        int createEnumParameter(const std::string &name, const std::string &label, int *valuePtr) {
            ParameterBase::GetFunc<int> getFuncIndex = [&, valuePtr](){ return *(int*)((char*)valuePtr + m_offset * m_idx);};
            ParameterBase::SetFunc<int> setFuncIndex = [&, valuePtr](int value){ *(int*)((char*)valuePtr + m_offset * m_idx) = value;};
            m_parameters.push_back(std::unique_ptr<EnumParameter>(new EnumParameter(name, label, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        template <typename T>
        int createEnumParameter(const std::string &name, const std::string &label, void* valuePtr, std::function<int(T*)> unboundGetFunc, std::function<void(T*, int)> unboundSetFunc = {}) {
            assert(sizeof(T) == m_offset);
            ParameterBase::GetFunc<int> getFunc = [&, valuePtr, unboundGetFunc] () { return unboundGetFunc(reinterpret_cast<T*>(static_cast<char*>(valuePtr) + m_idx * m_offset)); };
            ParameterBase::SetFunc<int> setFunc = [&, valuePtr, unboundSetFunc] (int v) { unboundSetFunc(reinterpret_cast<T*>(static_cast<char*>(valuePtr) + m_idx * m_offset), v); };
            m_parameters.push_back(std::unique_ptr<EnumParameter>(new EnumParameter(name, label, std::move(getFunc), std::move(setFunc))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        int createStringParameter(const std::string &name, const std::string &label, std::string *valuePtr) {
            Parameter<std::string>::GetFunc<std::string> getFuncIndex = [&, valuePtr](){ return *(std::string*)((char*)valuePtr + m_offset * m_idx);};
            Parameter<std::string>::SetFunc<std::string> setFuncIndex = [&, valuePtr](std::string value){ *(std::string*)((char*)valuePtr + m_offset * m_idx) = std::move(value);};
            m_parameters.push_back(std::unique_ptr<Parameter<std::string>>(
                    new Parameter<std::string>(name, label, ParameterBase::STRING, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        template <typename T>
        int createStringParameter(const std::string &name, const std::string &label, void* valuePtr, std::function<std::string(T*)> unboundGetFunc, std::function<void(T*, std::string)> unboundSetFunc = {}) {
            assert(sizeof(T) == m_offset);
            ParameterBase::GetFunc<std::string> getFunc = [&, valuePtr, unboundGetFunc] () { return unboundGetFunc(reinterpret_cast<T*>(static_cast<char*>(valuePtr) + m_idx * m_offset)); };
            ParameterBase::SetFunc<std::string> setFunc = [&, valuePtr, unboundSetFunc] (std::string v) { unboundSetFunc(reinterpret_cast<T*>(static_cast<char*>(valuePtr) + m_idx * m_offset), v); };
            m_parameters.push_back(std::unique_ptr<Parameter<std::string>>(
                    new Parameter<std::string>(name, label, ParameterBase::STRING, std::move(getFunc), std::move(setFunc))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        template<typename T>
        int
        createVectorParameter(const std::string &name, const std::string &label, const unsigned int dim, T *valuePtr) {
            ParameterBase::GetVecFunc<T> getFuncIndex = [&, valuePtr]()->T*{ return (T*)((char*)valuePtr + m_offset * m_idx);};
            ParameterBase::SetVecFunc<T> setFuncIndex = [&, valuePtr, dim](T* value){
                auto curPtr = (T*)((char*)valuePtr + m_offset * m_idx);
                memcpy(curPtr, value, dim*sizeof(T));
            };
            m_parameters.push_back(
                    std::unique_ptr<VectorParameter<T>>(new VectorParameter<T>(name, label, dim, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        template<typename T, typename U>
        int
        createVectorParameter(const std::string &name, const std::string &label, const unsigned int dim, void* valuePtr, std::function<T*(U*)> unboundGetFunc, std::function<void(U*, T*)> unboundSetFunc = {}) {
            assert(sizeof(U) == m_offset);
            ParameterBase::GetVecFunc<T> getFuncIndex = [&, valuePtr, unboundGetFunc](){ return unboundGetFunc(reinterpret_cast<U*>(static_cast<char*>(valuePtr) + m_idx * m_offset)); };
            ParameterBase::SetVecFunc<T> setFuncIndex = [&, valuePtr, unboundSetFunc](T* value){ unboundSetFunc(reinterpret_cast<U*>(static_cast<char*>(valuePtr) + m_idx * m_offset), value); };
            m_parameters.push_back(
                    std::unique_ptr<VectorParameter<T>>(new VectorParameter<T>(name, label, dim, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        /** Get the parameter value by its id and list index. */
        template<typename T>
        T getValue(const unsigned int i, const unsigned int parameterId) {
            if (i >= m_length){
                std::cout << "Access at invalid index";
                return T();
            }
            m_idx = i;
            Parameter<T> *param = static_cast<Parameter<T> *>(getParameter(parameterId));
            return param->getValue();
        }

        /** Set the parameter value by its id. */
        template<typename T>
        void setValue(const unsigned int i, const unsigned int parameterId, const T v) {
            if (i >= m_length){
                std::cout << "Access at invalid index";
            }
            m_idx = i;
            ParameterBase *paramBase = getParameter(parameterId);
            if (paramBase->checkType(v))
                static_cast<Parameter<T> *>(paramBase)->setValue(v);
            else
                std::cerr << "Type mismatch in setValue!" << std::endl;
        }

        /** Get the parameter value by its id. */
        template<typename T>
        T *getVecValue(const unsigned int i, const unsigned int parameterId) {
            if (i >= m_length){
                std::cout << "Access at invalid index";
                return nullptr;
            }
            m_idx = i;
            VectorParameter<T> *param = static_cast<VectorParameter<T> *>(getParameter(parameterId));
            return param->getValue();
        }

        /** Set the parameter value by its id. */
        template<typename T>
        void setVecValue(const unsigned int i, const unsigned int parameterId, T *v) {
            if (i >= m_length){
                std::cout << "Access at invalid index";
                return T();
            }
            m_idx = i;
            ParameterBase *paramBase = getParameter(parameterId);
            if (paramBase->checkType(v))
                static_cast<VectorParameter<T> *>(paramBase)->setValue(v);
            else
                std::cerr << "Type mismatch in setValue!" << std::endl;
        }

        void setVisible(const unsigned int parameterId, const bool v) { m_parameters[parameterId]->setVisible(v); }

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
        getType(const unsigned int parameterId) const { return m_parameters[parameterId]->getType(); }

    };
}

#endif //GENERICPARAMETERS_STRUCTLISTPARAMETER_H

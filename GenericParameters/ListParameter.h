#ifndef GENERICPARAMETERS_LISTPARAMETER_H
#define GENERICPARAMETERS_LISTPARAMETER_H

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

namespace GenParam {
    /** Class of a vector parameter.
    */
    class ListParameter : public ParameterBase {
        using GetListFunc = std::function<void*(unsigned int)>;  // Get a single parameter from the list
        using SetListFunc = std::function<void(unsigned int, void*)>;  // Set a single parameter from the list
        using ResizeFunc = std::function<void(
                unsigned int)>;  // Resize the list, only needed when the generic parameters are initializing objects

    protected:
        std::vector<ParameterBase::Ptr> m_parameters;
        ResizeFunc m_resize;
        ssize_t m_offset;
        unsigned int m_length;
        unsigned int m_maxLength;
        unsigned int m_idx;

    public:
        template<typename T>
        ListParameter(const std::string &name, const std::string &label, std::vector<T> *data)
                : ParameterBase(name, label, ParameterBase::STRUCT), m_parameters(), m_length(data->size()), m_maxLength(data->capacity()), m_offset(sizeof(T)), m_resize([data](const unsigned int i){ data->resize(i); }){}

        virtual ~ListParameter() { m_parameters.clear(); }

        unsigned int numParameters() const { return static_cast<unsigned int>(m_parameters.size()); }

        ParameterBase *getParameter(const unsigned int index) { return m_parameters[index].get(); }

        ParameterBase *const getParameter(const unsigned int index) const { return m_parameters[index].get(); }

        void resize(unsigned int i){
            if (i >= m_maxLength){
                std::cout << "Requested resize which is greater than the maximum capacity. Use vector::reserve to allocate more memory for the vector.";
            }
            m_length = i;
            m_resize(i);
        }

        unsigned int size() const {
            return m_length;
        }

        unsigned int getIndex() const {
            return m_idx;
        }

        void setIndex(unsigned int i) {
            if (i < m_length){
                m_idx = i;
            }
        }

        template<typename T>
        int createNumericParameter(const std::string &name, const std::string &label, T *valuePtr) {
            ParameterBase::GetFunc<T> getFuncIndex = [&, valuePtr](){ return *(T*)((char*)valuePtr + m_offset * m_idx);};
            ParameterBase::SetFunc<T> setFuncIndex = [&, valuePtr](T value){ *(T*)((char*)valuePtr + m_offset * m_idx) = value;};
            m_parameters.push_back(
                    std::unique_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        int createBoolParameter(const std::string &name, const std::string &label, bool *valuePtr) {
            Parameter<bool>::GetFunc<bool> getFuncIndex = [&, valuePtr](){ return *(bool*)((char*)valuePtr + m_offset * m_idx);};
            Parameter<bool>::SetFunc<bool> setFuncIndex = [&, valuePtr](bool value){ *(bool*)((char*)valuePtr + m_offset * m_idx) = value;};
            m_parameters.push_back(
                    std::unique_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        int createEnumParameter(const std::string &name, const std::string &label, int *valuePtr) {
            ParameterBase::GetFunc<int> getFuncIndex = [&, valuePtr](){ return *(int*)((char*)valuePtr + m_offset * m_idx);};
            ParameterBase::SetFunc<int> setFuncIndex = [&, valuePtr](int value){ *(int*)((char*)valuePtr + m_offset * m_idx) = value;};
            m_parameters.push_back(std::unique_ptr<EnumParameter>(new EnumParameter(name, label, std::move(getFuncIndex), std::move(setFuncIndex))));
            return static_cast<int>(m_parameters.size() - 1);
        }

        int createStringParameter(const std::string &name, const std::string &label, std::string *valuePtr) {
            Parameter<std::string>::GetFunc<std::string> getFuncIndex = [&, valuePtr](){ return *(std::string*)((char*)valuePtr + m_offset * m_idx);};
            Parameter<std::string>::SetFunc<std::string> setFuncIndex = [&, valuePtr](std::string value){ *(std::string*)((char*)valuePtr + m_offset * m_idx) = std::move(value);};
            m_parameters.push_back(std::unique_ptr<Parameter<std::string>>(
                    new Parameter<std::string>(name, label, ParameterBase::STRING, std::move(getFuncIndex), std::move(setFuncIndex))));
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
                return T();
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

#endif //GENERICPARAMETERS_LISTPARAMETER_H

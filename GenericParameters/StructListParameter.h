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
    protected:
        std::vector<std::unique_ptr<StructParameter>> m_parameters;
        int m_idx;                                                          // Index of the currently selected struct

    public:
        StructListParameter(const std::string &name, const std::string &label, const unsigned int numElems)
                : ParameterBase(name, label, ParameterBase::STRUCT_LIST) {
            m_idx = 0;
            resize(numElems);
        }

        StructListParameter(const std::string& name, const std::string& label)
                : ParameterBase(name, label, ParameterBase::STRUCT_LIST) {
            m_idx = -1;
        }

        virtual ~StructListParameter() {
            m_parameters.clear();
        }

        void resize(const unsigned int numElems)
        {
            const unsigned int oldSize = m_parameters.size();
            m_parameters.resize(numElems);

            if (oldSize < m_parameters.size())
                for (unsigned int i = oldSize; i < m_parameters.size(); i++)
                    m_parameters[i] = std::unique_ptr<StructParameter>(new StructParameter(m_name + "_" + std::to_string(i), m_label));

            if (m_parameters.size() >= m_idx)
                m_idx = m_parameters.size() - 1;
        }

        void setVisible(const bool v) {
            m_visible = v;
            for (auto& paramStruct: m_parameters)
                for (int i = 0; i < paramStruct->numParameters(); i++)
                    paramStruct->setVisible(i, v);
        }
        void setVisible(const unsigned int parameterId, const bool v) {
            m_parameters[m_idx]->setVisible(parameterId, v);
        }
        void setVisible(const unsigned int listIndex, const unsigned int parameterId, const bool v) {
            m_parameters[listIndex]->setVisible(parameterId, v);
        }
        bool getVisible(const unsigned int parameterId) { return m_parameters[m_idx]->getVisible(parameterId); }
        bool getVisible(const unsigned int listIndex, const unsigned int parameterId) { return m_parameters[listIndex]->getVisible(parameterId); }

        void setReadOnly(const bool v) {
            m_readOnly = v;
            for (auto& paramStruct: m_parameters)
                for (int i = 0; i < paramStruct->numParameters(); i++)
                    paramStruct->setReadOnly(i, v);
        }
        void setReadOnly(const unsigned int parameterId, const bool v) {
            m_parameters[m_idx]->setReadOnly(parameterId, v);
        }
        void setReadOnly(const unsigned int listIndex, const unsigned int parameterId, const bool v) {
            m_parameters[listIndex]->setReadOnly(parameterId, v);
        }
        bool getReadOnly(const unsigned int parameterId) { return m_parameters[m_idx]->getReadOnly(parameterId); }
        bool getReadOnly(const unsigned int listIndex, const unsigned int parameterId) { return m_parameters[listIndex]->getReadOnly(parameterId); }

        void setName(const unsigned int parameterId, const std::string &v) { m_parameters[m_idx]->setName(parameterId, v); }
        void setName(const unsigned int listIndex, const unsigned int parameterId, const std::string& v) { m_parameters[listIndex]->setName(parameterId, v); }
        std::string getName(const unsigned int parameterId) { return m_parameters[m_idx]->getName(parameterId); }
        std::string getName(const unsigned int listIndex, const unsigned int parameterId) { return m_parameters[listIndex]->getName(parameterId); }

        void setLabel(const unsigned int parameterId, const std::string &v) { m_parameters[m_idx]->setLabel(parameterId, v); }
        void setLabel(const unsigned int listIndex, const unsigned int parameterId, const std::string& v) { m_parameters[listIndex]->setLabel(parameterId, v); }
        std::string getLabel(const unsigned int parameterId) { return m_parameters[m_idx]->getLabel(parameterId); }
        std::string getLabel(const unsigned int listIndex, const unsigned int parameterId) { return m_parameters[listIndex]->getLabel(parameterId); }

        void setGroup(const unsigned int parameterId, const std::string &v) { m_parameters[m_idx]->setGroup(parameterId, v); }
        void setGroup(const unsigned int listIndex, const unsigned int parameterId, const std::string& v) { m_parameters[listIndex]->setGroup(parameterId, v); }
        std::string getGroup(const unsigned int parameterId) { return m_parameters[m_idx]->getGroup(parameterId); }
        std::string getGroup(const unsigned int listIndex, const unsigned int parameterId) { return m_parameters[m_idx]->getGroup(parameterId); }

        void setDescription(const unsigned int parameterId, const std::string &v) { m_parameters[m_idx]->setDescription(parameterId, v); }
        void setDescription(const unsigned int listIndex, const unsigned int parameterId, const std::string& v) { m_parameters[listIndex]->setDescription(parameterId, v); }
        std::string getDescription(const unsigned int parameterId, const std::string& v) { return m_parameters[m_idx]->getDescription(parameterId); }
        std::string getDescription(const unsigned int listIndex, const unsigned int parameterId, const std::string& v) { return m_parameters[listIndex]->getDescription(parameterId); }

        void setHotKey(const unsigned int parameterId, const std::string &v) { m_parameters[m_idx]->setHotKey(parameterId, v); }
        void setHotKey(const unsigned int listIndex, const unsigned int parameterId, const std::string& v) { m_parameters[listIndex]->setHotKey(parameterId, v); }
        std::string getHotKey(const unsigned int parameterId, const std::string& v) { return m_parameters[m_idx]->getHotKey(parameterId); }
        std::string getHotKey(const unsigned int listIndex, const unsigned int parameterId, const std::string& v) { return m_parameters[listIndex]->getHotKey(parameterId); }

        GenParam::ParameterBase::DataTypes getType(const unsigned int parameterId) const { return m_parameters[m_idx]->getType(parameterId); }
        GenParam::ParameterBase::DataTypes getType(const unsigned int listIndex, const unsigned int parameterId) const { return m_parameters[listIndex]->getType(parameterId); }
    };
}

#endif //GENERICPARAMETERS_STRUCTLISTPARAMETER_H

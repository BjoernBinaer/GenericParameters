#ifndef __ParameterObject_h__
#define __ParameterObject_h__

#include <vector>
#include <memory>
#include "NumericParameter.h"
#include "EnumParameter.h"

namespace GenParam
{
	class ParameterObject
	{
	protected:
		std::vector<std::shared_ptr<ParameterBase>> m_parameters;
	
	public:
		ParameterObject() : m_parameters() {}
		virtual ~ParameterObject() { m_parameters.clear();  }

		virtual void initParameters() {}
		unsigned int numParameters() const { return static_cast<unsigned int>(m_parameters.size()); }
		ParameterBase::Ptr getParameter(const unsigned int index) { return m_parameters[index]; }

		template<typename T>
		int createParameter(const std::string &name, const std::string &label, ParameterBase::DataTypes type,  T* valuePtr)
		{
			// check for numeric parameters
			if ((type >= ParameterBase::FLOAT) && (type <= ParameterBase::UINT32))
				m_parameters.push_back(std::shared_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, type, valuePtr)));
			else
				m_parameters.push_back(std::shared_ptr<Parameter<T>>(new Parameter<T>(name, label, type, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		int createParameter(const std::string &name, const std::string &label, ParameterBase::DataTypes type, Parameter::GetFunc<T> getValue, Parameter::SetFunc<T> setValue)
		{
			// check for numeric parameters
			if ((type >= ParameterBase::FLOAT) && (type <= ParameterBase::UINT32))
				m_parameters.push_back(std::shared_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, type, getValue, setValue)));
			else
				m_parameters.push_back(std::shared_ptr<Parameter<T>>(new Parameter<T>(name, label, type, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<>
		int createParameter<int>(const std::string &name, const std::string &label, ParameterBase::DataTypes type, int* valuePtr)
		{
			if (type == ParameterBase::ENUM)
				m_parameters.push_back(std::shared_ptr<EnumParameter>(new EnumParameter(name, label, type, valuePtr)));
			else
				m_parameters.push_back(std::shared_ptr<NumericParameter<int>>(new NumericParameter<int>(name, label, type, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<>
		int createParameter<int>(const std::string &name, const std::string &label, ParameterBase::DataTypes type, ParameterBase::GetFunc<int> getValue, ParameterBase::SetFunc<int> setValue)
		{
			if (type == ParameterBase::ENUM)
				m_parameters.push_back(std::shared_ptr<EnumParameter>(new EnumParameter(name, label, type, getValue, setValue)));
			else
				m_parameters.push_back(std::shared_ptr<NumericParameter<int>>(new NumericParameter<int>(name, label, type, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		T getValue(const unsigned int parameterId) const
		{
			auto param = std::static_pointer_cast<Parameter<T>>(m_parameters[parameterId]);
			return param->getValue();
		}

		template<typename T>
		void setValue(const unsigned int parameterId, const T v) 
		{
			auto param = std::static_pointer_cast<Parameter<T>>(m_parameters[parameterId]);
			param->setValue(v);
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

		void setDescription(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setDescription(v); }
		std::string getDescription(const unsigned int parameterId) { return m_parameters[parameterId]->getDescription(); }

		GenParam::ParameterBase::DataTypes getType(const unsigned int parameterId) const { return m_parameters[parameterId]->getType(); }
	};

}
#endif

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
		virtual ~ParameterObject() { m_parameters.clear(); }

		virtual void initParameters() {}
		unsigned int numParameters() const { return static_cast<unsigned int>(m_parameters.size()); }
		ParameterBase::Ptr getParameter(const unsigned int index) { return m_parameters[index]; }

		template<typename T>
		int createNumericParameter(const std::string &name, const std::string &label, T* valuePtr)
		{
			m_parameters.push_back(std::shared_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		int createNumericParameter(const std::string &name, const std::string &label, Parameter::GetFunc<T> getValue, Parameter::SetFunc<T> setValue = {})
		{
			m_parameters.push_back(std::shared_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createBoolParameter(const std::string &name, const std::string &label, bool* valuePtr)
		{
			m_parameters.push_back(std::shared_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createBoolParameter(const std::string &name, const std::string &label, Parameter::GetFunc<bool> getValue, Parameter::SetFunc<bool> setValue = {})
		{
			m_parameters.push_back(std::shared_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createEnumParameter(const std::string &name, const std::string &label, int* valuePtr)
		{
			m_parameters.push_back(std::shared_ptr<EnumParameter>(new EnumParameter(name, label, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createEnumParameter(const std::string &name, const std::string &label, ParameterBase::GetFunc<int> getValue, ParameterBase::SetFunc<int> setValue = {})
		{
			m_parameters.push_back(std::shared_ptr<EnumParameter>(new EnumParameter(name, label, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createStringParameter(const std::string &name, const std::string &label, std::string* valuePtr)
		{
			m_parameters.push_back(std::shared_ptr<Parameter<std::string>>(new Parameter<std::string>(name, label, ParameterBase::STRING, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createStringParameter(const std::string &name, const std::string &label, Parameter::GetFunc<std::string> getValue, Parameter::SetFunc<std::string> setValue = {})
		{
			m_parameters.push_back(std::shared_ptr<Parameter<std::string>>(new Parameter<std::string>(name, label, ParameterBase::STRING, getValue, setValue)));
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

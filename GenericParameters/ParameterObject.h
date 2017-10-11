#ifndef __ParameterObject_h__
#define __ParameterObject_h__

#include <vector>
#include <memory>
#include "NumericParameter.h"

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
		int createParameter(const std::string &name, const std::string &label, const std::string &group, const std::string &description, ParameterBase::DataTypes type,  T* valuePtr, const bool readOnly = false)
		{
			std::shared_ptr<Parameter<T>> param(new Parameter<T>(name, label, group, description, type, valuePtr, readOnly));
			m_parameters.push_back(param);
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		int createParameter(const std::string &name, const std::string &label, const std::string &group, const std::string &description, ParameterBase::DataTypes type, Parameter::GetFunc<T> getValue, Parameter::SetFunc<T> setValue, const bool readOnly = false)
		{
			std::shared_ptr<DoubleParameter> param(new DoubleParameter(name, label, group, description, type, getValue, setValue, readOnly));
			m_parameters.push_back(param);
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		T getParameter(unsigned int parameterId) const
		{
			auto param = std::static_pointer_cast<Parameter<T>>(m_parameters[parameterId]);
			return param->getValue();
		}

		template<typename T>
		void setParameter(unsigned int parameterId, const T v) 
		{
			auto param = std::static_pointer_cast<Parameter<T>>(m_parameters[parameterId]);
			param->setValue(v);
		}
	};

}
#endif

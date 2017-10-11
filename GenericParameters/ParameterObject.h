#ifndef __ParameterObject_h__
#define __ParameterObject_h__

#include <vector>
#include <memory>
#include "BoolParameter.h"
#include "NumericParameter.h"

namespace GenParam
{
	class ParameterObject
	{
	protected:
		std::vector<std::shared_ptr<Parameter>> m_parameters;
	
	public:
		ParameterObject() : m_parameters() {}
		virtual ~ParameterObject() { m_parameters.clear();  }

		virtual void initParameters() {}
		unsigned int numParameters() const { return static_cast<unsigned int>(m_parameters.size()); }
		Parameter::Ptr getParameter(const unsigned int index) { return m_parameters[index]; }

		int createBoolParameter(const std::string &name, const std::string &label, const std::string &group, const std::string &description, bool* valuePtr, const bool readOnly = false)
		{
			std::shared_ptr<BoolParameter> param(new BoolParameter(name, label, group, description, valuePtr, readOnly));
			m_parameters.push_back(param);
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createIntParameter(const std::string &name, const std::string &label, const std::string &group, const std::string &description, int* valuePtr, const bool readOnly = false)
		{
			std::shared_ptr<IntParameter> param(new IntParameter(name, label, group, description, valuePtr, readOnly));
			m_parameters.push_back(param);
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createDoubleParameter(const std::string &name, const std::string &label, const std::string &group, const std::string &description, double* valuePtr, const bool readOnly = false)
		{
			std::shared_ptr<DoubleParameter> param(new DoubleParameter(name, label, group, description, valuePtr, readOnly));
			m_parameters.push_back(param);
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createDoubleParameter(const std::string &name, const std::string &label, const std::string &group, const std::string &description, Parameter::GetFunc<double> getValue, Parameter::SetFunc<double> setValue, const bool readOnly = false)
		{
			std::shared_ptr<DoubleParameter> param(new DoubleParameter(name, label, group, description, getValue, setValue, readOnly));
			m_parameters.push_back(param);
			return static_cast<int>(m_parameters.size() - 1);
		}

		bool getBool(unsigned int parameterId) const
		{
			auto param = std::static_pointer_cast<BoolParameter>(m_parameters[parameterId]);
			return param->getValue();
		}

		int getInt(unsigned int parameterId) const
		{
			auto param = std::static_pointer_cast<IntParameter>(m_parameters[parameterId]);
			return param->getValue();
		}

		double getDouble(unsigned int parameterId) const
		{
			auto param = std::static_pointer_cast<DoubleParameter>(m_parameters[parameterId]);
			return param->getValue();
		}

		void setDouble(unsigned int parameterId, const double v) 
		{
			auto param = std::static_pointer_cast<DoubleParameter>(m_parameters[parameterId]);
			param->setValue(v);
		}
	};

}
#endif

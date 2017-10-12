#ifndef __EnumParameter_h__
#define __EnumParameter_h__

#include <functional>
#include <memory>
#include "Parameter.h"
#include <vector>

namespace GenParam
{
	class EnumParameter : public Parameter<int>
	{
	public: 
		using Ptr = std::shared_ptr<EnumParameter>;

		struct EnumValue
		{
			int id;
			std::string name;
		};

	protected:
		std::vector<EnumValue> m_enumValues;

	public:
		EnumParameter(const std::string& name, const std::string& label, ParameterBase::DataTypes type, int* valuePtr)
			: Parameter<int>(name, label, type, valuePtr)
		{
		}

		EnumParameter(const std::string& name, const std::string& label, ParameterBase::DataTypes type, GetFunc<int> getValue, SetFunc<int> setValue)
			: Parameter<int>(name, label, type, getValue, setValue)
		{
		}

		virtual ~EnumParameter() {}

		void addEnumValue(const std::string &name, int &id)
		{
			EnumValue val;
			val.name = name;
			id = static_cast<int>(m_enumValues.size());
			val.id = id;
			m_enumValues.push_back(val);
		}

		const std::vector<EnumValue>& getEnumValues() { return m_enumValues;  }
	};
}

#endif

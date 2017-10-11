#ifndef __BoolParameter_h__
#define __BoolParameter_h__

#include <functional>
#include <memory>
#include "Parameter.h"

namespace GenParam
{
	class BoolParameter : public Parameter
	{
	protected: 
		GetFunc<bool> m_getValue;
		SetFunc<bool> m_setValue;

	public:
		BoolParameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, bool* valuePtr, const bool readOnly) 
			: Parameter(name, label, group, description, readOnly)
		{
			m_getValue = [valuePtr]() { return *valuePtr; };
			m_setValue = [valuePtr](bool value) { *valuePtr = value;	};
		}

		BoolParameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, GetFunc<bool> getValue,	SetFunc<bool> setValue, const bool readOnly)
			: Parameter(name, label, group, description, readOnly),
			m_getValue(getValue), m_setValue(setValue)
		{
		}

		void setValue(const bool v) { m_setValue(v); }
		bool getValue() const {	return m_getValue(); }

		virtual ~BoolParameter() {}
	};
}

#endif

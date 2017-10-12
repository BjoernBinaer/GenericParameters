#ifndef __Parameter_h__
#define __Parameter_h__

#include <functional>
#include <memory>

namespace GenParam
{
	class ParameterBase
	{
	public:
		enum DataTypes
		{
			BOOL = 1,
			INT32, 
			DOUBLE, 
			ENUM
		};

		using Ptr = std::shared_ptr<ParameterBase>;
		template <typename T>
		using SetFunc = std::function<void(T)>;
		template <typename T>
		using GetFunc = std::function<T()>;
		template <typename T>
		using SetVecFunc = std::function<void(T*)>;
		template <typename T>
		using GetVecFunc = std::function<T* ()>;

		ParameterBase(const std::string& name, const std::string& label, const std::string& group, const std::string& description, const DataTypes type, const bool readOnly, const bool visible = true) :
			m_name(name), m_label(label), m_group(group), m_description(description), m_type(type), m_readOnly(readOnly), m_visible(visible)
		{}

		virtual ~ParameterBase() {}

		std::string getName() const { return m_name; }
		void setName(const std::string& name) { m_name = name; }

		std::string getGroup() const { return m_group; }
		void setGroup(const std::string& group) { m_group = group; }

		std::string getLabel() const { return m_label; }
		void setLabel(const std::string &val) { m_label = val; }

		std::string getDescription() const { return m_description; }
		void setDescription(const std::string &val) { m_description = val; }

		bool getReadOnly() const { return m_readOnly; }
		void setReadOnly(const bool val) { m_readOnly = val; }

		bool getVisible() const { return m_visible; }
		void setVisible(const bool val) { m_visible = val; }

		GenParam::ParameterBase::DataTypes getType() const { return m_type; }

	protected:
		std::string m_name;
		std::string m_label;
		std::string m_group;
		std::string m_description;
		DataTypes m_type;
		bool m_readOnly;
		bool m_visible; 
	};

	template<typename T>
	class Parameter : public ParameterBase
	{
	protected:
		GetFunc<T> m_getValue;
		SetFunc<T> m_setValue;

	public:
		Parameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, 
			ParameterBase::DataTypes type, T* valuePtr, 
			const bool readOnly, const bool visible)
			: ParameterBase(name, label, group, description, type, readOnly, visible)
		{
			m_getValue = [valuePtr]() { return *valuePtr; };
			m_setValue = [valuePtr](T value) { *valuePtr = value; };
		}

		Parameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, 
			ParameterBase::DataTypes type, GetFunc<T> getValue, SetFunc<T> setValue, 
			const bool readOnly, const bool visible)
			: ParameterBase(name, label, group, description, type, readOnly, visible),
			m_getValue(getValue), m_setValue(setValue)
		{
		}

		void setValue(const T v) { m_setValue(v); }
		T getValue() const { return m_getValue(); }

		virtual ~Parameter() {}
	};

	using BoolParameter = Parameter<bool>;
	using StringParameter = Parameter<std::string>;
}

#endif

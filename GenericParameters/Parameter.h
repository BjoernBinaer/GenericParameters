#ifndef __Parameter_h__
#define __Parameter_h__

#include <functional>
#include <memory>

namespace GenParam
{
	/** Base class of all generic parameter types. 
	*/
	class ParameterBase
	{
	public:
		enum DataTypes
		{
			BOOL = 1,
			FLOAT,
			DOUBLE, 
			INT8,
			INT16,
			INT32,
			UINT8,
			UINT16, 
			UINT32,
			VEC_FLOAT,
			VEC_DOUBLE,
			VEC_INT8,
			VEC_INT16,
			VEC_INT32,
			VEC_UINT8,
			VEC_UINT16,
			VEC_UINT32,
			ENUM, 
			STRING,
			LIST,
			STRUCT,
			NPARAMS
		};

		using Ptr = std::unique_ptr<ParameterBase>;
		template <typename T>
		using SetFunc = std::function<void(T)>;
		template <typename T>
		using GetFunc = std::function<T()>;
		template <typename T>
		using SetVecFunc = std::function<void(T*)>;
		template <typename T>
		using GetVecFunc = std::function<T* ()>;

		ParameterBase(const std::string& name, const std::string& label, const DataTypes type) :
			m_name(name), m_label(label), m_group(""), m_description(""), m_hotKey(""), m_type(type), m_readOnly(false), m_visible(true)
		{
		}

		virtual ~ParameterBase() {}
		
		std::string getName() const { return m_name; }
		void setName(const std::string& name) { m_name = name; }

		std::string getGroup() const { return m_group; }
		void setGroup(const std::string& group) { m_group = group; }

		std::string getLabel() const { return m_label; }
		void setLabel(const std::string &val) { m_label = val; }

		std::string getDescription() const { return m_description; }
		void setDescription(const std::string &val) { m_description = val; }

		std::string getHotKey() const { return m_hotKey; }
		void setHotKey(const std::string &val) { m_hotKey = val; }

		bool getReadOnly() const { return m_readOnly; }
		virtual void setReadOnly(const bool val) { m_readOnly = val; }

		bool getVisible() const { return m_visible; }
		void setVisible(const bool val) { m_visible = val; }

		GenParam::ParameterBase::DataTypes getType() const { return m_type; }

		/** Check if the type of the value matches the type of the generic parameter */
		template<typename T>
		bool checkType(T v) { return m_type == STRUCT; }

        template<typename T>
        bool checkType(std::vector<T> v) { return m_type == LIST; }

		bool checkType(char v) { return m_type == INT8; }
		bool checkType(short v) { return m_type == INT16; }
		bool checkType(int v) { return (m_type == INT32) || (m_type == ENUM); }
		bool checkType(unsigned char v) { return m_type == UINT8; }
		bool checkType(unsigned short v) { return m_type == UINT16; }
		bool checkType(unsigned int v) { return m_type == UINT32; }
		bool checkType(float v) { return m_type == FLOAT; }
		bool checkType(double v) { return m_type == DOUBLE; }
		bool checkType(char *v) { return m_type == VEC_INT8; }
		bool checkType(short *v) { return m_type == VEC_INT16; }
		bool checkType(int *v) { return (m_type == VEC_INT32); }
		bool checkType(unsigned char *v) { return m_type == VEC_UINT8; }
		bool checkType(unsigned short *v) { return m_type == VEC_UINT16; }
		bool checkType(unsigned int *v) { return m_type == VEC_UINT32; }
		bool checkType(float *v) { return m_type == VEC_FLOAT; }
		bool checkType(double *v) { return m_type == VEC_DOUBLE; }
		bool checkType(bool v) { return m_type == BOOL; }
		bool checkType(std::string v) { return m_type == STRING; }


	protected:
		std::string m_name;
		std::string m_label;
		std::string m_group;
		std::string m_description;
		std::string m_hotKey;
		DataTypes m_type;
		bool m_readOnly;
		bool m_visible; 
	};

	/** Class of a generic parameter.\n
	* There are two ways to construct a generic parameter. Either the user provides a pointer 
	* of a variable of the corresponding type or he provides a get and a set function. 
	* Changing the generic parameter will then also change the corresponding variable or 
	* class the corresponding set function.\n\n
	* An example how to generate generic parameters and how to use them can be found in 
	* the ParameterTest and the corresponding TestParameterObject.
	*/
	template<typename T>
	class Parameter : public ParameterBase
	{
	protected:
		GetFunc<T> m_getValue;
		SetFunc<T> m_setValue;

	public:
		/** Pointer-Constructor */
		Parameter(const std::string& name, const std::string& label, ParameterBase::DataTypes type, T* valuePtr)
			: ParameterBase(name, label, type)
		{
			m_getValue = [valuePtr]() { return *valuePtr; };
			m_setValue = [valuePtr](T value) { *valuePtr = value; };
		}

		/** Get/Set-Function constructor. Note that if the setValue function is the nullptr, then the parameter is marked as read-only. */
		Parameter(const std::string& name, const std::string& label, ParameterBase::DataTypes type, GetFunc<T> getValue, SetFunc<T> setValue)
			: ParameterBase(name, label, type),
			m_getValue(getValue), m_setValue(setValue)
		{
			if (m_setValue == nullptr)
				m_readOnly = true;
		}

		void setValue(const T v) 
		{
			if (m_setValue != nullptr) 
				m_setValue(v); 
		}
		T getValue() const { return m_getValue(); }

		virtual ~Parameter() {}

		virtual void setReadOnly(const bool val) 
		{
			m_readOnly = val; 
			if (m_setValue == nullptr)
				m_readOnly = true;
		}
	};

	using BoolParameter = Parameter<bool>;
	using StringParameter = Parameter<std::string>;
}

#endif

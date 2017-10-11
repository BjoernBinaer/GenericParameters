#ifndef __Parameter_h__
#define __Parameter_h__

#include <functional>
#include <memory>

namespace GenParam
{
	class Parameter
	{

	public:
		using Ptr = std::shared_ptr<Parameter>;
		template <typename T>
		using SetFunc = std::function<void(T)>;
		template <typename T>
		using GetFunc = std::function<T()>;
		template <typename T>
		using SetVecFunc = std::function<void(T*)>;
		template <typename T>
		using GetVecFunc = std::function<T* ()>;

		Parameter(const std::string& name, const std::string& label, const std::string& group, const std::string& description, const bool readOnly) :
			m_name(name), m_label(label), m_group(group), m_description(description), m_readOnly(readOnly)
		{}

		virtual ~Parameter() {}

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

	protected:
		std::string m_name;
		std::string m_label;
		std::string m_group;
		std::string m_description;
		bool m_readOnly;
	};
}

#endif

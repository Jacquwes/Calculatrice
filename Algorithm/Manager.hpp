#pragma once

#include <string>
#include <vector>

namespace Calculatrice::Algorithm::Manager
{
	template<class T>
	class Manager
	{
	public:
		inline Manager* add(T* item)
		{
			m_items.push_back(item);
			return this;
		}

		inline T* get(std::string id)

		{
			auto item = std::find_if(
				m_items.begin(),
				m_items.end(),
				[&](T* i) { return i->id() == id; }
			);
			if (item == m_items.end())
				return nullptr;
			else
				return *item;
		}

		inline Manager* set(std::string id, T* newItem)
		{
			T* item = get(id);
			if (item)
				item = newItem;
			else
				add(newItem);
			return this;
		}

		inline std::vector<T*> items()
		{
			return m_items;
		}

	private:
		std::vector<T*> m_items{};
	};
}
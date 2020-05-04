#pragma once

#include <string>
#include <vector>

namespace Calculatrice::Algorithm::Manager
{
	// Cette classe sert à gérer un ensemble de classes du même type. Elle est bâtie sur le templace "class T", ce qui offre beaucoup de possibilités.
	template<class T>
	class Manager
	{
	public:
		// Ajoute un objet au manager
		inline Manager* add(T* item)
		{
			m_items.push_back(item);
			return this;
		}

		// Sert à récupérer un objet dans le manager. S'il est introuvable, alors un pointeur nul est retourné.
		inline T* get(std::string id)
		{
			// Le type ici est auto, car on ne peut pas prévoir si le type d'item sera nullptr ou T**.
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

		// Si un objet est introuvable dans le manager, il est créé. Sinon, il est mis à jour.
		inline Manager* set(std::string id, T* newItem)
		{
			T* item = get(id);
			if (item)
				item = newItem;
			else
				add(newItem);
			return this;
		}

		// Retourne une liste de tous les items.
		inline std::vector<T*> items()
		{
			return m_items;
		}

	private:
		std::vector<T*> m_items{};
	};
}
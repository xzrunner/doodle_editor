#ifndef _FEDITOR_RESOURCES_MGR_H_
#define _FEDITOR_RESOURCES_MGR_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	template<class T>
	class ResourcesMgr
	{
	public:
		static ResourcesMgr* Instance();

		T* getItem(const std::string& filename);

	protected:
		ResourcesMgr();
		~ResourcesMgr();

	private:
		static ResourcesMgr<T>* m_instance;

		std::map<std::string, T*> m_items;

	}; // ResourcesMgr

	template<class T>
	ResourcesMgr<T>* ResourcesMgr<T>::m_instance = NULL;

	template<class T>
	inline ResourcesMgr<T>* ResourcesMgr<T>::Instance()
	{
		if (!m_instance)
		{
			m_instance = new ResourcesMgr<T>;
		}
		return m_instance;
	}

	template<class T>
	inline T* ResourcesMgr<T>::getItem(const std::string& filename)
	{
		std::map<std::string, T*>::iterator itr = m_items.find(filename);
		if (itr == m_items.end())
		{
			T* item = new T;
			bool loaded = item->loadFromFile(filename);
			if (loaded)
			{
				m_items.insert(std::make_pair(filename, item));
				return item;
			}
			else
			{
				delete item;
				return NULL;
			}
		}
		else
		{
			return itr->second;
		}
	}

	template<class T>
	ResourcesMgr<T>::ResourcesMgr()
	{
	}

	template<class T>
	ResourcesMgr<T>::~ResourcesMgr()
	{
		std::map<std::string, T*>::iterator itr = m_items.begin();
		for ( ; itr != m_items.end(); ++itr)
			delete itr->second;
		m_items.clear();
	}
}

#endif // _FEDITOR_RESOURCES_MGR_H_
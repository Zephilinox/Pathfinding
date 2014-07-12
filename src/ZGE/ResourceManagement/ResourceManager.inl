//STD
#include <cassert>
#include <iostream>

namespace zge
{

template <class ResourceType>
std::unique_ptr<ResourceManager<ResourceType>> ResourceManager<ResourceType>::m_Instance;

template <class ResourceType>
ResourceManager<ResourceType>::~ResourceManager()
{
    std::cout << "[ResourceManager] Destructor\n";

    //assert("[ResourceManager::~ResourceManager] Not all resources have been destructed" && m_Resources.size() == 0); //There should be nothing left in the map as all resources are destroyed when ref count hits 0
    std::cout << "[ResourceManager] " << m_Resources.size() << " Resources Unaccounted for:\n";

    for (auto it = m_Resources.begin(); it != m_Resources.end(); it++)
    {
        std::cout << "[" << typeid(ResourceType).name() << "] " << it->first << " @ " << it->second.first << "\n";
    }
}

template <class ResourceType>
ResourceManager<ResourceType>& ResourceManager<ResourceType>::getInstance()
{
    if (m_Instance == nullptr)
    {
        std::cout << "[ResourceManager] Constructed\n";
        m_Instance = std::unique_ptr<ResourceManager<ResourceType>>(new ResourceManager<ResourceType>);
    }

    return *m_Instance.get();
}

template <class ResourceType>
bool ResourceManager<ResourceType>::create(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    if (m_Resources.count(name) == 0)
    {
        //std::cout << "[ResourceManager] Creating " << name << "\n";
        m_Resources[name].first = 1;
        m_Resources[name].second.reset(new ResourceType());
        return true;
    }
    else
    {
        m_Resources[name].first++;
        //std::cout << "[ResourceManager] Increased ref count of " << name << " to " << m_Resources[name].first << "\n";
    }

    return false;
}

template <class ResourceType>
void ResourceManager<ResourceType>::destroy(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto it = m_Resources.find(name);
    if (it == m_Resources.end())
    {
        std::cout << "[ResourceManager] Cannot find the resource " << name << " to destroy\n";
        return;
    }

    if (it->second.first == 1)
    {
        //std::cout << "[ResourceManager] Erasing " << name << "\n";
        m_Resources.erase(it);
    }
    else if (it->second.first > 1)
    {
        it->second.first--;
        //std::cout << "[ResourceManager] Decreased ref count of " << name << " to " << it->second.first << "\n";
    }
    else
    {
        assert(!"[ResourceManager] There are no references to this resource\n");
    }
}

template <class ResourceType>
ResourceType& ResourceManager<ResourceType>::get(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    assert("[ResourceManager::get()] resource does not exist" && m_Resources.count(name)); //Resource exists

    return *m_Resources[name].second.get();
}

} //ZGE

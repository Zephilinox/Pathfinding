//STD
#include <cassert>

template <class ResourceType>
ResourceCache<ResourceType>::ResourceCache()
{
    //std::cout << "[ResourceCache] Constructor \n";
}

template <class ResourceType>
ResourceCache<ResourceType>::~ResourceCache()
{
    //std::cout << "[ResourceCache] Destructor \n";

    this->removeAll();
}

template <class ResourceType>
ResourceType& ResourceCache<ResourceType>::get(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    assert(m_Resources.count(name));
    return m_Resources[name].get()->get();
}

template <class ResourceType>
void ResourceCache<ResourceType>::add(std::string name, std::string path)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    std::transform(path.begin(), path.end(), path.begin(), ::tolower);

    m_Resources[name].reset(new Resource<ResourceType>(path));
}

template <class ResourceType>
void ResourceCache<ResourceType>::remove(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto it = m_Resources.find(name);
    assert(it != m_Resources.end());
    m_Resources.erase(it);
}

template <class ResourceType>
void ResourceCache<ResourceType>::removeAll()
{
    m_Resources.clear();
}

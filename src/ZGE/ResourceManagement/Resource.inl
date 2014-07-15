//STD
#include <algorithm>
#include <locale>

namespace zge
{

template <class ResourceType>
Resource<ResourceType>::Resource(std::string n)
    : m_Name(n)
{
    std::transform(m_Name.begin(), m_Name.end(), m_Name.begin(), ::tolower);

    //std::cout << "[Resource] Constructor | " << m_Name << "\n";
    if (ResourceManager<ResourceType>::getInstance().create(m_Name))
    {
        assert(ResourceManager<ResourceType>::getInstance().get(m_Name).loadFromFile(m_Name));
    }
}

template <class ResourceType>
Resource<ResourceType>::~Resource()
{
    //std::cout << "[Resource] Destructor | " << m_Name << "\n";
    ResourceManager<ResourceType>::getInstance().destroy(m_Name);
}

template <class ResourceType>
Resource<ResourceType>::Resource(const Resource<ResourceType>& res)
{
    this->copyResource(res);
}

template <class ResourceType>
Resource<ResourceType>& Resource<ResourceType>::operator=(const Resource<ResourceType>& res)
{
    this->copyResource(res);
    return *this;
}

template <class ResourceType>
Resource<ResourceType>::operator ResourceType&() const
{
    return ResourceManager<ResourceType>::getInstance().get(m_Name);
}

template <class ResourceType>
ResourceType& Resource<ResourceType>::get()
{
    return ResourceManager<ResourceType>::getInstance().get(m_Name);
}

template <class ResourceType>
void Resource<ResourceType>::copyResource(const Resource<ResourceType>& res)
{
    //std::cout << "[Resource] Copied\n";
    //std::cout << "\tthis = " << m_Name << "\n\tother = " << res.m_Name << "\n";

    if (!m_Name.empty())
    {
        ResourceManager<ResourceType>::getInstance().destroy(m_Name); //Destroy whatever resource res was holding before
    }

    m_Name = res.m_Name;
    ResourceManager<ResourceType>::getInstance().create(m_Name); //Increase reference count
}

} //ZGE

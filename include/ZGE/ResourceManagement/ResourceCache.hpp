#ifndef RESOURCECACHE_HPP
#define RESOURCECACHE_HPP

//STD
#include <map>
#include <memory>
#include <string>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Resource.hpp"

namespace zge
{

template <class ResourceType>
class ResourceCache
{
public:
    ResourceCache();
    ~ResourceCache();
    ResourceCache<ResourceType>(const ResourceCache<ResourceType>&) = delete;
    ResourceCache<ResourceType>& operator=(const ResourceCache<ResourceType>&) = delete;

    ResourceType& get(std::string name);

    void add(std::string name, std::string path);
    void remove(std::string name);
    void removeAll();

private:
    std::map<std::string, std::unique_ptr<Resource<ResourceType>>> m_Resources;
};

/*
*
*
* sf::Sound Specialization
*
*
*/
/*
template <>
class ResourceCache<sf::Sound>
{
public:
    ResourceCache();
    ~ResourceCache();
    ResourceType& get(std::string name);

    void add(std::string name, std::string path);
    void remove(std::string name);
    void removeAll();

private:
    std::map<std::string, std::unique_ptr<Resource<sf::Sound>>> m_Resources;
};*/

#include "ResourceManagement/ResourceCache.inl"

} //ZGE

#endif //RESOURCECACHE_HPP

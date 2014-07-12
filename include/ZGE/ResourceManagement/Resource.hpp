#ifndef RESOURCE_HPP
#define RESOURCE_HPP

//STD
#include <string>
#include <memory>

//3RD
#include <SFML/Audio.hpp>

//SELF
#include "ResourceManager.hpp"

namespace zge
{

template <class ResourceType>
class Resource
{
public:
    Resource(std::string n);
    ~Resource();

    Resource(const Resource& res);
    Resource& operator=(const Resource& res);

    ResourceType& get();

private:
    void copyResource(const Resource<ResourceType>& res);

    std::string m_Name;
};

/*
*
*
* sf::Sound specialization
*
*
*/
template <>
class Resource<sf::Sound>
{
public:
    Resource(std::string n);
    ~Resource();

    Resource(const Resource<sf::Sound>& res);
    Resource<sf::Sound>& operator=(const Resource<sf::Sound>& res);

    sf::Sound& get();

private:
    void copyResource(const Resource<sf::Sound>& res);

    std::string m_Name;
    sf::Sound m_Sound;
    static unsigned int m_GlobalSoundInstances;
};

/*
*
*
* sf::Music specialization
*
*
*/
template <>
class Resource<sf::Music>
{
public:
    Resource(const Resource<sf::Music>& res) = delete;
    Resource<sf::Music>& operator=(const Resource<sf::Music>& res) = delete;

    Resource(std::string n);
    ~Resource();

    sf::Music& get();

private:
    std::string m_Name;
    sf::Music m_Music;
    static unsigned int m_GlobalMusicInstances;
};

} //ZGE

#include "ZGE/ResourceManagement/Resource.inl"

#endif //RESOURCE_HPP

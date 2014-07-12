/*
*
*
* sf::Sound specialization
*
*
*/
#include "ZGE/ResourceManagement/Resource.hpp"

namespace zge
{

unsigned int Resource<sf::Sound>::m_GlobalSoundInstances;

Resource<sf::Sound>::Resource(std::string n)
    : m_Name(n)
{
    std::transform(m_Name.begin(), m_Name.end(), m_Name.begin(), ::tolower);

    //std::cout << "[Resource] Constructor | " << m_Name << "\n";
    m_GlobalSoundInstances++;

    assert("There are more than 256 sound instances, this may be close to OpenAL's limit" && m_GlobalSoundInstances < 256);

    if (ResourceManager<sf::SoundBuffer>::getInstance().create(m_Name))
    {
        assert("[Resource<sf::Sound>::Resource] Could not load sf::SoundBuffer from file" && ResourceManager<sf::SoundBuffer>::getInstance().get(m_Name).loadFromFile(m_Name));
    }

    m_Sound.setBuffer(ResourceManager<sf::SoundBuffer>::getInstance().get(m_Name));
}

Resource<sf::Sound>::~Resource()
{
    //std::cout << "[Resource] Destructor | " << m_Name << "\n";
    //std::cout << "\t[Resource] Global Sound Instances = " << m_GlobalSoundInstances << "\n";
    m_GlobalSoundInstances--;
    ResourceManager<sf::SoundBuffer>::getInstance().destroy(m_Name);
}

Resource<sf::Sound>::Resource(const Resource<sf::Sound>& res)
{
    this->copyResource(res);
}

Resource<sf::Sound>& Resource<sf::Sound>::operator=(const Resource<sf::Sound>& res)
{
    this->copyResource(res);
    return *this;
}

sf::Sound& Resource<sf::Sound>::get()
{
    return m_Sound;
}

void Resource<sf::Sound>::copyResource(const Resource<sf::Sound>& res)
{
    //std::cout << "[Resource] Copied\n";
    //std::cout << "\tthis = " << m_Name << "\n\tother = " << res.m_Name << "\n";

    if (!m_Name.empty())
    {
        ResourceManager<sf::SoundBuffer>::getInstance().destroy(m_Name); //Destroy whatever resource res was holding before
        m_GlobalSoundInstances--;
    }

    m_Name = res.m_Name;
    m_Sound = res.m_Sound;
    ResourceManager<sf::SoundBuffer>::getInstance().create(m_Name); //Increase reference count
    m_GlobalSoundInstances++;
}

/*
*
*
* sf::Music specialization
*
*
*/
#include "ZGE/ResourceManagement/Resource.hpp"

unsigned int Resource<sf::Music>::m_GlobalMusicInstances;

Resource<sf::Music>::Resource(std::string n)
    : m_Name(n)
{
    std::transform(m_Name.begin(), m_Name.end(), m_Name.begin(), ::tolower);

    //std::cout << "[Resource] Constructor | " << m_Name << "\n";
    m_GlobalMusicInstances++;

    assert(m_GlobalMusicInstances < 256);

    m_Music.openFromFile(m_Name);
}

Resource<sf::Music>::~Resource()
{
    //std::cout << "[Resource] Destructor | " << m_Name << "\n";
    //std::cout << "\t[Resource] Global Music Instances = " << m_GlobalMusicInstances << "\n";
    m_GlobalMusicInstances--;
}

sf::Music& Resource<sf::Music>::get()
{
    return m_Music;
}

} //ZGE

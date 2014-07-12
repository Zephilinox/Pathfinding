#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

//STD
#include <map>
#include <memory>

namespace zge
{

template <class ResourceType>
class ResourceManager
{
public:
    ~ResourceManager();
    static ResourceManager& getInstance();

    bool create(std::string name);
    void destroy(std::string name);
    ResourceType& get(std::string name);

private:
    ResourceManager() = default;
    static std::unique_ptr<ResourceManager> m_Instance;

    std::map<std::string, std::pair<unsigned int, std::unique_ptr<ResourceType>>> m_Resources;
};

}

#include "ZGE/ResourceManagement/ResourceManager.inl"

#endif //RESOURCEMANAGER_HPP

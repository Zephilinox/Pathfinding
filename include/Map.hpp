#ifndef MAP_HPP
#define MAP_HPP

//STD
#include <vector>
#include <memory>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Tile.hpp"

class Map : public sf::Drawable
{
public:
    Map();
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



private:
    void createMap();

    std::vector<std::vector<Tile>> m_Tiles;
};

#endif //MAP_HPP

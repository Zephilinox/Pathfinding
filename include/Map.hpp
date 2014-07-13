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

    Tile& getTile(sf::Vector2i pos);

    bool inMapBounds(sf::Vector2i pos);
    sf::Vector2i worldToMapCoordinates(sf::Vector2f pos);

private:
    void createMap();

    std::vector<std::vector<Tile>> m_Tiles;

    TileState m_MouseRightClickBrush;
};

#endif //MAP_HPP

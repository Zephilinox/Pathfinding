#ifndef MAP_HPP
#define MAP_HPP

//STD
#include <iostream>
#include <vector>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Square.hpp"

class Map : public sf::Drawable
{
public:
    Map(const sf::Vector2u& gridSize);

    Square& getSquare(const sf::Vector2u& facePos);

    sf::Vector2f getFaceWorldPos(const sf::Vector2u& facePos);
    sf::Vector2u getFacePos(const sf::Vector2f& worldPos);

    std::vector<sf::Vector2u> findAdjacentFaces(const sf::Vector2u& facePos);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::string toString(unsigned int val);
    unsigned int fromString(const std::string& str);

private:
    std::vector<std::vector<Square>> m_Grid;

    sf::Font arial;

    const unsigned int m_TILE_SIZE = 64;
};

#endif // MAP_HPP

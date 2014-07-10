#ifndef TILE_HPP
#define TILE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

class Tile : public sf::Drawable
{
public:
    Tile(sf::Vector2f pos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::RectangleShape m_Square;
};

#endif //TILE_HPP

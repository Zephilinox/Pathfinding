#include "Tile.hpp"

//STD

//3RD

//SELF

Tile::Tile(sf::Vector2f pos)
{
    m_Square.setPosition(pos);
    m_Square.setSize(sf::Vector2f(16, 16));
    m_Square.setOutlineThickness(1);
    m_Square.setOutlineColor(sf::Color::Black);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Square, states);
}

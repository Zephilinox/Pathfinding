#include "Map.hpp"

//STD
#include <iostream>

//3RD

//SELF

Map::Map()
{
    createMap();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& row : m_Tiles)
    {
        for (auto tile : row)
        {
            target.draw(tile, states);
        }
    }
}

void Map::createMap()
{
    m_Tiles.clear();

    for (unsigned h = 0; h < 960/16; ++h)
    {
        std::vector<Tile> row;
        for (unsigned w = 0; w < 960/16; ++w)
        {
            Tile tile(sf::Vector2f(w*16, h*16));
            row.push_back(tile);
        }
        m_Tiles.push_back(row);
    }
}

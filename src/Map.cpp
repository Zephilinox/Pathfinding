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
        for (auto& tile : row)
        {
            //target.draw(*tile.get(), states);
        }
    }
}

void Map::createMap()
{
    m_Tiles.clear();
    m_Tiles.resize(960/16);
    /*for (unsigned i = 0; i < m_Tiles.size(); ++i)
    {
        m_Tiles[i].resize(960/16);
    }*/

    for (unsigned h = 0; h <= 960/16; ++h)
    {
        for (unsigned w = 0; w <= 960/16; ++w)
        {
            //std::shared_ptr<Tile> tile(new Tile(sf::Vector2f(w * 16, h * 16)));
            Tile tile;
            m_Tiles[h].push_back(tile);
        }
    }
}

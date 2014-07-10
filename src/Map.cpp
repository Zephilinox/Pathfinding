#include "Map.hpp"

//STD
#include <iostream>

//3RD

//SELF
#include "Constants.h"

Map::Map()
{
    createMap();
}

void Map::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    for (auto& row : m_Tiles)
    {
        for (auto& tile : row)
        {
            tile.handleEvent(event, window);
        }
    }
}

void Map::update(const float dt, sf::RenderWindow& window)
{
    for (auto& row : m_Tiles)
    {
        for (auto& tile : row)
        {
            tile.update(dt, window);
        }
    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto row : m_Tiles)
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
    m_Tiles.reserve(60);

    for (unsigned h = 0; h < Constant::windowHeight/16; ++h)
    {
        std::vector<Tile> row;
        row.reserve(Constant::windowWidth/16);;

        for (unsigned w = 0; w < Constant::windowWidth/16; ++w)
        {
            Tile tile(sf::Vector2f(w*16, h*16));
            row.push_back(tile);
        }

        m_Tiles.push_back(row);
    }
}

#include "Map.hpp"

//STD
#include <iostream>

//3RD

//SELF
#include "Constants.hpp"

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
    sf::Vector2i mouseTilePos(sf::Mouse::getPosition(window).x / Constant::tileSize, sf::Mouse::getPosition(window).y / Constant::tileSize);

    if (inMapBounds(mouseTilePos))
    {
        Tile& t = m_Tiles[mouseTilePos.y][mouseTilePos.x];

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if (m_MouseRightClickBrush == TileState::Unknown)
            {
                if (t.getState() == TileState::Empty)
                {
                    m_MouseRightClickBrush = TileState::Wall;
                }
                else
                {
                    m_MouseRightClickBrush = TileState::Empty;
                }
            }

            t.setState(m_MouseRightClickBrush);
        }
        else
        {
            m_MouseRightClickBrush = TileState::Unknown;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        for (auto& row : m_Tiles)
        {
            for (auto& tile : row)
            {
                tile.setState(TileState::Empty);
                tile.getNode().setState(NodeState::Unknown);
            }
        }

        m_SourceTilePosition = sf::Vector2i(-1, -1);
        m_TargetTilePosition = sf::Vector2i(-1, -1);
    }

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
    for (auto& row : m_Tiles)
    {
        for (auto& tile : row)
        {
            target.draw(tile, states);
        }
    }
}

void Map::createMap()
{
    m_Tiles.clear();
    m_Tiles.reserve(Constant::windowHeight / Constant::tileSize);

    for (unsigned h = 0; h < Constant::windowHeight / Constant::tileSize; ++h)
    {
        std::vector<Tile> row;
        row.reserve(Constant::windowWidth / Constant::tileSize);;

        for (unsigned w = 0; w < Constant::windowWidth / Constant::tileSize; ++w)
        {
            Tile tile(sf::Vector2f(w * Constant::tileSize, h* Constant::tileSize));
            row.push_back(tile);
        }

        m_Tiles.push_back(row);
    }
}

Tile& Map::getTile(sf::Vector2i pos)
{
    return m_Tiles[pos.y][pos.x];
}

bool Map::inMapBounds(sf::Vector2i pos)
{
    if (pos.x < 0 ||
        pos.x >= signed(m_Tiles[0].size()) ||
        pos.y < 0 ||
        pos.y >= signed(m_Tiles.size()))
    {
        return false;
    }

    return true;
}

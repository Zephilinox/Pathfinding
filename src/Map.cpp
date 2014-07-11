#include "Map.hpp"

//STD
#include <iostream>

//3RD

//SELF
#include "Constants.h"

Map::Map():
m_SourceTilePosition(-1, -1),
m_TargetTilePosition(-1, -1),
m_MouseClickDelay(sf::seconds(0.3f))
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
    sf::Vector2i mouseTilePos(sf::Mouse::getPosition(window).x / 16, sf::Mouse::getPosition(window).y / 16);

    if (inMapBounds(mouseTilePos))
    {
        Tile& t = m_Tiles[mouseTilePos.y][mouseTilePos.x];

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            m_MouseClickCoolDown.getElapsedTime().asSeconds() >= m_MouseClickDelay.asSeconds())
        {
            m_MouseClickCoolDown.restart();

            if (t.getState() == TileState::Empty ||
                t.getState() == TileState::Wall)
            {
                if (m_SourceTilePosition == sf::Vector2i(-1, -1))
                {
                    t.setState(TileState::Source);
                    m_SourceTilePosition = mouseTilePos;
                }
                else if (m_TargetTilePosition == sf::Vector2i(-1, -1))
                {
                    t.setState(TileState::Target);
                    m_TargetTilePosition = mouseTilePos;
                }
            }
            else if (t.getState() == TileState::Source)
            {
                if (m_TargetTilePosition == sf::Vector2i(-1, -1))
                {
                    t.setState(TileState::Target);
                    m_TargetTilePosition = mouseTilePos;
                    m_SourceTilePosition = sf::Vector2i(-1, -1);
                }
            }
            else if (t.getState() == TileState::Target)
            {
                if (m_SourceTilePosition == sf::Vector2i(-1, -1))
                {
                    t.setState(TileState::Source);
                    m_SourceTilePosition = mouseTilePos;
                    m_TargetTilePosition = sf::Vector2i(-1, -1);
                }
            }
        }

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

            if (t.getState() == TileState::Source)
            {
                m_SourceTilePosition = sf::Vector2i(-1, -1);
            }
            else if (t.getState() == TileState::Target)
            {
                m_TargetTilePosition = sf::Vector2i(-1, -1);
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

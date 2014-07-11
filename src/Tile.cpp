#include "Tile.hpp"

//STD
#include <iostream>

//3RD

//SELF

Tile::Tile(sf::Vector2f pos):
m_State(TileState::Empty)
{
    m_Square.setPosition(pos);
    m_Square.setSize(sf::Vector2f(16, 16));
    m_Square.setOutlineThickness(1);
    m_Square.setOutlineColor(sf::Color::Black);
}

void Tile::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    switch (event.type)
    {
        default:
        {
            break;
        }
    }
}

void Tile::update(const float dt, sf::RenderWindow& window)
{

}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Square, states);
}

void Tile::setState(TileState state)
{
    m_State = state;

    updateColour();
}

TileState Tile::getState()
{
    return m_State;
}

void Tile::updateColour()
{
    switch (m_State)
    {
        case TileState::Empty:
        {
            m_Square.setFillColor(sf::Color::White);
            break;
        }

        case TileState::Source:
        {
            m_Square.setFillColor(sf::Color(50, 100, 200)); //Light Blue
            break;
        }

        case TileState::Target:
        {
            m_Square.setFillColor(sf::Color(200, 50, 50)); //Light Red
            break;
        }

        case TileState::Wall:
        {
            m_Square.setFillColor(sf::Color(100, 100, 100)); //Light Grey
            break;
        }

        case TileState::Path:
        {
            m_Square.setFillColor(sf::Color(200, 180, 50)); //Light Orange
            break;
        }

        case TileState::CheckedPath:
        {
            m_Square.setFillColor(sf::Color(50, 255, 180)); //Light Green
            break;
        }

        default:
        {
            m_Square.setFillColor(sf::Color::Black);
            std::cout << "Unknown TileState\n";
            break;
        }
    }
}

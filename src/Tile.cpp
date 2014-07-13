#include "Tile.hpp"

//STD
#include <iostream>

//3RD

//SELF

Tile::Tile(sf::Vector2f pos):
m_State(TileState::Empty),
m_Node(pos)
{
    m_Square.setPosition(pos);
    m_Square.setSize(sf::Vector2f(Constant::tileSize, Constant::tileSize));
    m_Square.setOutlineThickness(2);
    m_Square.setOutlineColor(sf::Color::Black);

    updateColour();
}

void Tile::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    m_Node.handleEvent(event, window);

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
    m_Node.update(dt, window);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Square, states);
    m_Node.draw(target, states);
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

Node& Tile::getNode()
{
    return m_Node;
}

void Tile::reset()
{
    m_Node.reset();
    setState(TileState::Empty);
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

        case TileState::Wall:
        {
            m_Square.setFillColor(sf::Color(100, 100, 100)); //Light Grey
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

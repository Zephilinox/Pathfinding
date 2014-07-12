#include "Node.hpp"

//STD
#include <iostream>

//3RD

//SELF

Node::Node(sf::Vector2f pos):
m_State(NodeState::Unknown),
m_Font("fonts/arial.ttf")
{
    m_Square.setPosition(pos);
    m_Square.setSize(sf::Vector2f(Constant::tileSize, Constant::tileSize));

    updateColour();

    m_F.setFont(m_Font.get());
    m_G.setFont(m_Font.get());
    m_H.setFont(m_Font.get());

    m_F.setColor(sf::Color::Black);
    m_G.setColor(sf::Color::Black);
    m_H.setColor(sf::Color::Black);

    m_F.setCharacterSize(10);
    m_G.setCharacterSize(10);
    m_H.setCharacterSize(10);

    m_F.setPosition(pos.x + int((Constant::tileSize - m_F.getLocalBounds().width)/2) - m_F.getLocalBounds().left,
                    pos.y - m_F.getLocalBounds().top + 2);

    m_G.setPosition(pos.x + int((Constant::tileSize - m_G.getLocalBounds().width)/2) - m_G.getLocalBounds().left,
                    pos.y + int((Constant::tileSize - m_G.getLocalBounds().height)/2) - m_G.getLocalBounds().top);

    m_H.setPosition(pos.x + int((Constant::tileSize - m_H.getLocalBounds().width)/2) - m_H.getLocalBounds().left,
                    pos.y + Constant::tileSize - m_H.getLocalBounds().height - m_H.getLocalBounds().top - 4);
}

void Node::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    switch (event.type)
    {
        default:
        {
            break;
        }
    }
}

void Node::update(const float dt, sf::RenderWindow& window)
{
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Square, states);
    target.draw(m_F, states);
    target.draw(m_G, states);
    target.draw(m_H, states);
}

void Node::setState(NodeState state)
{
    m_State = state;

    updateColour();
}

NodeState Node::getState()
{
    return m_State;
}

void Node::setMovementCost(int cost)
{
    m_MovementCost = cost;
    m_G.setString(zge::toString(m_MovementCost));
    m_F.setString(zge::toString(m_MovementCost + m_HeuristicCost));
}

int Node::getMovementCost()
{
    return m_MovementCost;
}

void Node::setHeuristicCost(int cost)
{
    m_HeuristicCost = cost;
    m_H.setString(zge::toString(m_HeuristicCost));
    m_F.setString(zge::toString(m_MovementCost + m_HeuristicCost));
}

int Node::getHeuristicCost()
{
    return m_HeuristicCost;
}

void Node::updateColour()
{
    switch (m_State)
    {
        case NodeState::Unknown:
        {
            m_Square.setFillColor(sf::Color(255, 255, 255, 0));
            break;
        }

        case NodeState::Source:
        {
            m_Square.setFillColor(sf::Color(50, 100, 200)); //Light Blue
            break;
        }

        case NodeState::Target:
        {
            m_Square.setFillColor(sf::Color(200, 50, 50)); //Light Red
            break;
        }

        case NodeState::Path:
        {
            m_Square.setFillColor(sf::Color(200, 180, 50)); //Light Orange
            break;
        }

        case NodeState::CheckedPath:
        {
            m_Square.setFillColor(sf::Color(50, 255, 180)); //Light Green
            break;
        }

        default:
        {
            m_Square.setFillColor(sf::Color::Black);
            std::cout << "Unknown NodeState\n";
            break;
        }
    }
}

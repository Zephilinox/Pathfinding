#include "Node.hpp"

//STD
#include <iostream>

//3RD

//SELF

Node::Node(sf::Vector2f pos):
m_ParentNodePosition(sf::Vector2i(-1, -1)),
m_State(NodeState::Unknown),
m_Font("fonts/arial.ttf"),
m_MovementCost(0),
m_HeuristicCost(0)
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

void Node::setMovementCost(unsigned cost)
{
    m_MovementCost = cost;
    m_G.setString(zge::toString(m_MovementCost));
    m_F.setString(zge::toString(m_MovementCost + m_HeuristicCost));

    updateFStringPosition();
    updateGStringPosition();
}

unsigned Node::getMovementCost()
{
    return m_MovementCost;
}

void Node::setHeuristicCost(unsigned cost)
{
    m_HeuristicCost = cost;
    m_H.setString(zge::toString(m_HeuristicCost));
    m_F.setString(zge::toString(m_MovementCost + m_HeuristicCost));

    updateFStringPosition();
    updateHStringPosition();
}

unsigned Node::getHeuristicCost()
{
    return m_HeuristicCost;
}
sf::Vector2f Node::getPosition()
{
    return m_Square.getPosition();
}
void Node::setParentNodePosition(sf::Vector2i pos)
{
    m_ParentNodePosition = pos;
}

sf::Vector2i Node::getParentNodePosition()
{
    return m_ParentNodePosition;
}

void Node::reset()
{
    m_MovementCost = 0;
    m_HeuristicCost = 0;
    m_ParentNodePosition = sf::Vector2i(-1, -1);

    setState(NodeState::Unknown);

    m_F.setString("");
    m_G.setString("");
    m_H.setString("");
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
            m_Square.setFillColor(sf::Color(100, 200, 255)); //Light Blue
            break;
        }

        case NodeState::Target:
        {
            m_Square.setFillColor(sf::Color(255, 100, 100)); //Light Red
            break;
        }

        case NodeState::OpenList:
        {
            m_Square.setFillColor(sf::Color(255, 200, 100)); //Light Orange
            break;
        }

        case NodeState::ClosedList:
        {
            m_Square.setFillColor(sf::Color(100, 255, 200)); //Light Green
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

void Node::updateFStringPosition()
{
    m_F.setPosition(m_Square.getPosition().x + int((Constant::tileSize - m_F.getLocalBounds().width)/2) - m_F.getLocalBounds().left,
                    (m_Square.getPosition().y - m_F.getLocalBounds().top + 2));
}

void Node::updateGStringPosition()
{

    m_G.setPosition(m_Square.getPosition().x + int((Constant::tileSize - m_G.getLocalBounds().width)/2) - m_G.getLocalBounds().left,
                    (m_Square.getPosition().y + Constant::tileSize - m_G.getLocalBounds().height - m_G.getLocalBounds().top - 4));
}

void Node::updateHStringPosition()
{
    m_H.setPosition(m_Square.getPosition().x + int((Constant::tileSize - m_H.getLocalBounds().width)/2) - m_H.getLocalBounds().left,
                    (m_Square.getPosition().y + int((Constant::tileSize - m_H.getLocalBounds().height)/2) - m_H.getLocalBounds().top));
}


#include "Pathfinder.hpp"

//STD
#include <iostream>

//3RD

//SELF

Pathfinder::Pathfinder(Map& map):
m_Map(map),
m_CardinalMovementCost(10),
m_IntercardinalMovementCost(14),
m_SourceNodePosition(-1, -1),
m_TargetNodePosition(-1, -1),
m_MouseClickDelay(sf::seconds(0.3f))
{

}

void Pathfinder::handleEvent(sf::Event& e, sf::RenderWindow& window)
{

}

void Pathfinder::update(const float dt, sf::RenderWindow& window)
{
    //Because map clears the node data when it resets, we need to check that our positions for the source and target nodes are still valid.

    if (m_Map.inMapBounds(m_SourceNodePosition) &&
        m_Map.getTile(m_SourceNodePosition).getNode().getState() != NodeState::Source)
    {
        m_SourceNodePosition = sf::Vector2i(-1, -1);
    }

    if (m_Map.inMapBounds(m_TargetNodePosition) &&
        m_Map.getTile(m_TargetNodePosition).getNode().getState() != NodeState::Target)
    {
        m_TargetNodePosition = sf::Vector2i(-1, -1);
    }

    sf::Vector2i mouseTilePos(sf::Mouse::getPosition(window).x / Constant::tileSize, sf::Mouse::getPosition(window).y / Constant::tileSize);

    if (m_Map.inMapBounds(mouseTilePos))
    {
        Tile& t = m_Map.getTile(mouseTilePos);
        Node& n = t.getNode();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            m_MouseClickCoolDown.getElapsedTime().asSeconds() >= m_MouseClickDelay.asSeconds())
        {
            m_MouseClickCoolDown.restart();

            if (n.getState() == NodeState::Unknown)
            {
                if (m_SourceNodePosition == sf::Vector2i(-1, -1)) //Set the node as the source
                {
                    n.setState(NodeState::Source);
                    m_SourceNodePosition = mouseTilePos;
                }
                else if (m_TargetNodePosition == sf::Vector2i(-1, -1)) //Set the node as the target
                {
                    n.setState(NodeState::Target);
                    m_TargetNodePosition = mouseTilePos;
                }
            }
            else if (n.getState() == NodeState::Source)
            {
                if (m_TargetNodePosition == sf::Vector2i(-1, -1)) //Toggle between source and target state
                {
                    n.setState(NodeState::Target);
                    m_TargetNodePosition = mouseTilePos;
                    m_SourceNodePosition = sf::Vector2i(-1, -1);
                }
            }
            else if (n.getState() == NodeState::Target)
            {
                if (m_SourceNodePosition == sf::Vector2i(-1, -1)) //Toggle between source and target state
                {
                    n.setState(NodeState::Source);
                    m_SourceNodePosition = mouseTilePos;
                    m_TargetNodePosition = sf::Vector2i(-1, -1);
                }
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            //Clear node of being source or target

            if (n.getState() == NodeState::Source)
            {
                m_SourceNodePosition = sf::Vector2i(-1, -1);
                n.setState(NodeState::Unknown);
            }
            else if (n.getState() == NodeState::Target)
            {
                m_TargetNodePosition = sf::Vector2i(-1, -1);
                n.setState(NodeState::Unknown);
            }
        }
    }
}

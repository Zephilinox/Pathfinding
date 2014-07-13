#include "Pathfinder.hpp"

//STD
#include <iostream>
#include <limits.h>

//3RD

//SELF

Pathfinder::Pathfinder(Map& map):
m_Map(map),
m_CardinalMovementCost(10),
m_IntercardinalMovementCost(14),
m_SourceNodePosition(-1, -1),
m_TargetNodePosition(-1, -1),
m_MouseClickDelay(sf::seconds(0.3f)),
m_StepDelay(sf::seconds(0.2f))
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            m_OpenList.clear();
            m_ClosedList.clear();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            step();
        }
    }
}

unsigned Pathfinder::calculateHeuristicCost(sf::Vector2i from, sf::Vector2i to)
{
    return (std::abs(from.x - to.x) + std::abs(from.y - to.y)) * m_CardinalMovementCost;
}

unsigned Pathfinder::calculateMovementCost(sf::Vector2i from, sf::Vector2i to)
{
    if (from.x == to.x ||
        from.y == to.y)
    {
        return m_CardinalMovementCost;
    }
    else
    {
        return m_IntercardinalMovementCost;
    }
}

void Pathfinder::step()
{
    if (m_StepCooldown.getElapsedTime().asSeconds() > m_StepDelay.asSeconds())
    {
        m_StepCooldown.restart();
    }
    else
    {
        return;
    }

    std::cout << "Stepping\n";

    std::cout << m_OpenList.size() << " " << m_ClosedList.size() << "\n";
    if (!m_Map.inMapBounds(m_SourceNodePosition) ||
        !m_Map.inMapBounds(m_TargetNodePosition))
    {
        return;
    }

    if (m_ClosedList.size() != 0 &&
        m_ClosedList[0] == m_SourceNodePosition &&
        m_OpenList.size() > 0 &&
        m_ClosedList.back() != m_TargetNodePosition)
    {
        unsigned lowestFScore = UINT_MAX;
        unsigned lowestFScoreNode = 0;
        for (unsigned i = 0; i < m_OpenList.size(); ++i)
        {
            Node& n = m_Map.getTile(m_OpenList[i]).getNode();
            if (n.getHeuristicCost() + n.getMovementCost() < lowestFScore)
            {
                lowestFScore = n.getHeuristicCost() + n.getMovementCost();
                lowestFScoreNode = i;
            }
        }

        std::cout << "Lowest F Score = " << lowestFScore << "\n";

        m_ClosedList.push_back(m_OpenList[lowestFScoreNode]);
        m_OpenList.erase(m_OpenList.begin() + lowestFScoreNode);

        if (m_ClosedList.back() == m_TargetNodePosition)
        {
            std::cout << "Found target\n";
            return;
        }
        else
        {
            std::cout << m_ClosedList.back().x << ", " <<  m_ClosedList.back().y << " / " << m_TargetNodePosition.x << ", " << m_TargetNodePosition.y << "\n";
        }

        auto adjacentNodes = getAdjacentNodes(m_ClosedList.back());

        for (auto& nodePos : adjacentNodes)
        {
            Node& adjNode = m_Map.getTile(nodePos).getNode();

            if (std::find(m_OpenList.begin(), m_OpenList.end(), nodePos) == m_OpenList.end())
            {
                adjNode.setParentNodePosition(m_ClosedList.back());
                adjNode.setHeuristicCost(calculateHeuristicCost(nodePos, m_TargetNodePosition));
                adjNode.setMovementCost(calculateMovementCost(m_ClosedList.back(), nodePos) + adjNode.getMovementCost());

                if (adjNode.getState() != NodeState::Source &&
                    adjNode.getState() != NodeState::Target)
                {
                    adjNode.setState(NodeState::OpenList);
                }

                m_OpenList.push_back(nodePos);
            }
            else if (adjNode.getMovementCost() > calculateMovementCost(m_ClosedList.back(), nodePos))
            {
                adjNode.setParentNodePosition(m_ClosedList.back());
                adjNode.setHeuristicCost(calculateHeuristicCost(nodePos, m_TargetNodePosition));
                adjNode.setMovementCost(calculateMovementCost(m_ClosedList.back(), nodePos) + adjNode.getMovementCost());
            }
        }
    }
    else if (m_Map.getTile(m_SourceNodePosition).getNode().getState() == NodeState::Source)
    {
        m_OpenList.push_back(m_SourceNodePosition);
        auto adjacentNodes = getAdjacentNodes(m_OpenList.back());

        m_ClosedList.push_back(m_OpenList.front());
        m_OpenList.erase(m_OpenList.begin());

        for (auto& nodePos : adjacentNodes)
        {
            Node& n = m_Map.getTile(nodePos).getNode();
            n.setState(NodeState::OpenList);
            n.setParentNodePosition(m_ClosedList.back());
            n.setHeuristicCost(calculateHeuristicCost(nodePos, m_TargetNodePosition));
            n.setMovementCost(calculateMovementCost(m_ClosedList.back(), nodePos) + n.getMovementCost());
            m_OpenList.push_back(nodePos);
        }
    }
}

std::vector<sf::Vector2i> Pathfinder::getAdjacentNodes(sf::Vector2i pos)
{
    std::vector<sf::Vector2i> nodes;
    std::vector<sf::Vector2i> nodePositions {
                                            sf::Vector2i(pos.x - 1, pos.y),
                                            sf::Vector2i(pos.x + 1, pos.y),
                                            sf::Vector2i(pos.x, pos.y - 1),
                                            sf::Vector2i(pos.x, pos.y + 1),
                                            sf::Vector2i(pos.x - 1, pos.y - 1),
                                            sf::Vector2i(pos.x - 1, pos.y + 1),
                                            sf::Vector2i(pos.x + 1, pos.y - 1),
                                            sf::Vector2i(pos.x + 1, pos.y + 1),
                                            };

    for (sf::Vector2i nodePos : nodePositions)
    {
        if (m_Map.inMapBounds(nodePos))
        {
            Tile& t = m_Map.getTile(nodePos);
            if (t.getState() != TileState::Wall)
            {
                nodes.push_back(m_Map.worldToMapCoordinates(t.getNode().getPosition()));
            }
        }
    }

    return nodes;
}

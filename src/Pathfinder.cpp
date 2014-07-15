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
m_StepDelay(sf::seconds(0.01f))
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

    if (m_Map.inMapBounds(mouseTilePos) &&
            m_OpenList.size() == 0 &&
            m_ClosedList.size() == 0)
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

    std::cout << "\nStepping\n";

    if (!m_Map.inMapBounds(m_SourceNodePosition) || //Make sure the source and target are valid
        !m_Map.inMapBounds(m_TargetNodePosition))
    {
        std::cout << "Source or Target is invalid\n";
        std::cout << m_SourceNodePosition.x << ", " << m_SourceNodePosition.y << "\n";
        std::cout << m_TargetNodePosition.x << ", " << m_TargetNodePosition.y << "\n";
        return;
    }

    std::cout << "Source and Target are valid\n";

    if (m_OpenList.size() == 0 &&
        m_ClosedList.size() == 0)
    {
        std::cout << "Adding source node\n";
        m_OpenList.push_back(m_SourceNodePosition);
    }
    else if ((m_ClosedList.size() != 0 && //make sure there is an object at the back
             m_ClosedList.back() == m_TargetNodePosition) || //If the target is in the closed list then we found a path
             m_OpenList.size() == 0) //If the open list is empty then we have checked the entire map and not found a path
    {
        std::cout << "Path found\n";

        //Reset the nodes we have modified
        for (sf::Vector2i pos : m_ClosedList)
        {
            m_Map.getTile(pos).getNode().resetCosts();
            m_Map.getTile(pos).getNode().resetState();
        }

        for (sf::Vector2i pos : m_OpenList)
        {
            m_Map.getTile(pos).getNode().resetCosts();
            m_Map.getTile(pos).getNode().resetState();
        }

        //Draw the path
        sf::Vector2i parentPos = m_ClosedList.back();
        while (m_Map.inMapBounds(parentPos))
        {
            std::cout << "Parent Position = [" << parentPos.x << ", " << parentPos.y << "]\n";
            m_Map.getTile(parentPos).getNode().setState(NodeState::ClosedList);
            parentPos = m_Map.getTile(parentPos).getNode().getParentNodePosition();
        }

        //Draw source and target
        m_Map.getTile(m_ClosedList.front()).getNode().setState(NodeState::Source);
        m_Map.getTile(m_ClosedList.back()).getNode().setState(NodeState::Target);
    }
    else
    {
        std::cout << "Finding lowest scored node\n";
        //Find node in open list with lowest score, and move it to closed list.
        unsigned lowestScoreNodeIndex = getLowestScoreNodeIndex(m_OpenList);
        m_ClosedList.push_back(m_OpenList[lowestScoreNodeIndex]);

        {
            Node& n = m_Map.getTile(m_ClosedList.back()).getNode();
            if (n.getState() != NodeState::Source && //If the node isn't the source or target node;
                n.getState() != NodeState::Target)
            {
                n.setState(NodeState::ClosedList);
            }
        }

        m_OpenList.erase(m_OpenList.begin() + lowestScoreNodeIndex);

        std::cout << "Finding adjacent nodes\n";
        //Find adjacent nodes of current node
        auto adjNodePoses = getAdjacentNodes(m_ClosedList.back());
        for (sf::Vector2i& nodePos : adjNodePoses)
        {
            if (m_Map.getTile(nodePos).getState() != TileState::Wall && //Can be walked on
                std::find(m_ClosedList.begin(), m_ClosedList.end(), nodePos) == m_ClosedList.end()) //is not on the closed list
            {
                Node& n = m_Map.getTile(nodePos).getNode();

                if (std::find(m_OpenList.begin(), m_OpenList.end(), nodePos) == m_OpenList.end()) //is not on the open list
                {
                    std::cout << "Found undiscovered valid node\n";
                    //Recalculated costs and set parent node
                    updateNodeInfo(nodePos, m_ClosedList.back());

                    if (n.getState() != NodeState::Source && //Make sure we don't override the source or target tile.
                        n.getState() != NodeState::Target)
                    {
                        n.setState(NodeState::OpenList);
                    }

                    m_OpenList.push_back(nodePos);
                }
                else if (n.getMovementCost() > calculateMovementCost(m_ClosedList.back(), nodePos))//this path to the node is shorter
                {
                    std::cout << "Found better path\n";
                    //Recalculated costs and set parent node
                    updateNodeInfo(nodePos, m_ClosedList.back());
                }
            }
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

unsigned Pathfinder::getLowestScoreNodeIndex(std::vector<sf::Vector2i> nodes)
{
    unsigned lowestScore = UINT_MAX;
    unsigned lowestScoreNode = 0;
    for (unsigned i = 0; i < nodes.size(); ++i)
    {
        Node& n = m_Map.getTile(m_OpenList[i]).getNode();
        if (n.getHeuristicCost() + n.getMovementCost() < lowestScore)
        {
            lowestScore = n.getHeuristicCost() + n.getMovementCost();
            lowestScoreNode = i;
        }
    }

    return lowestScoreNode;
}

void Pathfinder::updateNodeInfo(sf::Vector2i pos, sf::Vector2i parentPos)
{
    Node& n = m_Map.getTile(pos).getNode();

    n.setHeuristicCost(calculateHeuristicCost(pos, m_TargetNodePosition));
    n.setMovementCost(calculateMovementCost(parentPos, pos));
    n.setParentNodePosition(parentPos);
}

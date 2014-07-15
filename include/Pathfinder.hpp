#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

//STD
#include <memory>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Map.hpp"
#include "Tile.hpp"
#include "Node.hpp"

class Pathfinder
{
public:
    Pathfinder(Map& map);
    void handleEvent(sf::Event& e, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);

    unsigned calculateHeuristicCost(sf::Vector2i source, sf::Vector2i target);
    unsigned calculateMovementCost(sf::Vector2i source, sf::Vector2i target);

    void step();

private:
    std::vector<sf::Vector2i> getAdjacentNodes(sf::Vector2i pos);
    unsigned getLowestScoreNodeIndex(std::vector<sf::Vector2i> nodes);
    void updateNodeInfo(sf::Vector2i pos, sf::Vector2i parentPos);

    Map& m_Map;

    const unsigned m_CardinalMovementCost; //N, E, S, W
    const unsigned m_IntercardinalMovementCost; //NE, SE, SW, NW

    sf::Vector2i m_SourceNodePosition;
    sf::Vector2i m_TargetNodePosition;

    sf::Clock m_MouseClickCoolDown;
    sf::Time m_MouseClickDelay;

    std::vector<sf::Vector2i> m_OpenList;
    std::vector<sf::Vector2i> m_ClosedList;

    sf::Clock m_StepCooldown;
    sf::Time m_StepDelay;
};

#endif //PATHFINDER_HPP

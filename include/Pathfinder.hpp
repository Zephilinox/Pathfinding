#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

//STD
#include <memory>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Map.hpp"
#include "Tile.hpp"

enum HeuristicAlgorithm {Unknown, Manhattan};

class Pathfinder
{
public:
    Pathfinder(Map& map);
    void handleEvent(sf::Event& e, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);

    int calculateHeuristicCost(HeuristicAlgorithm heurAlg, sf::Vector2i source, sf::Vector2i target);
    int calculateMovementCost(sf::Vector2i source, sf::Vector2i target);

private:
    Map& m_Map;

    const int m_CardinalMovementCost; //N, E, S, W
    const int m_IntercardinalMovementCost; //NE, SE, SW, NW

    sf::Vector2i m_SourceNodePosition;
    sf::Vector2i m_TargetNodePosition;

    sf::Clock m_MouseClickCoolDown;
    sf::Time m_MouseClickDelay;
};

#endif //PATHFINDER_HPP

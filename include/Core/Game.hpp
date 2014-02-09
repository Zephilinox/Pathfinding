#ifndef GAME_HPP
#define GAME_HPP

//STD
#include <iostream>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Map.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void handleEvent(sf::Event& e);
    void update(const sf::Time& delta);
    void display();

    void calculatePath();
    unsigned int calculateManhattanDistance(const sf::Vector2u& startPos, const sf::Vector2u& endPos);
    std::vector<sf::Vector2u> filterAdjacentFaces(std::vector<sf::Vector2u> adjacentFaces);

    sf::RenderWindow m_RenderWindow;
    sf::Clock m_FrameTimer;
    sf::Time m_TimeSinceLastUpdate;

    sf::Clock m_RunningTimer;
    unsigned int m_EventCalls;
    unsigned int m_UpdateCalls;
    unsigned int m_DisplayCalls;

    Map m_Map;

    sf::Color m_CurrentColor;
    bool m_LeftMouseClicked;
    bool m_RightMouseClicked;

    sf::Vector2u m_StartPos;
    sf::Vector2u m_TargetPos;
    std::vector<sf::Vector2u> m_OpenList;
    std::vector<sf::Vector2u> m_ClosedList;

    const sf::Time m_UPDATE_RATE;
};

#endif //GAME_HPP

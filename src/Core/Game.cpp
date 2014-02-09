#include "Core/Game.hpp"

Game::Game()
    : m_RenderWindow(sf::VideoMode(960,960), "Pathfinding")
    , m_EventCalls(0)
    , m_UpdateCalls(0)
    , m_DisplayCalls(0)
    , m_Map(sf::Vector2u(1024, 1024))
    , m_CurrentColor(sf::Color(127, 127, 127, 127))
    , m_LeftMouseClicked(false)
    , m_RightMouseClicked(false)
    , m_StartPos(1, 1)
    , m_TargetPos(13, 13)
    , m_UPDATE_RATE(sf::seconds(1.f / 60.f))
{
    m_Map.getSquare(m_StartPos).rs.setFillColor(sf::Color(0, 100, 250));
    m_Map.getSquare(m_TargetPos).rs.setFillColor(sf::Color(250, 50, 50));

    m_Map.getSquare(m_StartPos).heuristicCost.setString(m_Map.toString(calculateManhattanDistance(m_StartPos, m_TargetPos)));

    calculatePath();
}

void Game::run()
{
    m_RenderWindow.setVerticalSyncEnabled(true);

    while (m_RenderWindow.isOpen())
    {
        sf::Time durationOfLastFrame = m_FrameTimer.restart();
        m_TimeSinceLastUpdate += durationOfLastFrame;

        while (m_TimeSinceLastUpdate >= m_UPDATE_RATE)
        {
            m_TimeSinceLastUpdate -= m_UPDATE_RATE;

            sf::Event e;
            while (m_RenderWindow.pollEvent(e))
            {
                handleEvent(e);
            }

            update(m_UPDATE_RATE);
        }

        display();

        if (m_RunningTimer.getElapsedTime().asSeconds() >= 1.f)
        {
            m_RunningTimer.restart();

            std::cout << "\nDEBUG STATS\n";
            std::cout << "EventCalls: " << m_EventCalls << " per second\n";
            std::cout << "UpdateCalls: " << m_UpdateCalls  << " per second\n";
            std::cout << "DisplayCalls: " << m_DisplayCalls << " per second\n\n";
            m_EventCalls = 0;
            m_UpdateCalls = 0;
            m_DisplayCalls = 0;
        }
    }
}

void Game::handleEvent(sf::Event& e)
{
    m_EventCalls++;

    switch(e.type)
    {
        case sf::Event::Closed:
        {
            m_RenderWindow.close();
            break;
        }

        case sf::Event::MouseButtonPressed:
        {
            switch(e.mouseButton.button)
            {
                case sf::Mouse::Right:
                {
                    m_RightMouseClicked = true;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        case sf::Event::MouseButtonReleased:
        {
            switch(e.mouseButton.button)
            {
                case sf::Mouse::Left:
                case sf::Mouse::Right:
                {
                    m_CurrentColor = sf::Color(127, 127, 127, 127);
                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        default:
        {
            break;
        }
    }

    m_LeftMouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Game::update(const sf::Time& delta)
{
    m_UpdateCalls++;

    if (m_LeftMouseClicked &&
         sf::Mouse::getPosition().x >= 0 &&
         sf::Mouse::getPosition().x <= 1024 &&
         sf::Mouse::getPosition().y >= 0 &&
         sf::Mouse::getPosition().y <= 1024)
    {
        sf::Vector2u facePos = m_Map.getFacePos(sf::Vector2f(sf::Mouse::getPosition(m_RenderWindow)));
        sf::Color faceColor = m_Map.getSquare(facePos).rs.getFillColor();

        if (faceColor != sf::Color::Blue && faceColor != sf::Color::Red)
        {
            if (m_CurrentColor == sf::Color(127, 127, 127, 127))
            {
                if (faceColor == sf::Color::White)
                {
                    m_CurrentColor = sf::Color::Black;
                }
                else if (faceColor == sf::Color(60, 60, 60))
                {
                    m_CurrentColor = sf::Color::White;
                }
            }

            if (m_CurrentColor == sf::Color::White)
            {
                if (faceColor == sf::Color::Black)
                {
                    m_Map.getSquare(facePos).rs.setFillColor(sf::Color::White);
                }
            }
            else if (m_CurrentColor == sf::Color::Black)
            {
                if (faceColor == sf::Color::White)
                {
                    m_Map.getSquare(facePos).rs.setFillColor(sf::Color(60, 60, 60));
                }
            }
        }

        m_LeftMouseClicked = false;
    }
}

void Game::display()
{
    m_DisplayCalls++;

    m_RenderWindow.clear(sf::Color(40, 40, 40));
    m_RenderWindow.draw(m_Map);
    m_RenderWindow.display();
}

void Game::calculatePath()
{
    m_OpenList.push_back(m_StartPos);

    std::vector<sf::Vector2u> v = filterAdjacentFaces(m_Map.findAdjacentFaces(m_StartPos));

    for (auto pos : v)
    {
        Square& sqr = m_Map.getSquare(pos);
        sqr.parentSquarePos = m_StartPos;

        if (sqr.rs.getFillColor() != sf::Color::Red && sqr.rs.getFillColor() != sf::Color::Blue)
        {
            sqr.rs.setFillColor(sf::Color::Yellow);
        }

        if (pos.x != sqr.parentSquarePos.x && pos.y != sqr.parentSquarePos.y) //diagonal
        {
            sqr.movementCost.setString("14");
        }
        else
        {
            sqr.movementCost.setString("10");
        }

        sqr.heuristicCost.setString(m_Map.toString(calculateManhattanDistance(pos, m_TargetPos)));
        sqr.totalCost.setString(m_Map.toString(m_Map.fromString(sqr.heuristicCost.getString()) + m_Map.fromString(sqr.movementCost.getString())));

        m_OpenList.push_back(pos);
    }

    m_OpenList.erase(m_OpenList.begin());
    m_ClosedList.push_back(m_StartPos);


    //...

    m_OpenList.clear();
    m_ClosedList.clear();
}

unsigned int Game::calculateManhattanDistance(const sf::Vector2u& startPos, const sf::Vector2u& endPos)
{
    sf::Vector2i startPosI(startPos);
    sf::Vector2i endPosI(endPos);

    sf::Vector2i dist(startPosI.x - endPosI.x, startPosI.y - endPosI.y);

    return 10 * std::abs(dist.x + dist.y);
}

std::vector<sf::Vector2u> Game::filterAdjacentFaces(std::vector<sf::Vector2u> adjacentFaces)
{
    adjacentFaces.erase(std::remove_if(adjacentFaces.begin(), adjacentFaces.end(), [&] (sf::Vector2u const& pos)
    {
        return m_Map.getSquare(pos).rs.getFillColor() == sf::Color(40, 40, 40);
    }), adjacentFaces.end());

    std::cout << adjacentFaces.size() << "\n";

    return adjacentFaces;
}

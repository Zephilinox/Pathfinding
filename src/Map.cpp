#include "Map.hpp"

//STD
#include <sstream>

Map::Map(const sf::Vector2u& gridSize)
{
    arial.loadFromFile("arial.ttf");

    m_Grid.resize(gridSize.y / m_TILE_SIZE); //row-major ordering. top-to-bottom and then left-to-right

    for (auto& row : m_Grid)
    {
        row.resize(gridSize.x / m_TILE_SIZE); //create x amount of columns
    }

    std::cout << "Grid = (" << m_Grid.size() << ", " << m_Grid[0].size() << ")\n";

    sf::RectangleShape rs;
    rs.setSize(sf::Vector2f(m_TILE_SIZE, m_TILE_SIZE));
    rs.setFillColor(sf::Color::White);
    rs.setOutlineColor(sf::Color::Black);
    rs.setOutlineThickness(2.f);

    sf::Text baseText;
    baseText.setFont(arial);
    baseText.setColor(sf::Color::Black);
    baseText.setCharacterSize(16);
    baseText.setString("0");

    Square sqr;
    sqr.rs = rs;
    sqr.totalCost = baseText;
    sqr.movementCost = baseText;
    sqr.heuristicCost = baseText;

    for (unsigned int row = 0; row < m_Grid.size(); ++row)
    {
        for (unsigned int column = 0; column < m_Grid[row].size(); ++column)
        {
            sqr.rs.setPosition(column * m_TILE_SIZE, row * m_TILE_SIZE);
            sqr.movementCost.setPosition(column * m_TILE_SIZE, row * m_TILE_SIZE);
            sqr.heuristicCost.setPosition(column * m_TILE_SIZE, row * m_TILE_SIZE + (m_TILE_SIZE / 3.f));
            sqr.totalCost.setPosition(column * m_TILE_SIZE, row * m_TILE_SIZE + (m_TILE_SIZE / 1.5f));

            m_Grid[row][column] = sqr;
        }
    }
}

Square& Map::getSquare(const sf::Vector2u& facePos)
{
    return m_Grid.at(facePos.y).at(facePos.x);
}


sf::Vector2f Map::getFaceWorldPos(const sf::Vector2u& facePos)
{
    return sf::Vector2f(facePos.x * m_TILE_SIZE, facePos.y * m_TILE_SIZE);
}

sf::Vector2u Map::getFacePos(const sf::Vector2f& worldPos)
{
    return sf::Vector2u(worldPos.x / m_TILE_SIZE, worldPos.y / m_TILE_SIZE);
}

std::vector<sf::Vector2u> Map::findAdjacentFaces(const sf::Vector2u& facePos)
{
    std::vector<sf::Vector2u> adjacentFaces;

    bool farLeft = false;
    bool farRight = false;
    bool farTop = false;
    bool farBottom = false;

    if (facePos.x == 0) //Not last square on left-side of map
    {
        farLeft = true;
    }
    else if (facePos.x == m_Grid[0].size() - 1) //Not last square on right-side of map
    {
        farRight = true;
    }

    if (facePos.y == 0) //Not last square on top-side of map
    {
        farTop = true;
    }
    else if (facePos.y == m_Grid.size() - 1) //Not last square on bottom-side of map
    {
        farBottom = true;
    }

    if (!farTop && !farLeft)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x - 1, facePos.y - 1));
    }

    if (!farTop && !farRight)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x + 1, facePos.y - 1));
    }

    if (!farBottom && !farLeft)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x - 1, facePos.y + 1));
    }

    if (!farBottom && !farRight)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x + 1, facePos.y + 1));
    }

    if (!farTop)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x, facePos.y - 1));
    }

    if (!farBottom)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x,facePos.y + 1));
    }

    if (!farLeft)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x - 1, facePos.y));
    }

    if (!farRight)
    {
        adjacentFaces.push_back(sf::Vector2u(facePos.x + 1, facePos.y));
    }

    return adjacentFaces;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto row : m_Grid)
    {
        for (auto square : row) //column
        {
            target.draw(square.rs, states);

            if (square.totalCost.getString() != "0")
            {
                target.draw(square.totalCost, states);
            }

            if (square.movementCost.getString() != "0")
            {
                target.draw(square.movementCost, states);
            }

            if (square.heuristicCost.getString() != "0")
            {
                target.draw(square.heuristicCost, states);
            }
        }
    }
}

std::string Map::toString(unsigned int val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

unsigned int Map::fromString(const std::string& str)
{
    std::stringstream ss;
    ss << str;
    unsigned int ret;
    ss >> ret;
    return ret;
}

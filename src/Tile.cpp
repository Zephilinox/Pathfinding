#include "Tile.hpp"

//STD
#include <iostream>

//3RD

//SELF

Tile::Tile(sf::Vector2f pos):
m_ToggleColourDelay(sf::seconds(0.3f))
{
    m_Square.setPosition(pos);
    m_Square.setSize(sf::Vector2f(16, 16));
    m_Square.setOutlineThickness(1);
    m_Square.setOutlineColor(sf::Color::Black);
}

void Tile::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    switch (event.type)
    {
        default:
        {
            break;
        }
    }
}

void Tile::update(const float dt, sf::RenderWindow& window)
{
    sf::Vector2i mousePosTile(sf::Mouse::getPosition(window).x / 16, sf::Mouse::getPosition(window).y / 16);
    sf::Vector2i selfPosTile(m_Square.getPosition().x / 16, m_Square.getPosition().y / 16);

    if (mousePosTile == selfPosTile)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            toggleColour();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            m_Square.setFillColor(sf::Color::White);
        }
    }
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Square, states);
}

void Tile::toggleColour()
{
    if (m_ToggleColourCooldown.getElapsedTime().asSeconds() >= m_ToggleColourDelay.asSeconds())
    {
        m_ToggleColourCooldown.restart();

        if (m_Square.getFillColor() == sf::Color::White)
        {
            m_Square.setFillColor(sf::Color::Red);
        }
        else if (m_Square.getFillColor() == sf::Color::Red)
        {
            m_Square.setFillColor(sf::Color::Blue);
        }
        else if (m_Square.getFillColor() == sf::Color::Blue)
        {
            m_Square.setFillColor(sf::Color::White);
        }
    }
}

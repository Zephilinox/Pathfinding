#ifndef TILE_HPP
#define TILE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

class Tile : public sf::Drawable
{
public:
    Tile(sf::Vector2f pos);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void toggleColour();

    sf::RectangleShape m_Square;

    sf::Clock m_ToggleColourCooldown;
    sf::Time m_ToggleColourDelay;
};

#endif //TILE_HPP

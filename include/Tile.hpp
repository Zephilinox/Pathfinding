#ifndef TILE_HPP
#define TILE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Node.hpp"

enum TileState {Unknown, Empty, Source, Target, Wall, Path, CheckedPath};

class Tile : public sf::Drawable
{
public:
    Tile(sf::Vector2f pos);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setState(TileState state);
    TileState getState();

private:
    void updateColour();

    TileState m_State;

    sf::RectangleShape m_Square;
};

#endif //TILE_HPP

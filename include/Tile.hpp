#ifndef TILE_HPP
#define TILE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Node.hpp"

enum class TileState {Unknown, Empty, Wall};

class Tile : public sf::Drawable
{
public:
    Tile(sf::Vector2f pos);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setState(TileState state);
    TileState getState();

    Node& getNode();

    void reset();

private:
    void updateColour();

    TileState m_State;

    sf::RectangleShape m_Square;

    Node m_Node;
};

#endif //TILE_HPP

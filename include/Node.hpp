#ifndef NODE_HPP
#define NODE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "ZGE/ResourceManagement/Resource.hpp"
#include "ZGE/Utility.hpp"
#include "Constants.hpp"

enum class NodeState {Unknown, Source, Target, OpenList, ClosedList};

class Node : public sf::Drawable
{
public:
    Node(sf::Vector2f pos);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setState(NodeState state);
    NodeState getState();

    void setMovementCost(unsigned cost);
    unsigned getMovementCost();

    void setHeuristicCost(unsigned cost);
    unsigned getHeuristicCost();

    sf::Vector2f getPosition();

    void setParentNodePosition(sf::Vector2i pos);
    sf::Vector2i getParentNodePosition();

    void reset();

private:
    void updateColour();
    void updateFStringPosition();
    void updateGStringPosition();
    void updateHStringPosition();

    sf::Vector2i m_ParentNodePosition;

    NodeState m_State;

    sf::RectangleShape m_Square;

    zge::Resource<sf::Font> m_Font;

    sf::Text m_F;
    sf::Text m_G;
    sf::Text m_H;

    unsigned m_MovementCost;
    unsigned m_HeuristicCost;
};

#endif //NODE_HPP

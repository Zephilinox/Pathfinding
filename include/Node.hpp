#ifndef NODE_HPP
#define NODE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "ZGE/ResourceManagement/Resource.hpp"
#include "ZGE/Utility.hpp"
#include "Constants.hpp"

enum class NodeState {Unknown, Source, Target, Path, CheckedPath};

class Node : public sf::Drawable
{
public:
    Node(sf::Vector2f pos);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(const float dt, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setState(NodeState state);
    NodeState getState();

    void setMovementCost(int cost);
    int getMovementCost();

    void setHeuristicCost(int cost);
    int getHeuristicCost();

private:
    void updateColour();

    NodeState m_State;

    sf::RectangleShape m_Square;

    zge::Resource<sf::Font> m_Font;

    sf::Text m_F;
    sf::Text m_G;
    sf::Text m_H;

    int m_MovementCost;
    int m_HeuristicCost;
};

#endif //NODE_HPP

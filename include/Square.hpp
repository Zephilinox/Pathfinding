#ifndef SQUARE_HPP
#define SQUARE_HPP

//3RD
#include <SFML/Graphics.hpp>

struct Square
{
    sf::RectangleShape rs;

    sf::Text totalCost;
    sf::Text movementCost;
    sf::Text heuristicCost;

    sf::Vector2u parentSquarePos;
};

#endif // SQUARE_HPP

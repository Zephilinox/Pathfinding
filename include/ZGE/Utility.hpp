#ifndef UTILITY_HPP
#define UTILITY_HPP

//STD
#include <sstream>

//3RD
#include <SFML/Graphics.hpp>

//SELF

namespace zge
{

void drawLine(sf::RenderTarget& target, float x1, float y1, float x2, float y2, sf::Color c);

template<class T>
std::string toString(T var)
{
    std::stringstream ss;
    ss << var;
    return ss.str();
}

template<class T>
T fromString(std::string str)
{
    std::stringstream ss(str);
    T var;
    ss >> var;
    return var;
}


} //ZGE

#endif //UTILITY_HPP

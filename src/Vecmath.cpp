#include "Vecmath.hpp"

/* Includes - STL */
#include <cstdio>
#include <cmath>


void reassign(sf::Vector2f& v, float x, float y)
{
    v.x = x;
    v.y = y;
}

void reassign(sf::Vector2f& v, sf::Vector2f other)
{
    v.x = other.x;
    v.y = other.y;
}


float dot(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f norm(sf::Vector2f v)
{
    return v / mag(v);
}

float ang(sf::Vector2f v)
{
    return std::atan2(v.x, v.y);
}

float mag(sf::Vector2f v)
{
    return std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
}

const std::string to_str(sf::Vector2f v)
{
    char tmpbuf[256];
    sprintf(tmpbuf, "[%f, %f] \n", v.x, v.y);
    return tmpbuf;
}

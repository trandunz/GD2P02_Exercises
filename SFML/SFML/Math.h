#pragma once
#include "SFML/Graphics.hpp"

#define PI 3.14159265

inline sf::Vector3f Normalize(sf::Vector3f _v)
{
    float length = sqrtf((_v.x * _v.x) + (_v.y * _v.y) + (_v.z * _v.z));
    if (length != 0)
        return { _v.x / length, _v.y / length , _v.z / length };
    else
        return { _v.x, _v.y, _v.z };
}

inline float DotProduct(sf::Vector3f _v1, sf::Vector3f _v2)
{
    return ((_v1.x * _v2.x) + (_v1.y * _v2.y) + (_v1.z * _v2.z));
}

inline sf::Vector3f ProjectVectorOntoVector(sf::Vector3f _v1, sf::Vector3f _v2)
{
    float t = DotProduct(_v1, Normalize(_v2));
    return _v2 * t;
}

inline sf::Vector3f CrossProduct(sf::Vector3f _v1, sf::Vector3f _v2)
{
    return {((_v1.y * _v2.z) - (_v1.z * _v2.y)), ((_v1.z * _v2.x) - (_v1.x * _v2.z)), ((_v1.x * _v1.y) - (_v1.y * _v2.x))};
}


inline sf::Vector2f Normalize(sf::Vector2f _v)
{
    float length = sqrtf((_v.x * _v.x) + (_v.y * _v.y));
    if (length != 0)
        return { _v.x / length, _v.y / length};
    else
        return { _v.x, _v.y};
}

inline float GetAngleBetweenVectors(sf::Vector3f _v1, sf::Vector3f _v2)
{
    return acosf(DotProduct(Normalize(_v1), Normalize(_v2)));
}




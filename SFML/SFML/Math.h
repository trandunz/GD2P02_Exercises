#pragma once
#include "SFML/System/Vector3.hpp"
#include "SFML/System/Vector2.hpp"
#include <cstdlib>

#define PI 3.14159265359

inline sf::Vector2f Normalize(sf::Vector2f _v)
{
    float length = sqrtf((_v.x * _v.x) + (_v.y * _v.y));
    if (length != 0)
        return { _v.x / length, _v.y / length };
    else
        return { _v.x, _v.y };
}

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

inline float DotProduct(sf::Vector2f _v1, sf::Vector2f _v2)
{
    return ((_v1.x * _v2.x) + (_v1.y * _v2.y));
}

inline sf::Vector3f CrossProduct(sf::Vector3f _v1, sf::Vector3f _v2)
{
    return { ((_v1.y * _v2.z) - (_v1.z * _v2.y)), ((_v1.z * _v2.x) - (_v1.x * _v2.z)), ((_v1.x * _v1.y) - (_v1.y * _v2.x)) };
}

inline sf::Vector3f CrossProduct(sf::Vector2f _v1, sf::Vector3f _v2)
{
    return { ((_v1.y * _v2.z) - (1.0f * _v2.y)), ((1.0f * _v2.x) - (_v1.x * _v2.z)), ((_v1.x * _v1.y) - (_v1.y * _v2.x)) };
}

inline float Magnitude(sf::Vector3f _v)
{
    return sqrtf((_v.x * _v.x) + (_v.y * _v.y) + (_v.z * _v.z));
}

inline float Lerp(float _start, float _end, float _ratio)
{
    return _start * (1 - _ratio) + _end * _ratio;
}

inline sf::Vector2f Lerp(sf::Vector2f& _start, sf::Vector2f& _end, float _ratio) 
{
    return _start * _ratio + _end * (1.0f - _ratio);
}

inline sf::Vector3f ProjectVectorOntoVector(sf::Vector3f _v1, sf::Vector3f _v2)
{
    float t = DotProduct(_v1, Normalize(_v2));
    return _v2 * t;
}

inline float GetAngleBetweenVectors(sf::Vector3f _v1, sf::Vector3f _v2)
{
    return acosf(DotProduct(Normalize(_v1), Normalize(_v2)));
}

inline float LinePlaneIntersection(sf::Vector3f _planeNormal, sf::Vector3f _pointOnPlane, sf::Vector3f _lineStart, sf::Vector3f _lineEnd)
{
    sf::Vector3f d1 = _pointOnPlane;
    d1 -= _lineStart;
    sf::Vector3f d2 = _lineEnd;
    d2 -= _lineStart;
    return DotProduct(_planeNormal, d1) / DotProduct(_planeNormal, d2);
}
    


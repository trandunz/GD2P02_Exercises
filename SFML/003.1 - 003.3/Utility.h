#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <iostream>

#define PI 3.14159265359f

inline float Mag(sf::Vector2f _vector)
{
	return { sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y)) };
}

inline sf::Vector2f Normalize(sf::Vector2f _vector)
{
	return _vector / Mag(_vector);
}

inline float DotProduct(sf::Vector2f _v1, sf::Vector2f _v2)
{
	return ((_v1.x * _v2.x) + (_v1.y * _v2.y));
}

inline sf::Vector3f CrossProduct(sf::Vector3f _v1, sf::Vector3f _v2)
{
	sf::Vector3f result(((_v1.y * _v2.z) - (_v1.z * _v2.y)), ((_v1.z * _v2.x) - (_v1.x * _v2.z)), ((_v1.x * _v2.y) - (_v1.y * _v2.x)));
	return result;
}




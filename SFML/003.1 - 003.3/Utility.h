#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#define PI 3.14159265359f

inline float Mag(sf::Vector2f _vector)
{
	return { sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y)) };
}

inline sf::Vector2f Normalize(sf::Vector2f _vector)
{
	return _vector / Mag(_vector);
}




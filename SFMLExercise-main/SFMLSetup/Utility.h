#pragma once
#include "SFML/System/Vector2.hpp"
#include <cstdlib>

inline float Mag(sf::Vector2f _vector)
{
	return { sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y)) };
}

inline sf::Vector2f Normalize(sf::Vector2f _vector)
{
	return _vector / Mag(_vector);
}




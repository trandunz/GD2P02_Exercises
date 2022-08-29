#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Math.h"

inline void Print(sf::Vector2f _vec)
{
	std::cout << _vec.x << "|" << _vec.y << std::endl;
}

class Shape_Tool : public sf::Drawable
{
public:
	Shape_Tool();
	virtual ~Shape_Tool();

	virtual void Update();
	virtual void HandleMouseInput(sf::Event& _event, sf::RenderWindow& _renderWindow);
	virtual void ResetShape();
	virtual sf::VertexArray GetVertices() const;
	sf::Vector3f GetNormal();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_Vertices;
};


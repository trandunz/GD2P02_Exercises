#pragma once
#include "Utility.h"

class Mesh : public sf::Drawable
{
public:
	Mesh();
	Mesh(std::vector<sf::Vertex> _vertices);
	Mesh(int _sideCount);
	~Mesh();

	bool TrianglePointCollision(sf::Vector2f _point);
	void SetPosition(sf::Vector2f _position);

	void Scale(float _scale);
	void Move(sf::Vector2f _amount);

	bool CollideWithWindowBounds(sf::Vector2u _windowSize);
	
	sf::Vector2f GetCentre();

	sf::VertexArray m_VertexArray{};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


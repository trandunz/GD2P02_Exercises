#pragma once
#include "Utility.h"

class Mesh : public sf::Drawable
{
public:
	Mesh();
	Mesh(std::vector<sf::Vertex> _vertices);
	~Mesh();

	bool TrianglePointCollision(sf::Vector2f _point);

	void SetPosition(sf::Vector2f _position);
	void Scale(float _scale);

	sf::Vector2f GetCentre();

	sf::VertexArray m_VertexArray{};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


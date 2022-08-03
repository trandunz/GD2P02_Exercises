#pragma once
#include "Object.h"

class LiquidShape : public sf::Drawable
{
public:
	LiquidShape(sf::Vector2f _position, sf::Vector2f _size);
	virtual ~LiquidShape();

	virtual bool CheckForCollisions(std::vector<Object*>& _objects);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void ApplyFriction(Object& _object);

	sf::RectangleShape* m_Mesh = nullptr;
};


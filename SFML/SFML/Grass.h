#pragma once
#include "Segment.h"

class Grass : public sf::Drawable
{
public:
	Grass();
	Grass(unsigned _numberOfSegments, float _degmentLength, sf::Vector2f _position);
	~Grass();
	
	void Update(float _dt);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Segment*> m_Segments{};
};


#pragma once
#include "IKSegment.h"

class Worm : public sf::Drawable
{
public:
	Worm();
	Worm(sf::Vector2f _position, unsigned _numberOfSegments, float _segmentLength);
	~Worm();

	void Update(float _dt, sf::Vector2f _mousePos = { 400,400 });
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f m_StartPos{};
	std::vector<IKSegment*> m_Segments{};
};


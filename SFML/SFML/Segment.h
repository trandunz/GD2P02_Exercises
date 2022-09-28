#pragma once
#include "Utility.h"

class Segment : public sf::Drawable
{
public:
	Segment();
	Segment(Segment* _segment, sf::Vector2f _aPos, float _length, float _localRadians, float _t = 0.0f);
	Segment(Segment* _segment, float _length, float _localRadians, float _t = 0.0f);
	~Segment();

	void Update(float _dt);
	void Wiggle(float _dt);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f CalculatePositionB();

	Segment* m_ChildSegment{ nullptr };

	sf::Vector2f m_A{};
	sf::Vector2f m_B{};

	float m_Length{};
	float m_Radians{};
	float m_LocalRadians{};

	float m_T{};

	sf::VertexArray m_VertexArray{sf::PrimitiveType::Lines};

public:
	sf::Vector2f GetAPos();
	sf::Vector2f GetBPos();
};


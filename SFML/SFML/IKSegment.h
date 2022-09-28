#pragma once
#include "Utility.h"

class IKSegment : public sf::Drawable
{
public:
	IKSegment(IKSegment* _child, float _length);
	IKSegment(IKSegment* _child, sf::Vector2f _position, float _length);
	~IKSegment();

	void Follow(float _dt, sf::Vector2f _target = {});
	void Update(float _dt);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f CalculatePositionB();

	IKSegment* m_ChildSegment{ nullptr };

	sf::Vector2f m_A{};
	sf::Vector2f m_B{};

	float m_Length{};
	float m_Radians{};

	sf::VertexArray m_VertexArray{ sf::PrimitiveType::Lines };
};


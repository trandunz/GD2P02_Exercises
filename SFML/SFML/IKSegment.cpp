#include "IKSegment.h"
#include "Math.h"

IKSegment::IKSegment(IKSegment* _child, float _length)
{
	m_Length = _length;
	m_ChildSegment = _child;

	m_VertexArray.append({ {}, sf::Color::Cyan });
	m_VertexArray.append({ {}, sf::Color::Cyan });
}

IKSegment::IKSegment(IKSegment* _child, sf::Vector2f _position, float _length)
{
	m_Length = _length;
	m_A = _position;
	m_ChildSegment = _child;

	m_VertexArray.append({ {}, sf::Color::Cyan });
	m_VertexArray.append({ {}, sf::Color::Cyan });
}

IKSegment::~IKSegment()
{
	m_ChildSegment = nullptr;
}

void IKSegment::Follow(float _dt, sf::Vector2f _target)
{
	sf::Vector2f direction = _target - m_A;
	m_Radians = atan2f(direction.y, direction.x);
	direction = -Normalize(direction) * m_Length;
	m_A = _target + direction;

	if (m_ChildSegment)
	{
		m_ChildSegment->Follow(_dt, m_A);
	}
}

void IKSegment::Update(float _dt)
{
	m_B = m_A + CalculatePositionB();

	m_VertexArray[0].position = m_A;
	m_VertexArray[1].position = m_B;

	if (m_ChildSegment)
	{
		m_ChildSegment->Update(_dt);
	}
}

void IKSegment::UpdatePositonB(float _dt)
{
	m_B = m_A + CalculatePositionB();

	m_VertexArray[0].position = m_A;
	m_VertexArray[1].position = m_B;
}

sf::Vector2f IKSegment::GetA()
{
	return m_A;
}

void IKSegment::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_VertexArray);

	if (m_ChildSegment)
	{
		target.draw(*m_ChildSegment);
	}
}

sf::Vector2f IKSegment::CalculatePositionB()
{
	float dy{ m_Length * sinf(m_Radians) };
	float dx{ m_Length * cosf(m_Radians) };
	return { dx, dy };
}

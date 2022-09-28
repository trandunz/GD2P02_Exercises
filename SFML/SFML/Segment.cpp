#include "Segment.h"

Segment::Segment()
{
}

Segment::Segment(Segment* _segment, sf::Vector2f _aPos, float _length, float _localRadians, float _t)
{
	m_A = _aPos;
	m_Length = _length;
	m_Radians = _localRadians;
	m_LocalRadians = _localRadians;
	m_ChildSegment = _segment;
	m_T = _t;

	m_VertexArray.append({ {}, sf::Color::Green });
	m_VertexArray.append({ {}, sf::Color::Green });
}

Segment::Segment(Segment* _segment, float _length, float _localRadians, float _t)
{
	m_Length = _length;
	m_Radians = _localRadians;
	m_LocalRadians = _localRadians;
	m_ChildSegment = _segment;
	m_T = _t;

	m_VertexArray.append({ {}, sf::Color::Green });
	m_VertexArray.append({ {}, sf::Color::Green });
}

Segment::~Segment()
{
	m_ChildSegment = nullptr;
}

void Segment::Update(float _dt)
{
	m_B = m_A + CalculatePositionB();

	if (m_ChildSegment)
	{
		m_ChildSegment->m_A = m_B;
		m_ChildSegment->m_Radians = m_Radians + m_LocalRadians;
		m_ChildSegment->Update(_dt);
	}

	m_VertexArray[0].position = m_A;
	m_VertexArray[1].position = m_B;
}

void Segment::Wiggle(float _dt)
{
	float wiggleSpeed{ 8 };
	float wiggleStrength{ 0.5f };

	m_LocalRadians = wiggleStrength * sinf(m_T);
	m_T += wiggleSpeed * _dt;

	m_Radians = -1.57f + m_LocalRadians;

	if (m_ChildSegment)
	{
		m_ChildSegment->Wiggle(_dt);
	}
}

void Segment::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_VertexArray);

	if (m_ChildSegment)
		target.draw(*m_ChildSegment);
}

sf::Vector2f Segment::CalculatePositionB()
{
	float dy{ m_Length * sinf(m_Radians) };
	float dx{ m_Length * cosf(m_Radians) };
	return { dx, dy };
}

sf::Vector2f Segment::GetAPos()
{
	return m_A;
}

sf::Vector2f Segment::GetBPos()
{
	return m_B;
}

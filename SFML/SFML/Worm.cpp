#include "Worm.h"

Worm::Worm()
{

}

Worm::Worm(sf::Vector2f _position, unsigned _numberOfSegments, float _segmentLength)
{
	if (_numberOfSegments > 0)
	{
		m_Segments.emplace_back(new IKSegment(nullptr, _position, _segmentLength));

		for (unsigned i = 1; i < _numberOfSegments - 1; i++)
		{
			m_Segments.emplace_back(new IKSegment(m_Segments[i - 1], _segmentLength));
		}

		m_Segments.emplace_back(new IKSegment(m_Segments[_numberOfSegments - 2], _segmentLength));
	}
}

Worm::~Worm()
{
	CleanupVector(m_Segments);
}

void Worm::Update(float _dt, sf::Vector2f _mousePos)
{
	if (m_Segments.size() > 0)
	{
		m_Segments[m_Segments.size() - 1]->Follow(_dt, _mousePos);
		m_Segments[m_Segments.size() - 1]->Update(_dt);
	}
}

void Worm::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Segments.size() > 0)
	{
		target.draw(*m_Segments[m_Segments.size() - 1]);
	}
}

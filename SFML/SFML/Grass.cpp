#include "Grass.h"
#include "Math.h"

Grass::Grass()
{
}

Grass::Grass(unsigned _numberOfSegments, float _degmentLength, sf::Vector2f _position)
{
	float t{};

	if (_numberOfSegments > 0)
	{
		m_Segments.emplace_back(new Segment(nullptr, _degmentLength, 0, t));

		for (unsigned i = 1; i < _numberOfSegments - 1; i++)
		{
			_degmentLength *= 1.5f;
			m_Segments.emplace_back(new Segment(m_Segments[i - 1], _degmentLength, 0, t));
		}

		m_Segments.emplace_back(new Segment(m_Segments[_numberOfSegments - 2], _position, _degmentLength, 0, t));
	}
}

Grass::~Grass()
{
	CleanupVector(m_Segments);
}

void Grass::Update(float _dt)
{
	if (m_Segments.size() > 0)
	{
		m_Segments[m_Segments.size() - 1]->Wiggle(_dt);
		m_Segments[m_Segments.size() - 1]->Update(_dt);
	}
}

void Grass::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Segments.size() > 0)
	{
		target.draw(*m_Segments[m_Segments.size() - 1]);
	}
}

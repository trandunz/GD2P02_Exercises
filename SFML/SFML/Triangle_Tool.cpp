#include "Triangle_Tool.h"

Triangle_Tool::Triangle_Tool()
{
	m_Vertices.setPrimitiveType(sf::Triangles);
	m_IntersectArea.setPrimitiveType(sf::Lines);
}

void Triangle_Tool::Update()
{
	
}

void Triangle_Tool::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Vertices);
	target.draw(m_IntersectArea);
}

void Triangle_Tool::HandleMouseInput(sf::Event& _event, sf::RenderWindow& _renderWindow)
{
	if (_event.type == sf::Event::MouseButtonPressed
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = _renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_renderWindow));
		m_Vertices.append({ mousePos, sf::Color::Blue });
		if (m_Vertices.getVertexCount() > 3)
		{
			m_Vertices.resize(3);
		}
	}
}

bool Triangle_Tool::CheckForLineIntersection(Shape_Tool& _line)
{
	if (m_Vertices.getVertexCount() < 3 || _line.GetVertices().getVertexCount() < 2)
	{
		m_IntersectArea.clear();
		m_IntersectArea.resize(0);
		return false;
	}

	float result = DotProduct(_line.GetNormal(), _line.GetVertices()[0].position - m_Vertices[0].position) / DotProduct(_line.GetNormal(), m_Vertices[1].position - m_Vertices[0].position);
	float result2 = DotProduct(_line.GetNormal(), _line.GetVertices()[0].position - m_Vertices[1].position) / DotProduct(_line.GetNormal(), m_Vertices[2].position - m_Vertices[1].position);
	float result3 = DotProduct(_line.GetNormal(), _line.GetVertices()[0].position - m_Vertices[2].position) / DotProduct(_line.GetNormal(), m_Vertices[0].position - m_Vertices[2].position);
	bool intersecting = false;
	if (result >= 0 && result <= 1)
	{
		m_IntersectArea.append({ GetPointOnLine(_line.GetVertices(), result), sf::Color::Green });
		intersecting = true;
	}
	if (result2 >= 0 && result2 <= 1)
	{
		m_IntersectArea.append({ GetPointOnLine(_line.GetVertices(), result2), sf::Color::Green });
		intersecting = true;
	}
	if (result3 >= 0 && result3 <= 1)
	{
		m_IntersectArea.append({ GetPointOnLine(_line.GetVertices(), result3), sf::Color::Green });
		intersecting = true;
	}	
	return intersecting;
}

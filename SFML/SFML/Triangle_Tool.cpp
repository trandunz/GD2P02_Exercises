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
	for (auto& point : m_IntersectionPoints)
	{
		target.draw(point);
	}
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
	
	m_IntersectionPoints.clear();

	sf::Vector3f lineStart = { GetVertices()[0].position.x, GetVertices()[0].position.y, 0.0f };
	sf::Vector3f lineEnd = { GetVertices()[1].position.x, GetVertices()[1].position.y, 0.0f };
	sf::Vector3f pointOnPlane = { _line.GetVertices()[0].position.x, _line.GetVertices()[0].position.y,0.0f };
	float result = LinePlaneIntersection(_line.GetNormal(), pointOnPlane, lineStart, lineEnd);
	lineStart = { GetVertices()[1].position.x, GetVertices()[1].position.y, 0.0f };
	lineEnd = { GetVertices()[2].position.x, GetVertices()[2].position.y, 0.0f };
	float result2 = LinePlaneIntersection(_line.GetNormal(), pointOnPlane, lineStart, lineEnd);
	lineStart = { GetVertices()[2].position.x, GetVertices()[2].position.y, 0.0f };
	lineEnd = { GetVertices()[0].position.x, GetVertices()[0].position.y, 0.0f };
	float result3 = LinePlaneIntersection(_line.GetNormal(), pointOnPlane, lineStart, lineEnd);

	bool intersecting = false;
	if (result >= 0 && result <= 1)
	{
		lineStart = { GetVertices()[0].position.x, GetVertices()[0].position.y, 0.0f };
		lineEnd = { GetVertices()[1].position.x, GetVertices()[1].position.y, 0.0f };
		sf::Vector3f intersectionpoint;
		intersectionpoint = lineStart + (result * (lineEnd - lineStart));
		sf::CircleShape pointMesh(1.0f);
		pointMesh.setOrigin({ 5.0f,5.0f });
		pointMesh.setFillColor(sf::Color::Green);
		pointMesh.setPosition({ intersectionpoint.x, intersectionpoint.y });
		m_IntersectionPoints.push_back(pointMesh);

		intersecting = true;
	}
	if (result2 >= 0 && result2 <= 1)
	{
		lineStart = { GetVertices()[1].position.x, GetVertices()[1].position.y, 0.0f };
		lineEnd = { GetVertices()[2].position.x, GetVertices()[2].position.y, 0.0f };
		sf::Vector3f intersectionpoint;
		intersectionpoint = lineStart + (result2 * (lineEnd - lineStart));
		sf::CircleShape pointMesh(1.0f);
		pointMesh.setOrigin({ 5.0f,5.0f });
		pointMesh.setFillColor(sf::Color::Green);
		pointMesh.setPosition({ intersectionpoint.x, intersectionpoint.y });
		m_IntersectionPoints.push_back(pointMesh);

		intersecting = true;
	}
	if (result3 >= 0 && result3 <= 1)
	{
		lineStart = { GetVertices()[2].position.x, GetVertices()[2].position.y, 0.0f };
		lineEnd = { GetVertices()[0].position.x, GetVertices()[0].position.y, 0.0f };
		sf::Vector3f intersectionpoint;
		intersectionpoint = lineStart + (result3 * (lineEnd - lineStart));
		sf::CircleShape pointMesh(1.0f);
		pointMesh.setOrigin({ 5.0f,5.0f });
		pointMesh.setFillColor(sf::Color::Green);
		pointMesh.setPosition({ intersectionpoint.x, intersectionpoint.y });
		m_IntersectionPoints.push_back(pointMesh);

		intersecting = true;
	}
	return intersecting;
}

#include "Triangle_Tool.h"

Triangle_Tool::Triangle_Tool()
{
	m_Vertices.setPrimitiveType(sf::Triangles);
	m_IntersectArea.setPrimitiveType(sf::Triangles);
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
		if (m_Vertices.getVertexCount() < 3)
		{
			sf::Vector2f mousePos = _renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_renderWindow));
			m_Vertices.append({ mousePos, sf::Color::Blue });
		}
	}
}

bool Triangle_Tool::CheckForLineIntersection(Shape_Tool& _plane)
{
	if (m_Vertices.getVertexCount() < 3 || _plane.GetVertices().getVertexCount() < 2)
	{
		return false;
	}

	m_IntersectionPoints.clear();
	m_IntersectionPoints.resize(0);

	m_IntersectArea.clear();
	m_IntersectArea.resize(0);

	bool intersecting = false;

	sf::Vector3f pointOnPlane = { _plane.GetVertices()[0].position.x, _plane.GetVertices()[0].position.y,0.0f };

	sf::Vector3f lineStart = { GetVertices()[0].position.x, GetVertices()[0].position.y, 0.0f };
	sf::Vector3f lineEnd = { GetVertices()[1].position.x, GetVertices()[1].position.y, 0.0f };
	float result = LinePlaneIntersection(_plane.GetNormal(), pointOnPlane, lineStart, lineEnd);
	if (result >= 0 && result <= 1)
	{
		sf::Vector3f intersectionpoint3d = lineStart + (result * (lineEnd - lineStart));
		sf::Vector2f intersectionpoint2d{ intersectionpoint3d.x, intersectionpoint3d.y };
		sf::CircleShape pointMesh(2.5f);
		pointMesh.setOrigin({ pointMesh.getRadius(),pointMesh.getRadius() });
		pointMesh.setFillColor(sf::Color::Magenta);
		pointMesh.setPosition(intersectionpoint2d);
		m_IntersectionPoints.emplace_back(pointMesh);

		FindClosestPoint(_plane, intersectionpoint2d);

		intersecting = true;
	}

	lineStart = { GetVertices()[1].position.x, GetVertices()[1].position.y, 0.0f };
	lineEnd = { GetVertices()[2].position.x, GetVertices()[2].position.y, 0.0f };
	result = LinePlaneIntersection(_plane.GetNormal(), pointOnPlane, lineStart, lineEnd);
	if (result >= 0 && result <= 1)
	{
		sf::Vector3f intersectionpoint3d = lineStart + (result * (lineEnd - lineStart));
		sf::Vector2f intersectionpoint2d{ intersectionpoint3d.x, intersectionpoint3d.y };
		sf::CircleShape pointMesh(2.5f);
		pointMesh.setOrigin({ pointMesh.getRadius(),pointMesh.getRadius() });
		pointMesh.setFillColor(sf::Color::Magenta);
		pointMesh.setPosition(intersectionpoint2d);
		m_IntersectionPoints.emplace_back(pointMesh);

		FindClosestPoint(_plane, intersectionpoint2d);

		intersecting = true;
	}

	lineStart = { GetVertices()[2].position.x, GetVertices()[2].position.y, 0.0f };
	lineEnd = { GetVertices()[0].position.x, GetVertices()[0].position.y, 0.0f };
	result = LinePlaneIntersection(_plane.GetNormal(), pointOnPlane, lineStart, lineEnd);
	if (result >= 0 && result <= 1)
	{
		sf::Vector3f intersectionpoint3d = lineStart + (result * (lineEnd - lineStart));
		sf::Vector2f intersectionpoint2d{ intersectionpoint3d.x, intersectionpoint3d.y };
		sf::CircleShape pointMesh(2.5f);
		pointMesh.setOrigin({ pointMesh.getRadius(),pointMesh.getRadius() });
		pointMesh.setFillColor(sf::Color::Magenta);
		pointMesh.setPosition(intersectionpoint2d);
		m_IntersectionPoints.emplace_back(pointMesh);

		FindClosestPoint(_plane, intersectionpoint2d);

		intersecting = true;
	}

	for (auto& point : m_IntersectionPoints)
	{
		m_IntersectArea.append({ point.getPosition(), sf::Color::Green });
	}
	
	return intersecting;
}

void Triangle_Tool::ClearIntersectionPoints()
{
	m_IntersectionPoints.clear();
	m_IntersectionPoints.resize(0);

	m_IntersectArea.clear();
	m_IntersectArea.resize(0);
}

void Triangle_Tool::FindClosestPoint(Shape_Tool& _plane, sf::Vector2f& intersectionpoint2d)
{
	if (m_IntersectionPoints.size() < 3)
	{
		sf::CircleShape closestPointMesh(2.5f);
		closestPointMesh.setOrigin({ closestPointMesh.getRadius(),closestPointMesh.getRadius() });
		closestPointMesh.setFillColor(sf::Color::Magenta);
		std::vector<sf::CircleShape> pointsInBack{};
		std::vector<sf::CircleShape> pointsInFront{};
		sf::Vector2f planeNormal2D = { _plane.GetNormal().x, _plane.GetNormal().y };
		for (int i = 0; i < m_Vertices.getVertexCount(); i++)
		{
			if (DotProduct(intersectionpoint2d - m_Vertices[i].position, planeNormal2D) > 0)
			{
				closestPointMesh.setPosition(m_Vertices[i].position);
				pointsInFront.emplace_back(closestPointMesh);
			}
			else
			{
				closestPointMesh.setPosition(m_Vertices[i].position);
				pointsInBack.emplace_back(closestPointMesh);
			}
		}

		if (pointsInBack.size() <= pointsInFront.size())
		{
			if (pointsInBack.size() > 0)
			{
				m_IntersectionPoints.emplace_back(pointsInBack.back());
			}
		}
		else
		{
			if (pointsInFront.size() > 0)
			{
				m_IntersectionPoints.emplace_back(pointsInFront.back());
			}
		}
	}
}

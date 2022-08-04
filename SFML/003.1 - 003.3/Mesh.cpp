#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<sf::Vertex> _vertices)
{
	m_VertexArray.setPrimitiveType(sf::Triangles);

	for (auto& vertice : _vertices)
	{
		m_VertexArray.append(vertice);
	}
}

Mesh::~Mesh()
{
	m_VertexArray.clear();
	m_VertexArray.resize(0);
}

bool Mesh::TrianglePointCollision(sf::Vector2f _point)
{
	sf::Vector2f vector1 = Normalize(m_VertexArray[0].position - _point);
	sf::Vector2f vector2 = Normalize(m_VertexArray[1].position - _point);
	sf::Vector2f vector3 = Normalize(m_VertexArray[2].position - _point);

	float dot1 = acos(DotProduct(vector1, vector2));
	float dot2 = acos(DotProduct(vector2, vector3));
	float dot3 = acos(DotProduct(vector3, vector1));

	float sum = dot1 + dot2 + dot3;
	if (sum <= (2 * PI) + 0.01f
		&& sum >= (2 * PI) - 0.01f)
	{
		return true;
	}

	return false;
}

void Mesh::SetPosition(sf::Vector2f _position)
{
	for (int i = 0; i < m_VertexArray.getVertexCount(); i++)
	{
		m_VertexArray[i].position += _position;
	}
}

void Mesh::Scale(float _scale)
{
	for (int i = 0; i < m_VertexArray.getVertexCount(); i++)
	{
		m_VertexArray[i].position *= _scale;
	}
}

sf::Vector2f Mesh::GetCentre()
{
	sf::Vector2f centre{};
	for (int i = 0; i < m_VertexArray.getVertexCount(); i++)
	{
		centre += m_VertexArray[i].position;
	}
	return centre / (float)m_VertexArray.getVertexCount();
}

void Mesh::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_VertexArray);
}

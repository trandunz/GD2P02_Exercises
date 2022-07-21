#include "Shape_Tool.h"

Shape_Tool::Shape_Tool()
{
	m_Vertices.setPrimitiveType(sf::Lines);
}

Shape_Tool::~Shape_Tool()
{
	ResetShape();
}

void Shape_Tool::Update()
{
}

void Shape_Tool::HandleMouseInput(sf::Event& _event, sf::RenderWindow& _renderWindow)
{
	if (_event.type == sf::Event::MouseButtonPressed
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = _renderWindow.mapPixelToCoords(sf::Mouse::getPosition(_renderWindow));
		m_Vertices.append({ mousePos, sf::Color::Red});
		if (m_Vertices.getVertexCount() > 2)
		{
			m_Vertices.resize(2);
		}
	}
}

void Shape_Tool::ResetShape()
{
	m_Vertices.clear();
	m_Vertices.resize(0);
}

sf::VertexArray Shape_Tool::GetVertices() const
{
	return m_Vertices;
}

sf::Vector2f Shape_Tool::GetNormal()
{
	sf::Vector3f normal = CrossProduct(Normalize(m_Vertices[1].position - m_Vertices[0].position), Normalize({ m_Vertices[0].position.x, m_Vertices[0].position.y, -1 }));
	return { normal.x, normal.y};
}

void Shape_Tool::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Vertices);
}

#include "Object.h"

Object::Object()
{
}

Object::Object(sf::Vector2f _startPos, float _mass)
{
	m_Mesh = new sf::CircleShape(50.0f);
	m_Mesh->setFillColor(sf::Color::Green);
	m_Mesh->setOutlineColor(sf::Color::Red);
	m_Mesh->setOutlineThickness(10.0f);
	m_Mesh->setOrigin(m_Mesh->getRadius(), m_Mesh->getRadius());

	m_Mass = _mass;
	m_Mesh->setPosition(_startPos);
}

Object::~Object()
{
	m_CustomMesh = nullptr;

	if (m_Mesh)
		delete m_Mesh;
	m_Mesh = nullptr;

	if (m_RenderWindow)
		m_RenderWindow = nullptr;
}

void Object::SetMesh(Mesh* _mesh)
{
	m_CustomMesh = _mesh;
}

void Object::SetRenderWindow(sf::RenderWindow& _renderWindow)
{
	m_RenderWindow = &_renderWindow;
}

void Object::UpdatePhysics(float _dt)
{
	if (m_Mesh)
	{
		m_Velocity += m_Acceleration * _dt;
		m_Mesh->move(m_Velocity * _dt);
		m_Acceleration = {};
	}
}

void Object::Update(float _dt)
{
	ApplyFriction(0.1f);
	CollideWithWindowBounds();
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Mesh)
		target.draw(*m_Mesh);

	if (m_CustomMesh)
		target.draw(*m_CustomMesh);
}

void Object::ApplyGravity(float _strength)
{
	m_GravityStrength = _strength; ;
	ApplyForce({ 0, _strength * m_Mass });
}

void Object::ApplyForce(sf::Vector2f _force)
{
	m_Acceleration += _force / m_Mass;
}

void Object::ApplyFriction(float _coefficient)
{
	if (m_RenderWindow && m_Mesh)
	{
		if (m_Mesh->getPosition().y + m_Mesh->getRadius() >= m_RenderWindow->getSize().y
			|| m_Mesh->getPosition().x - m_Mesh->getRadius() <= 0
			|| m_Mesh->getPosition().y - m_Mesh->getRadius() <= 0
			|| m_Mesh->getPosition().x + m_Mesh->getRadius() >= m_RenderWindow->getSize().x)
		{
			sf::Vector2f negativeUnitVelocity = Normalize(m_Velocity) * -1.0f;
			float normalForce = m_Mass * m_GravityStrength;
			ApplyForce(negativeUnitVelocity * normalForce * _coefficient);
		}
	}
}

void Object::CollideWithWindowBounds()
{
	if (m_RenderWindow && m_Mesh)
	{
		if (m_Mesh->getPosition().y + m_Mesh->getRadius() >= m_RenderWindow->getSize().y)
		{
			m_Mesh->setPosition(m_Mesh->getPosition().x, m_RenderWindow->getSize().y - m_Mesh->getRadius());
			m_Velocity.y *= -1;
		}
		if (m_Mesh->getPosition().y - m_Mesh->getRadius() <= 0)
		{
			m_Mesh->setPosition(m_Mesh->getPosition().x, m_Mesh->getRadius());
			m_Velocity.y *= -1;
		}
		if (m_Mesh->getPosition().x + m_Mesh->getRadius() >= m_RenderWindow->getSize().x)
		{
			m_Mesh->setPosition(m_RenderWindow->getSize().x - m_Mesh->getRadius(), m_Mesh->getPosition().y);
			m_Velocity.x *= -1;
		}
		if (m_Mesh->getPosition().x - m_Mesh->getRadius() <= 0)
		{
			m_Mesh->setPosition(m_Mesh->getRadius(), m_Mesh->getPosition().y);
			m_Velocity.x *= -1;
		}
	}
}

sf::FloatRect Object::GetGlobalBounds()
{
	if (m_Mesh == nullptr)
		return sf::FloatRect();

	return m_Mesh->getGlobalBounds();
}

sf::Vector2f Object::GetVelocity() const
{
	return m_Velocity;
}

float Object::GetReferenceArea() const
{
	if (m_Mesh == nullptr)
		return 0.0f;

	float scaledRadius = m_Mesh->getRadius() / 1000.0f;
	return PI * (scaledRadius * scaledRadius);
}

void Object::SetPosition(sf::Vector2f _position)
{
	if (m_CustomMesh)
	{ 
		for (int i = 0; i < m_CustomMesh->m_VertexArray.getVertexCount(); i++)
		{
			m_CustomMesh->m_VertexArray[i].position += _position;
		}
	}
}

void Object::Scale(float _scale)
{
	if (m_CustomMesh)
	{
		for (int i = 0; i < m_CustomMesh->m_VertexArray.getVertexCount(); i++)
		{
			m_CustomMesh->m_VertexArray[i].position *= _scale;
		}
	}
}

sf::Vector2f Object::GetPosition()
{
	if (m_Mesh)
		return m_Mesh->getPosition();
	else
		return {};
}

#include "ConvexPolygon.h"

ConvexPolygon::ConvexPolygon()
{
}

ConvexPolygon::ConvexPolygon(sf::Vector2f _startPos, float _mass)
{
	m_Mesh = new Mesh(3);

	m_Mass = _mass;
	m_Mesh->SetPosition(_startPos);
}

ConvexPolygon::ConvexPolygon(int _sides, sf::Vector2f _startPos, float _mass)
{
	m_Mesh = new Mesh(_sides);

	m_Mass = _mass;
	m_Mesh->SetPosition(_startPos);
}

ConvexPolygon::~ConvexPolygon()
{
	if (m_Mesh)
		delete m_Mesh;
	m_Mesh = nullptr;

	if (m_RenderWindow)
		m_RenderWindow = nullptr;
}

void ConvexPolygon::SetRenderWindow(sf::RenderWindow& _renderWindow)
{
	m_RenderWindow = &_renderWindow;
}

void ConvexPolygon::UpdatePhysics(float _dt)
{
	if (m_Mesh)
	{
		m_Velocity += m_Acceleration * _dt;
		m_Mesh->Move(m_Velocity * _dt);
		m_Acceleration = {};
	}
}

void ConvexPolygon::Update(float _dt)
{
	//ApplyFriction(0.1f);
	CollideWithWindowBounds();
}

void ConvexPolygon::ApplyGravity(float _strength)
{
	m_GravityStrength = _strength; ;
	ApplyForce({ 0, _strength * m_Mass });
}

void ConvexPolygon::ApplyForce(sf::Vector2f _force)
{
	m_Acceleration += _force / m_Mass;
}

void ConvexPolygon::ApplyFriction(float _coefficient)
{
	if (m_RenderWindow && m_Mesh)
	{
		if (m_Mesh->CollideWithWindowBounds(m_RenderWindow->getSize()))
		{
			sf::Vector2f negativeUnitVelocity = Normalize(m_Velocity) * -1.0f;
			float normalForce = m_Mass * m_GravityStrength;
			ApplyForce(negativeUnitVelocity * normalForce * _coefficient);
		}
	}
}

void ConvexPolygon::CollideWithWindowBounds()
{
	if (m_RenderWindow && m_Mesh)
	{
		for (int i = 0; i < m_Mesh->m_VertexArray.getVertexCount(); i++)
		{
			if (m_Mesh->m_VertexArray[i].position.y >= m_RenderWindow->getSize().y)
			{
				float collisionDepth = m_RenderWindow->getSize().y - m_Mesh->m_VertexArray[i].position.y;
				m_Mesh->Move({ 0 , collisionDepth });
				m_Velocity.y *= -1;
			}
			if (m_Mesh->m_VertexArray[i].position.y <= 0)
			{
				std::cout << m_Mesh->m_VertexArray[i].position.y << std::endl;
				float collisionDepth = 0 - m_Mesh->m_VertexArray[i].position.y;
				m_Mesh->Move({ 0 , collisionDepth });
				m_Velocity.y *= -1;
			}
			if (m_Mesh->m_VertexArray[i].position.x >= m_RenderWindow->getSize().x)
			{
				float collisionDepth = m_RenderWindow->getSize().x - m_Mesh->m_VertexArray[i].position.x;
				m_Mesh->Move({ collisionDepth , 0 });
				m_Velocity.x *= -1;
			}
			if (m_Mesh->m_VertexArray[i].position.x <= 0)
			{
				float collisionDepth = 0 + m_Mesh->m_VertexArray[i].position.x;
				m_Mesh->Move({ -collisionDepth , 0 });
				m_Velocity.x *= -1;
			}
		}
	}
}

sf::Vector2f& ConvexPolygon::GetVelocity()
{
	return m_Velocity;
}

void ConvexPolygon::SetPosition(sf::Vector2f _position)
{
	if (m_Mesh)
	{
		m_Mesh->SetPosition(_position);
	}
}

void ConvexPolygon::Scale(float _scale)
{
	if (m_Mesh)
	{
		m_Mesh->Scale(_scale);
	}
}

void ConvexPolygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Mesh)
		target.draw(*m_Mesh);
}

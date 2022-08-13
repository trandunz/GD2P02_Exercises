#include "CapsuleObject.h"

CapsuleObject::CapsuleObject(sf::Vector2f _startPos, sf::Vector2f _endPos, float _radius, float _mass, sf::Color _color)
{
	m_Radius = _radius;

	Top = sf::CircleShape(_radius);
	Bot = sf::CircleShape(_radius);
	Mid = sf::RectangleShape({ _radius , _radius });

	Top.setFillColor(_color);
	Bot.setFillColor(_color);
	Mid.setFillColor(_color);

	Mid.setSize({ _radius * 2, Mag(_endPos - _startPos) });

	Top.setOrigin(Top.getLocalBounds().width / 2, Top.getLocalBounds().height / 2);
	Bot.setOrigin(Bot.getLocalBounds().width / 2, Bot.getLocalBounds().height / 2);
	Mid.setOrigin(Mid.getLocalBounds().width / 2, Mid.getLocalBounds().height / 2);

	Top.setPosition(_startPos);
	Bot.setPosition(_endPos);
	Mid.setPosition(_startPos + ((_endPos - _startPos) / 2.0f));

	
	m_Mass = _mass;
}

CapsuleObject::~CapsuleObject()
{
	if (m_RenderWindow)
		m_RenderWindow = nullptr;
}

void CapsuleObject::SetRenderWindow(sf::RenderWindow& _renderWindow)
{
	m_RenderWindow = &_renderWindow;
}

void CapsuleObject::UpdatePhysics(float _dt)
{
	m_Velocity += m_Acceleration * _dt;
	Top.move(m_Velocity * _dt);
	Bot.move(m_Velocity * _dt);
	Mid.move(m_Velocity * _dt);
	m_Acceleration = {};
}

void CapsuleObject::Update(float _dt)
{
	CollideWithWindowBounds();
}

void CapsuleObject::ApplyGravity(float _strength)
{
	m_GravityStrength = _strength; ;
	ApplyForce({ 0, _strength * m_Mass });
}

void CapsuleObject::ApplyForce(sf::Vector2f _force)
{
	m_Acceleration += _force / m_Mass;
}

void CapsuleObject::CollideWithWindowBounds()
{
	CollideCircleWithBounds(Top);
	CollideCircleWithBounds(Bot);
}

bool CapsuleObject::CheckCollision(CapsuleObject& _capsule)
{
	sf::Vector2f orientation = Normalize(_capsule.Bot.getPosition() - _capsule.Top.getPosition());
	sf::Vector2f vectorToPoint = Bot.getPosition() - _capsule.Top.getPosition();
	float t = DotProduct(vectorToPoint, orientation);
	sf::Vector2f projectedPoint = _capsule.Top.getPosition() + (-orientation * t);

	float distance = Mag(Top.getPosition() - projectedPoint);
	if (distance <= _capsule.m_Radius + m_Radius)
	{
		m_Velocity.y *= -1;
		//ApplyForce(Normalize(vectorToPoint) * 10000.0f);
		std::cout << "Collision!" << std::endl;
		return true;
	}
	
	return false;
}

void CapsuleObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(Top);
	target.draw(Bot);
	target.draw(Mid);
}

void CapsuleObject::CollideCircleWithBounds(sf::CircleShape& _circle)
{
	if (_circle.getPosition().y + _circle.getRadius() >= m_RenderWindow->getSize().y)
	{
		float collisionDepth = m_RenderWindow->getSize().y - (_circle.getPosition().y + _circle.getRadius());

		OffsetShapes({ 0,collisionDepth });
		m_Velocity.y *= -1;
	}
	if (_circle.getPosition().y - _circle.getRadius() <= 0)
	{
		float collisionDepth = 0 + (_circle.getPosition().y - _circle.getRadius());

		OffsetShapes({ 0,collisionDepth });
		m_Velocity.y *= -1;
	}
	if (_circle.getPosition().x + _circle.getRadius() >= m_RenderWindow->getSize().x)
	{
		float collisionDepth = m_RenderWindow->getSize().x - _circle.getPosition().x + _circle.getRadius();

		OffsetShapes({ collisionDepth,0 });
		m_Velocity.x *= -1;
	}
	if (_circle.getPosition().x - _circle.getRadius() <= 0)
	{
		float collisionDepth = 0 + _circle.getPosition().x - _circle.getRadius();
		OffsetShapes({ collisionDepth,0 });
		m_Velocity.x *= -1;
	}
}

void CapsuleObject::OffsetOtherShapes(sf::Shape& _thisShape, sf::Vector2f _amount)
{
	if (&Top != &_thisShape)
	{
		Top.move(_amount);
	}
	if (&Bot != &_thisShape)
	{
		Bot.move(_amount);
	}
	if (&Mid != &_thisShape)
	{
		Mid.move(_amount);
	}
}

void CapsuleObject::OffsetShapes(sf::Vector2f _amount)
{
	Mid.move(_amount);
	Bot.move(_amount);
	Top.move(_amount);
}

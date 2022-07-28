#pragma once
#include "Utility.h"

class Movers : public sf::Drawable
{
public:
	Movers(sf::Vector2f _startPos, float _mass);
	virtual ~Movers();

	void SetRenderWindow(sf::RenderWindow& _renderWindow);
	virtual void UpdatePhysics(float _dt);
	virtual void Update(float _dt);

	virtual void ApplyGravity(float _strength);
	virtual void ApplyForce(sf::Vector2f _force);
	virtual void ApplyFriction(float _coefficient);
	virtual void CollideWithWindowBounds();
	virtual sf::FloatRect GetGlobalBounds();

	sf::Vector2f GetVelocity() const;
	virtual float GetReferenceArea() const;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::CircleShape* m_Mesh = nullptr;
	float m_Mass = 0.0f;
	float m_GravityStrength{};
	sf::Vector2f m_Velocity{};
	sf::Vector2f m_Acceleration{};
};


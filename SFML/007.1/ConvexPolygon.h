#pragma once
#include "Mesh.h"

class ConvexPolygon : public sf::Drawable
{
public:
	ConvexPolygon();
	ConvexPolygon(sf::Vector2f _startPos, float _mass);
	ConvexPolygon(int _sides, sf::Vector2f _startPos, float _mass);
	virtual ~ConvexPolygon();

	void SetRenderWindow(sf::RenderWindow& _renderWindow);
	virtual void UpdatePhysics(float _dt);
	virtual void Update(float _dt);

	virtual void ApplyGravity(float _strength);
	virtual void ApplyForce(sf::Vector2f _force);
	virtual void ApplyFriction(float _coefficient);
	virtual void CollideWithWindowBounds();

	sf::Vector2f& GetVelocity();

	void SetPosition(sf::Vector2f _position);
	void Scale(float _scale);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::RenderWindow* m_RenderWindow = nullptr;

	Mesh* m_Mesh = nullptr;
	float m_Mass = 0.0f;
	float m_GravityStrength{};
	sf::Vector2f m_Velocity{};
	sf::Vector2f m_Acceleration{};
};


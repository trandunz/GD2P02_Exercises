#pragma once
#include "Object.h"

struct SprintJointDef
{
	Object* BodyA = nullptr;
	Object* BodyB = nullptr;
	float Length = 50.0f;
	float Constant = 1.0f;
	float Damping = 0.1f;
};

class SpringJoint : public sf::Drawable
{
public:
	SpringJoint(SprintJointDef& _def);
	~SpringJoint();

	void PhysicsUpdate(float _dt);
	void Update(float _dt);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f GetSpringForce(Object& _refrenceObject, Object& _otherObject);

	sf::VertexArray m_Vertexarray{};
	SprintJointDef m_JointDef{};
};


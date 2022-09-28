#include "SpringJoint.h"
#include "Math.h"

SpringJoint::SpringJoint(SprintJointDef& _def)
{
	m_JointDef = _def;
	m_Vertexarray.setPrimitiveType(sf::Lines);
	m_Vertexarray.append({ {m_JointDef.BodyA->GetPosition()},sf::Color::White });
	m_Vertexarray.append({ {m_JointDef.BodyB->GetPosition()},sf::Color::White });
}

SpringJoint::~SpringJoint()
{
	m_JointDef.BodyA = nullptr;
	m_JointDef.BodyB = nullptr;
	m_Vertexarray.clear();
	m_Vertexarray.resize(0);
}

void SpringJoint::PhysicsUpdate(float _dt)
{
	m_JointDef.BodyA->ApplyForce(GetSpringForce(*m_JointDef.BodyA, *m_JointDef.BodyB) / _dt);
	m_JointDef.BodyB->ApplyForce(GetSpringForce(*m_JointDef.BodyB, *m_JointDef.BodyA) / _dt);
	m_JointDef.BodyB->GetVelocity() = m_JointDef.BodyB->GetVelocity() * 0.99f;
	m_JointDef.BodyA->GetVelocity() = m_JointDef.BodyA->GetVelocity() * 0.99f;
	//m_JointDef.BodyB->ApplyForce(-m_JointDef.BodyB->GetVelocity() * m_JointDef.Damping / _dt);

	//m_JointDef.BodyA->ApplyForce(-m_JointDef.BodyA->GetVelocity() * m_JointDef.Damping / _dt);
}

void SpringJoint::Update(float _dt)
{
	m_Vertexarray[0].position = m_JointDef.BodyA->GetPosition();
	m_Vertexarray[1].position = m_JointDef.BodyB->GetPosition();
}

void SpringJoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Vertexarray);
}

sf::Vector2f SpringJoint::GetSpringForce(Object& _refrenceObject, Object& _otherObject)
{
	sf::Vector2f force{ _refrenceObject.GetPosition() - _otherObject.GetPosition() };
	float x = Magnitude(force) - m_JointDef.Length;
	force = Normalize(force) * (-m_JointDef.Constant * x);
	return force;
}

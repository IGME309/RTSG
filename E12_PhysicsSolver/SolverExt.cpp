#include "SolverExt.h"

//  Solver
SolverExt::SolverExt(void) : Solver() { } //call parent constructor

//Methods
void SolverExt::ApplyFriction(float a_fFriction)
{
	if (a_fFriction < 0.01f)
		a_fFriction = 0.01f;

	m_v3Velocity *= 1.0f - a_fFriction;

	//if velocity is really small make it zero
	if (glm::length(m_v3Velocity) < 0.01f)
		m_v3Velocity = ZERO_V3;
}
void SolverExt::ApplyForce(vector3 a_v3Force)
{
	//check minimum mass
	if (m_fMass < 0.01f)
		m_fMass = 0.01f;
	//f = m * a -> a = f / m
	m_v3Acceleration += a_v3Force / m_fMass;
}
vector3 CalculateMaxVelocity(vector3 a_v3Velocity, float maxVelocity)
{
	if (glm::length(a_v3Velocity) > maxVelocity)
	{
		a_v3Velocity = glm::normalize(a_v3Velocity);
		a_v3Velocity *= maxVelocity;
	}
	return a_v3Velocity;
}
vector3 RoundSmallVelocity(vector3 a_v3Velocity, float minVelocity = 0.01f)
{
	if (glm::length(a_v3Velocity) < minVelocity)
	{
		a_v3Velocity = ZERO_V3;
	}
	return a_v3Velocity;
}
void SolverExt::Update(void)
{
	ApplyForce(m_v3Gravity);

	m_v3Velocity += m_v3Acceleration;

	float fMaxVelocity = 5.0f;
	m_v3Velocity = CalculateMaxVelocity(m_v3Velocity, fMaxVelocity);

	ApplyFriction(0.1f);
	m_v3Velocity = RoundSmallVelocity(m_v3Velocity, 0.028f);

	m_v3Position += m_v3Velocity;

	if (m_v3Position.y <= 0)
	{
		m_v3Position.y = 0;
		m_v3Velocity.y = 0;
	}

	m_v3Acceleration = ZERO_V3;
}
void SolverExt::ResolveCollision(Solver* a_pOther)
{
	float fMagThis = glm::length(m_v3Velocity);
	float fMagOther = glm::length(m_v3Velocity);

	if (fMagThis > 0.015f || fMagOther > 0.015f)
	{
		//a_pOther->ApplyForce(GetVelocity());
		ApplyForce(-m_v3Velocity);
		a_pOther->ApplyForce(m_v3Velocity);
	}
	else
	{
		vector3 v3Direction = m_v3Position - a_pOther->GetPosition();
		if (glm::length(v3Direction) != 0)
			v3Direction = glm::normalize(v3Direction);
		v3Direction *= m_fSeparationStrength;
		ApplyForce(v3Direction);
		a_pOther->ApplyForce(-v3Direction);
	}
}
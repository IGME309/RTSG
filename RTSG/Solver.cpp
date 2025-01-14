#include "RTSG\Physics\Solver.h"
using namespace RTSG;
//  Solver
void Solver::Init(void)
{
	m_v3Acceleration = ZERO_V3;
	m_v3Position = ZERO_V3;
	m_v3Velocity = ZERO_V3;
	m_fMass = 1.0f;
}
void Solver::Swap(Solver& other)
{
	std::swap(m_v3Acceleration, other.m_v3Acceleration);
	std::swap(m_v3Velocity, other.m_v3Velocity);
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_fMass, other.m_fMass);
}
void Solver::Release(void) {/*nothing to deallocate*/ }
//The big 3
Solver::Solver(void) { Init(); }
Solver::Solver(Solver const& other)
{
	m_v3Acceleration = other.m_v3Acceleration;
	m_v3Velocity = other.m_v3Velocity;
	m_v3Position = other.m_v3Position;
	m_fMass = other.m_fMass;
}
Solver& Solver::operator=(Solver const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Solver temp(other);
		Swap(temp);
	}
	return *this;
}
Solver::~Solver() { Release(); }

//Accessors
void Solver::SetPosition(vector3 a_v3Position) { m_v3Position = a_v3Position; }
vector3 Solver::GetPosition(void) { return m_v3Position; }

void Solver::SetSize(vector3 a_v3Size) { m_v3Size = a_v3Size; }
vector3 Solver::GetSize(void) { return m_v3Size; }

void Solver::SetVelocity(vector3 a_v3Velocity) { m_v3Velocity = a_v3Velocity; }
vector3 Solver::GetVelocity(void) { return m_v3Velocity; }

void Solver::SetMass(float a_fMass) { m_fMass = a_fMass; }
float Solver::GetMass(void) { return m_fMass; }

void Solver::SetSeparationStrength(float a_fForce) { m_fSeparationStrength = a_fForce; }
float Solver::GetSeparationStrength(void) { return m_fSeparationStrength; }

void Solver::SetGravity(vector3 a_v3Gravity) { m_v3Gravity = a_v3Gravity; }
vector3 Solver::GetGravity(void) { return m_v3Gravity; }

//Methods
void Solver::ApplyFriction(float a_fFriction)
{
	if (a_fFriction < 0.01f)
		a_fFriction = 0.01f;

	m_v3Velocity *= 1.0f - a_fFriction;

	//if velocity is really small make it zero
	if (glm::length(m_v3Velocity) < 0.01f)
		m_v3Velocity = ZERO_V3;
}
void Solver::ApplyForce(vector3 a_v3Force)
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
void Solver::Update(void)
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
void Solver::ResolveCollision(Solver* a_pOther)
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
		vector3 v3Direction = m_v3Position - a_pOther->m_v3Position;
		if (glm::length(v3Direction) != 0)
			v3Direction = glm::normalize(v3Direction);
		v3Direction *= m_fSeparationStrength;
		ApplyForce(v3Direction);
		a_pOther->ApplyForce(-v3Direction);
	}
}
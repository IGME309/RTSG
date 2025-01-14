#include "RigidBody.h"

//Accessors
bool RigidBody::GetVisible(void) { return m_bVisible; }
float RigidBody::GetRadius(void) { return m_fRadius; }
vector3 RigidBody::GetColor(void) { return m_v3Color; }
void RigidBody::SetColor(vector3 a_v3Color) { m_v3Color = a_v3Color; }
vector3 RigidBody::GetCenterLocal(void) { return m_v3Center; }
vector3 RigidBody::GetMinLocal(void) { return m_v3MinL; }
vector3 RigidBody::GetMaxLocal(void) { return m_v3MaxL; }
vector3 RigidBody::GetCenterGlobal(void){	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 RigidBody::GetMinGlobal(void) { return m_v3MinG; }
vector3 RigidBody::GetMaxGlobal(void) { return m_v3MaxG; }
vector3 RigidBody::GetHalfWidth(void) { return m_v3HalfWidth; }
matrix4 RigidBody::GetModelMatrix(void) { return m_m4ToWorld; }
void RigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix) { m_m4ToWorld = a_m4ModelMatrix; }
//Allocation
void RigidBody::Init(void)
{
	m_pMeshMngr = RTSG::ModelManager::GetInstance();
	m_bVisible = true;

	m_fRadius = 0.0f;

	m_v3Color = C_WHITE;

	m_v3Center = ZERO_V3;
	m_v3MinL = ZERO_V3;
	m_v3MaxL = ZERO_V3;

	m_v3MinG = ZERO_V3;
	m_v3MaxG = ZERO_V3;

	m_v3HalfWidth = ZERO_V3;

	m_m4ToWorld = IDENTITY_M4;
}
void RigidBody::Swap(RigidBody& other)
{
	std::swap(m_pMeshMngr , other.m_pMeshMngr);
	std::swap(m_bVisible , other.m_bVisible);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_v3Color , other.m_v3Color);

	std::swap(m_v3Center , other.m_v3Center);
	std::swap(m_v3MinL , other.m_v3MinL);
	std::swap(m_v3MaxL , other.m_v3MaxL);

	std::swap(m_v3MinG , other.m_v3MinG);
	std::swap(m_v3MaxG , other.m_v3MaxG);

	std::swap(m_v3HalfWidth , other.m_v3HalfWidth);

	std::swap(m_m4ToWorld , other.m_m4ToWorld);
}
void RigidBody::Release(void)
{
	m_pMeshMngr = nullptr;
}
//The big 3
RigidBody::RigidBody()
{
	Init();
}
RigidBody::RigidBody(RigidBody const& other)
{
	m_pMeshMngr = other.m_pMeshMngr;
	m_bVisible = other.m_bVisible;

	m_fRadius = other.m_fRadius;

	m_v3Color = other.m_v3Color;

	m_v3Center = other.m_v3Center;
	m_v3MinL = other.m_v3MinL;
	m_v3MaxL = other.m_v3MaxL;

	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;

	m_m4ToWorld = other.m_m4ToWorld;
}
RigidBody& RigidBody::operator=(RigidBody const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		RigidBody temp(other);
		Swap(temp);
	}
	return *this;
}
RigidBody::~RigidBody(){Release();};

//--- Non Standard Singleton Methods
void RigidBody::AddToRenderList(void)
{
	if (!m_bVisible)
		return;
}
bool RigidBody::IsColliding(RigidBody* const other)
{
	return false;
}

//--- Set values for the temp functions
void RigidBody::SetCenterGlobal(vector3 a_v3Input)
{
	m_v3Center = m_m4ToWorld * vector4(a_v3Input, 1.0f);
}
void RigidBody::SetRadius(float a_fInput)
{
	m_fRadius = a_fInput;
}
void RigidBody::SetHalfWidth(vector3 a_v3Input)
{
	m_v3HalfWidth = a_v3Input;
}
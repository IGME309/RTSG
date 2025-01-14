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
RigidBody::RigidBody(std::vector<vector3> a_pointList)
{
	//Initialize the values
	Init();
	//Count the points in the point List
	uint uSize = a_pointList.size();
	//If the size is small return there is nothing to do here
	if (uSize < 1)
		return;
	//initialize min and Max to the first point, that way it will
	//always belong to the model (0,0,0) might not be part of the model
	m_v3MinL = m_v3MaxL = a_pointList[0];

	//find the min and max for each coordinate component
	for (uint i = 1; i < uSize; i++)
	{
		m_v3MinL.x = glm::min(m_v3MinL.x, a_pointList[i].x);
		m_v3MinL.y = glm::min(m_v3MinL.y, a_pointList[i].y);
		m_v3MinL.z = glm::min(m_v3MinL.z, a_pointList[i].z);

		m_v3MaxL.x = glm::max(m_v3MaxL.x, a_pointList[i].x);
		m_v3MaxL.y = glm::max(m_v3MaxL.y, a_pointList[i].y);
		m_v3MaxL.z = glm::max(m_v3MaxL.z, a_pointList[i].z);
	}
	// Average ONLY TWO POINTS to find the center (max and min)
	m_v3Center = (m_v3MaxL + m_v3MinL) / 2.0f;
	// Get the size and then divide it by 2 to find the halfwidth (or half size)
	m_v3HalfWidth = (m_v3MaxL - m_v3MinL) / 2.0f;
	// find the radius by getting the distance between center and max (or min)
	m_fRadius = glm::distance(m_v3Center, m_v3MaxL);
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
	
	//Display the sphere
	//Set in therms of the world coordinate system, center and scale
	matrix4 m4Transform = m_m4ToWorld * glm::translate(m_v3Center)
		* glm::scale(vector3(m_fRadius));
	m_pMeshMngr->AddWireSphereToRenderList(m4Transform, m_v3Color);

	//Display the Cube (AABB)
	//Transform will be the same as the sphere except for the size (half size)
	m4Transform = m_m4ToWorld * glm::translate(m_v3Center);
	m4Transform = m4Transform * glm::scale(m_v3HalfWidth * 2.0f);
	m_pMeshMngr->AddWireCubeToRenderList(m4Transform, C_RED);
}
bool RigidBody::IsColliding(RigidBody* const other)
{
	//this will never collide with anything unless coded
	return false;
}

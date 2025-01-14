#include "RigidBody.h"
bool RigidBody::IsColliding(RigidBody* const other)
{
	//check if the models are colliding, first assume they are colliding...
	bool bReturn = true;
	//Unless they are not!
	//TODO: Check if they are not colliding if at least
	//one of the following 6 conditions are true
	//This is to the Left of Other
	//This to the Right of Other
	//This Below Other
	//This Above Other
	//This Behind of Other
	//This In front of Other
	return bReturn;
}
void RigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix)
{
	//set the model matrix
	m_m4ToWorld = a_m4ModelMatrix;

	//Calculate the vectors in global space
	//TODO: Globalize MinL and MaxL and store them in MinG and MaxG
	//Globalize the center
	m_v3CenterG = m_m4ToWorld * vector4(m_v3Center, 1.0f);
}
//Accessors
float RigidBody::GetRadius(void) { return m_fRadius; }
void RigidBody::SetColorAABB(vector3 a_v3Color) { m_v3ColorAABB = a_v3Color; }
void RigidBody::SetColorBS(vector3 a_v3Color) { m_v3ColorBS = a_v3Color; }
vector3 RigidBody::GetCenterLocal(void) { return m_v3Center; }
vector3 RigidBody::GetMinLocal(void) { return m_v3MinL; }
vector3 RigidBody::GetMaxLocal(void) { return m_v3MaxL; }
vector3 RigidBody::GetCenterGlobal(void){	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 RigidBody::GetMinGlobal(void) { return m_v3MinG; }
vector3 RigidBody::GetMaxGlobal(void) { return m_v3MaxG; }
vector3 RigidBody::GetHalfWidth(void) { return m_v3HalfWidth; }
matrix4 RigidBody::GetModelMatrix(void) { return m_m4ToWorld; }

//Allocation
void RigidBody::Init(void)
{
	m_pMeshMngr = RTSG::ModelManager::GetInstance();
	m_bVisibleAABB = true;
	m_bVisibleBS = false;

	m_fRadius = 0.0f;

	m_v3ColorAABB = C_WHITE;
	m_v3ColorBS = C_WHITE;

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
	std::swap(m_bVisibleAABB , other.m_bVisibleAABB);
	std::swap(m_bVisibleBS, other.m_bVisibleBS);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_v3ColorAABB , other.m_v3ColorAABB);
	std::swap(m_v3ColorBS, other.m_v3ColorBS);

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
	m_bVisibleAABB = other.m_bVisibleAABB;
	m_bVisibleBS = other.m_bVisibleBS;

	m_fRadius = other.m_fRadius;

	m_v3ColorAABB = other.m_v3ColorAABB;
	m_v3ColorBS = other.m_v3ColorBS;

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
	matrix4 m4Transform;
	//Display the sphere
	//Set in therms of the world coordinate system, center and scale
	if (m_bVisibleBS)
	{
		m4Transform = m_m4ToWorld * glm::translate(m_v3Center)
			* glm::scale(vector3(m_fRadius));
		m_pMeshMngr->AddWireSphereToRenderList(m4Transform, m_v3ColorBS);
	}
	//Display the Cube (AABB)
	//Transform will be the same as the sphere except for the size (half size)
	if (m_bVisibleAABB)
	{
		m4Transform = m_m4ToWorld * glm::translate(m_v3Center)
			* glm::scale(m_v3HalfWidth * 2.0f);
		m_pMeshMngr->AddWireCubeToRenderList(m4Transform, m_v3ColorAABB);
	}
}


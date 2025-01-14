#include "RTSG\Physics\RigidBody.h"
using namespace RTSG;
//Allocation
void RigidBody::Init(void)
{
	m_pModelMngr = ModelManager::GetInstance();
	m_bVisibleBS = false;
	m_bVisibleOBB = true;
	m_bVisibleARBB = false;

	m_fRadius = 0.0f;

	m_v3CenterL = ZERO_V3;
	m_v3CenterG = ZERO_V3;
	m_v3MinL = ZERO_V3;
	m_v3MaxL = ZERO_V3;

	m_v3MinG = ZERO_V3;
	m_v3MaxG = ZERO_V3;

	m_v3HalfWidth = ZERO_V3;
	m_v3ARBBSize = ZERO_V3;

	m_m4ToWorld = IDENTITY_M4;

	m_uCollidingCount = 0;
	m_CollidingArray = nullptr;
}
void RigidBody::Swap(RigidBody& other)
{
	std::swap(m_pModelMngr, other.m_pModelMngr);
	std::swap(m_bVisibleBS, other.m_bVisibleBS);
	std::swap(m_bVisibleOBB, other.m_bVisibleOBB);
	std::swap(m_bVisibleARBB, other.m_bVisibleARBB);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_v3CenterL, other.m_v3CenterL);
	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinL, other.m_v3MinL);
	std::swap(m_v3MaxL, other.m_v3MaxL);

	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3ARBBSize, other.m_v3ARBBSize);

	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_uCollidingCount, other.m_uCollidingCount);
	std::swap(m_CollidingArray, other.m_CollidingArray);
}
void RigidBody::Release(void)
{
	m_pModelMngr = nullptr;
	ClearCollidingList();
}
//Accessors
bool RigidBody::GetVisibleBS(void) { return m_bVisibleBS; }
void RigidBody::SetVisibleBS(bool a_bVisible) { m_bVisibleBS = a_bVisible; }
bool RigidBody::GetVisibleOBB(void) { return m_bVisibleOBB; }
void RigidBody::SetVisibleOBB(bool a_bVisible) { m_bVisibleOBB = a_bVisible; }
bool RigidBody::GetVisibleARBB(void) { return m_bVisibleARBB; }
void RigidBody::SetVisibleARBB(bool a_bVisible) { m_bVisibleARBB = a_bVisible; }
float RigidBody::GetRadius(void) { return m_fRadius; }
vector3 RigidBody::GetCenterLocal(void) { return m_v3CenterL; }
vector3 RigidBody::GetMinLocal(void) { return m_v3MinL; }
vector3 RigidBody::GetMaxLocal(void) { return m_v3MaxL; }
vector3 RigidBody::GetCenterGlobal(void){ return m_v3CenterG; }
vector3 RigidBody::GetMinGlobal(void) { return m_v3MinG; }
vector3 RigidBody::GetMaxGlobal(void) { return m_v3MaxG; }
vector3 RigidBody::GetHalfWidth(void) { return m_v3HalfWidth; }
matrix4 RigidBody::GetModelMatrix(void) { return m_m4ToWorld; }
RigidBody::PRigidBody* RigidBody::GetColliderArray(void) { return m_CollidingArray; }
uint RigidBody::GetCollidingCount(void) { return m_uCollidingCount; }
void RigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix)
{
	//to save some calculations if the model matrix is the same there is nothing to do here
	if (a_m4ModelMatrix == m_m4ToWorld)
		return;

	//Assign the model matrix
	m_m4ToWorld = a_m4ModelMatrix;

	m_v3CenterG = vector3(m_m4ToWorld * vector4(m_v3CenterL, 1.0f));

	//Calculate the 8 corners of the cube
	vector3 v3Corner[8];
	//Back square
	v3Corner[0] = m_v3MinL;
	v3Corner[1] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z);
	v3Corner[2] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MinL.z);
	v3Corner[3] = vector3(m_v3MaxL.x, m_v3MaxL.y, m_v3MinL.z);

	//Front square
	v3Corner[4] = vector3(m_v3MinL.x, m_v3MinL.y, m_v3MaxL.z);
	v3Corner[5] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MaxL.z);
	v3Corner[6] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MaxL.z);
	v3Corner[7] = m_v3MaxL;

	//Place them in world space
	for (uint uIndex = 0; uIndex < 8; ++uIndex)
	{
		v3Corner[uIndex] = vector3(m_m4ToWorld * vector4(v3Corner[uIndex], 1.0f));
	}

	//Identify the max and min as the first corner
	m_v3MaxG = m_v3MinG = v3Corner[0];

	//get the new max and min for the global box
	for (uint i = 1; i < 8; ++i)
	{
		if (m_v3MaxG.x < v3Corner[i].x) m_v3MaxG.x = v3Corner[i].x;
		else if (m_v3MinG.x > v3Corner[i].x) m_v3MinG.x = v3Corner[i].x;

		if (m_v3MaxG.y < v3Corner[i].y) m_v3MaxG.y = v3Corner[i].y;
		else if (m_v3MinG.y > v3Corner[i].y) m_v3MinG.y = v3Corner[i].y;

		if (m_v3MaxG.z < v3Corner[i].z) m_v3MaxG.z = v3Corner[i].z;
		else if (m_v3MinG.z > v3Corner[i].z) m_v3MinG.z = v3Corner[i].z;
	}

	//we calculate the distance between min and max vectors
	m_v3ARBBSize = m_v3MaxG - m_v3MinG;
}
//The big 3
RigidBody::RigidBody(std::vector<vector3> a_pointList)
{
	Init();
	//Count the points of the incoming list
	uint uVertexCount = a_pointList.size();

	//If there are none just return, we have no information to create the BS from
	if (uVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3MaxL = m_v3MinL = a_pointList[0];

	//Get the max and min out of the list
	for (uint i = 1; i < uVertexCount; ++i)
	{
		if (m_v3MaxL.x < a_pointList[i].x) m_v3MaxL.x = a_pointList[i].x;
		else if (m_v3MinL.x > a_pointList[i].x) m_v3MinL.x = a_pointList[i].x;

		if (m_v3MaxL.y < a_pointList[i].y) m_v3MaxL.y = a_pointList[i].y;
		else if (m_v3MinL.y > a_pointList[i].y) m_v3MinL.y = a_pointList[i].y;

		if (m_v3MaxL.z < a_pointList[i].z) m_v3MaxL.z = a_pointList[i].z;
		else if (m_v3MinL.z > a_pointList[i].z) m_v3MinL.z = a_pointList[i].z;
	}

	//with model matrix being the identity, local and global are the same
	m_v3MinG = m_v3MinL;
	m_v3MaxG = m_v3MaxL;

	//with the max and the min we calculate the center
	m_v3CenterG = m_v3CenterL = (m_v3MaxL + m_v3MinL) / 2.0f;

	//we calculate the distance between min and max vectors
	m_v3HalfWidth = (m_v3MaxL - m_v3MinL) / 2.0f;

	//Get the distance between the center and either the min or the max
	m_fRadius = glm::distance(m_v3CenterL, m_v3MinL);
}
RigidBody::RigidBody(RigidBody const& other)
{
	m_pModelMngr = other.m_pModelMngr;

	m_bVisibleBS = other.m_bVisibleBS;
	m_bVisibleOBB = other.m_bVisibleOBB;
	m_bVisibleARBB = other.m_bVisibleARBB;

	m_fRadius = other.m_fRadius;

	m_v3CenterL = other.m_v3CenterL;
	m_v3CenterG = other.m_v3CenterG;
	m_v3MinL = other.m_v3MinL;
	m_v3MaxL = other.m_v3MaxL;

	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3ARBBSize = other.m_v3ARBBSize;

	m_m4ToWorld = other.m_m4ToWorld;

	m_uCollidingCount = other.m_uCollidingCount;
	m_CollidingArray = other.m_CollidingArray;
}
RigidBody& RigidBody::operator=(RigidBody const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		RigidBody temp(other);
		Swap(temp);
	}
	return *this;
}
RigidBody::~RigidBody() { Release(); };

//--- other Methods
void RigidBody::AddCollisionWith(RigidBody* other)
{
	//if its already in the list return
	if (IsInCollidingArray(other))
		return;
	/*
		check if the object is already in the colliding set, if
		the object is already there return with no changes
	*/

	//insert the entry
	PRigidBody* pTemp;
	pTemp = new PRigidBody[m_uCollidingCount + 1];
	if (m_CollidingArray)
	{
		memcpy(pTemp, m_CollidingArray, sizeof(RigidBody*) * m_uCollidingCount);
		delete[] m_CollidingArray;
		m_CollidingArray = nullptr;
	}
	pTemp[m_uCollidingCount] = other;
	m_CollidingArray = pTemp;

	++m_uCollidingCount;
}

void RigidBody::RemoveCollisionWith(RigidBody* other)
{
	//if there are no dimensions return
	if (m_uCollidingCount == 0)
		return;

	//we look one by one if its the one wanted
	for (uint i = 0; i < m_uCollidingCount; i++)
	{
		if (m_CollidingArray[i] == other)
		{
			//if it is, then we swap it with the last one and then we pop
			std::swap(m_CollidingArray[i], m_CollidingArray[m_uCollidingCount - 1]);
			PRigidBody* pTemp;
			pTemp = new PRigidBody[m_uCollidingCount - 1];
			if (m_CollidingArray)
			{
				memcpy(pTemp, m_CollidingArray, sizeof(uint) * (m_uCollidingCount - 1));
				delete[] m_CollidingArray;
				m_CollidingArray = nullptr;
			}
			m_CollidingArray = pTemp;

			--m_uCollidingCount;
			return;
		}
	}
}

void RigidBody::ClearCollidingList(void)
{
	m_uCollidingCount = 0;
	if (m_CollidingArray)
	{
		delete[] m_CollidingArray;
		m_CollidingArray = nullptr;
	}
}

uint RigidBody::SAT(RigidBody* const a_pOther)
{
	//Backup matrices and halfwidths
	matrix4 mToWorldA = m_m4ToWorld;
	vector3 v3HalfWidthA = m_v3HalfWidth;
	vector3 v3CenterGlobalA = m_v3CenterG;
	matrix4 mToWorldB = a_pOther->m_m4ToWorld;
	vector3 v3HalfWidthB = a_pOther->m_v3HalfWidth;
	vector3 v3CenterGlobalB = a_pOther->m_v3CenterG;

	return BTXs::ComputeSAT(mToWorldA, v3HalfWidthA, v3CenterGlobalA, mToWorldB, v3HalfWidthB, v3CenterGlobalB);
}

bool RigidBody::IsColliding(RigidBody* const other, bool a_bAddToCollisionList)
{
	//check if spheres are colliding
	//bool bColliding = (glm::distance(m_v3CenterG, other->m_v3CenterG) < m_fRadius + other->m_fRadius);
	
	//distance2 is faster than squared root distance
	//bool bColliding = glm::distance2(m_v3CenterG, other->m_v3CenterG) <
	//	(m_fRadius + other->m_fRadius) * (m_fRadius + other->m_fRadius);

	//replaced by ARBB vs ARBB as this is faster than computing sqr roots 
	// and its used as pretest anyways best case its one single comparison,
	// worst case its the 6
	bool bColliding = true;
	if (this->m_v3MaxG.x < other->m_v3MinG.x)
		bColliding = false;
	else if (this->m_v3MinG.x > other->m_v3MaxG.x)
		bColliding = false;
	
	else if (this->m_v3MaxG.y < other->m_v3MinG.y)
		bColliding = false;
	else if (this->m_v3MinG.y > other->m_v3MaxG.y)
		bColliding = false;
	
	else if (this->m_v3MaxG.z < other->m_v3MinG.z)
		bColliding = false;
	else if (this->m_v3MinG.z > other->m_v3MaxG.z)
		bColliding = false;

	if (bColliding) 
	{	
		//they failed the pretest, use specialized test
		//if we could not find a Separating Axis then they are colliding
		bColliding = (SAT(other) == BTXs::eSATResults::SAT_NONE);
	}

	//When we want to add to the collision list
	if (a_bAddToCollisionList)
	{
		//if they are colliding even after the specialized test
		if (bColliding)
		{
			//add the collisions
			this->AddCollisionWith(other);
			other->AddCollisionWith(this);
		}
		else
		{
			//they are not colliding remove the collisions
			this->RemoveCollisionWith(other);
			other->RemoveCollisionWith(this);
		}
	}

	return bColliding;
}

bool RigidBody::IsInCollidingArray(RigidBody* a_pEntry)
{
	//see if the entry is in the set
	for (uint i = 0; i < m_uCollidingCount; i++)
	{
		if (m_CollidingArray[i] == a_pEntry)
			return true;
	}
	return false;
}

void RigidBody::AddToRenderList(void)
{
	if (m_bVisibleBS)
	{
		if (m_uCollidingCount > 0)
		{
			m_pModelMngr->AddSpecialToRenderList(RTSG::eBTX_SPECIALMODEL::SPHERECORNFLOWER,
				glm::translate(m_m4ToWorld, m_v3CenterL) * glm::scale(vector3(m_fRadius)));
		}
		else
		{
			m_pModelMngr->AddSpecialToRenderList(RTSG::eBTX_SPECIALMODEL::SPHERECORNFLOWER,
				glm::translate(m_m4ToWorld, m_v3CenterL) * glm::scale(vector3(m_fRadius)));
		}
	}
	if (m_bVisibleOBB)
	{
		if (m_uCollidingCount > 0)
		{
			m_pModelMngr->AddSpecialToRenderList(RTSG::eBTX_SPECIALMODEL::CUBERED,
				glm::translate(m_m4ToWorld, m_v3CenterL) * glm::scale(m_v3HalfWidth * 2.0f));
		}
		else
		{

			m_pModelMngr->AddSpecialToRenderList(RTSG::eBTX_SPECIALMODEL::CUBEWHITE,
				glm::translate(m_m4ToWorld, m_v3CenterL) * glm::scale(m_v3HalfWidth * 2.0f));
		}
	}
	if (m_bVisibleARBB)
	{
		if (m_uCollidingCount > 0)
		{
			m_pModelMngr->AddSpecialToRenderList(RTSG::eBTX_SPECIALMODEL::CUBEYELLOW,
				glm::translate(m_v3CenterG) * glm::scale(m_v3ARBBSize));
		}
		else
		{
			m_pModelMngr->AddSpecialToRenderList(RTSG::eBTX_SPECIALMODEL::CUBEYELLOW,
				glm::translate(m_v3CenterG) * glm::scale(m_v3ARBBSize));
		}
	}
}
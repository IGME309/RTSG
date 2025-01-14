#include "Simplex\Physics\Octant.h"
using namespace Simplex;
//  Octant
uint Octant::m_uOctantCount = 0;
uint Octant::m_uMaxLevel = 3;
uint Octant::m_uIdealEntityCount = 5;
uint Octant::GetOctantCount(void){ return m_uOctantCount; }
void Octant::Init(void)
{
	m_uChildren = 0;

	m_fSize = 0.0f;

	m_uID = m_uOctantCount;
	m_uLevel = 0;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();

	m_pRoot = nullptr;
	m_pParent = nullptr;
	for (uint n = 0; n < 8; n++)
	{
		m_pChild[n] = nullptr;
	}
}
void Octant::Swap(Octant& other)
{
	std::swap(m_uChildren, other.m_uChildren);

	std::swap(m_fSize, other.m_fSize);
	std::swap(m_uID, other.m_uID);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();

	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_pParent, other.m_pParent);
	for (uint i = 0; i < 8; i++)
	{
		std::swap(m_pChild[i], other.m_pChild[i]);
	}
}
Octant * Octant::GetParent(void) { return m_pParent; }
void Octant::Release(void)
{
	//this is a special kind of release, it will only happen for the root
	if (m_uLevel == 0)
	{
		KillBranches();
	}
	m_uChildren = 0;
	m_fSize = 0.0f;
	m_EntityList.clear();
	m_lChild.clear();
}
//The big 3
Octant::Octant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	//Init the default values
	Init();

	m_uOctantCount = 0;
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_uID = m_uOctantCount;

	m_pRoot = this;
	m_lChild.clear();

	std::vector<vector3> lMinMax; //Will hold all of the Min and Max vectors of the Bounding Object

	uint nObjects = m_pEntityMngr->GetEntityCount();
	for (uint i = 0; i < nObjects; i++)
	{
		Entity* pEntity = m_pEntityMngr->GetEntity(i);
		RigidBody* pRigidBody = pEntity->GetRigidBody();
		lMinMax.push_back(pRigidBody->GetMinGlobal());
		lMinMax.push_back(pRigidBody->GetMaxGlobal());
	}
	RigidBody* pRigidBody = new RigidBody(lMinMax);

	vector3 vHalfWidth = pRigidBody->GetHalfWidth();
	float fMax = vHalfWidth.x;
	for (int i = 1; i < 3; i++)
	{
		if (fMax < vHalfWidth[i])
			fMax = vHalfWidth[i];
	}
	vector3 v3Center = pRigidBody->GetCenterLocal();
	lMinMax.clear();
	SafeDelete(pRigidBody);

	m_fSize = fMax * 2.0f;
	m_v3Center = v3Center;
	m_v3Min = m_v3Center - (vector3(fMax));
	m_v3Max = m_v3Center + (vector3(fMax));

	m_uOctantCount++;

	ConstructTree(m_uMaxLevel);

#ifdef DEBUG
	printf("\nOctree Generated");
#endif
}
Octant::Octant(vector3 a_v3Center, float a_fSize)
{
	//Init the default values
	Init();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	m_v3Min = m_v3Center - (vector3(m_fSize) / 2.0f);
	m_v3Max = m_v3Center + (vector3(m_fSize) / 2.0f);

	m_uOctantCount++;
}
Octant::Octant(Octant const& other)
{
	m_uChildren = other.m_uChildren;
	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_fSize = other.m_fSize;
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_pParent = other.m_pParent;

	m_pRoot, other.m_pRoot;
	m_lChild, other.m_lChild;

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();

	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i] = other.m_pChild[i];
	}
}
Octant& Octant::operator=(Octant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Octant temp(other);
		Swap(temp);
	}
	return *this;
}
Octant::~Octant() { Release(); };
//Accessors
float Octant::GetSize(void) { return m_fSize; }
vector3 Octant::GetCenterGlobal(void) { return m_v3Center; }
vector3 Octant::GetMinGlobal(void) { return m_v3Min; }
vector3 Octant::GetMaxGlobal(void) { return m_v3Max; }
//--- Non Standard Singleton Methods
void Octant::Display(uint a_nIndex, vector3 a_v3Color)
{
	if (m_uID == a_nIndex)
	{
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) *
			glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);

		return;
	}
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->Display(a_nIndex);
	}
}
void Octant::Display(vector3 a_v3Color)
{
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->Display(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) *
		glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
}
void Octant::Subdivide(void)
{
	//If this node has reach the maximum depth return without changes
	if (m_uLevel >= m_uMaxLevel)
		return;

	//If this node has been already subdivided return without changes
	if (m_uChildren != 0)
		return;

	//As this will have children it will not be a leaf
	m_uChildren = 8;

	float fSize = m_fSize / 4.0f;
	float fSizeD = fSize * 2.0f;
	vector3 v3Center;

	//Octant 0 Bottom Left Back
	v3Center = m_v3Center;
	v3Center.x -= fSize;
	v3Center.y -= fSize;
	v3Center.z -= fSize;
	m_pChild[0] = new Octant(v3Center, fSizeD);

	//Octant 1 Bottom Right Back
	v3Center.x += fSizeD;
	m_pChild[1] = new Octant(v3Center, fSizeD);

	//Octant 2 Bottom Right Front
	v3Center.z += fSizeD;
	m_pChild[2] = new Octant(v3Center, fSizeD);

	//Octant 3 Bottom Left Front
	v3Center.x -= fSizeD;
	m_pChild[3] = new Octant(v3Center, fSizeD);

	//Octant 4 Top Left Front
	v3Center.y += fSizeD;
	m_pChild[4] = new Octant(v3Center, fSizeD);

	//Octant 5 Top Left Back
	v3Center.z -= fSizeD;
	m_pChild[5] = new Octant(v3Center, fSizeD);

	//Octant 6 Top Right Back
	v3Center.x += fSizeD;
	m_pChild[6] = new Octant(v3Center, fSizeD);

	//Octant 7 Top Right Front
	v3Center.z += fSizeD;
	m_pChild[7] = new Octant(v3Center, fSizeD);

	for (uint nIndex = 0; nIndex < 8; nIndex++)
	{
		m_pChild[nIndex]->m_pRoot = m_pRoot;
		m_pChild[nIndex]->m_pParent = this;
		m_pChild[nIndex]->m_uLevel = m_uLevel + 1;
		if (m_pChild[nIndex]->ContainsMoreThan(m_uIdealEntityCount))
		{
			m_pChild[nIndex]->Subdivide();
		}
	}
}
Octant * Octant::GetChild(uint a_nChild)
{
	if (a_nChild > 7) return nullptr;
	return m_pChild[a_nChild];
}
bool Octant::IsColliding(uint a_uRBIndex)
{
	uint nObjectCount = m_pEntityMngr->GetEntityCount();
	//If the index given is larger than the number of elements in the bounding object there is no collision
	if (a_uRBIndex >= nObjectCount)
		return false;
	//As the Octree will never rotate or scale this collision is as easy as an Axis Alligned Bounding Box
	//Get all vectors in global space (the octant ones are already in Global)
	Entity* pEntity = m_pEntityMngr->GetEntity(a_uRBIndex);
	RigidBody* pRigidBody = pEntity->GetRigidBody();
	vector3 v3MinO = pRigidBody->GetMinGlobal();
	vector3 v3MaxO = pRigidBody->GetMaxGlobal();

	//Check for X
	if (m_v3Max.x < v3MinO.x)
		return false;
	if (m_v3Min.x > v3MaxO.x)
		return false;

	//Check for Y
	if (m_v3Max.y < v3MinO.y)
		return false;
	if (m_v3Min.y > v3MaxO.y)
		return false;

	//Check for Z
	if (m_v3Max.z < v3MinO.z)
		return false;
	if (m_v3Min.z > v3MaxO.z)
		return false;

	return true;
}
bool Octant::IsLeaf(void) { return m_uChildren == 0; }
bool Octant::ContainsMoreThan(uint a_nEntities)
{
	uint nCount = 0;
	uint nObjectCount = m_pEntityMngr->GetEntityCount();
	for (uint n = 0; n < nObjectCount; n++)
	{
		if (IsColliding(n))
			nCount++;
		if (nCount > a_nEntities)
			return true;
	}
	return false;
}
void Octant::KillBranches(void)
{
	/*This method has recursive behavior that is somewhat hard to explain line by line but
	it will traverse the whole tree until it reaches a node with no children and
	once it returns from it to its parent it will kill all of its children, recursively until
	it reaches back the node that called it.*/
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->KillBranches();
		delete m_pChild[nIndex];
		m_pChild[nIndex] = nullptr;
	}
	m_uChildren = 0;
}
void Octant::DisplayLeafs(vector3 a_v3Color)
{
	uint nLeafs = m_lChild.size();
	for (uint nChild = 0; nChild < nLeafs; nChild++)
	{
		m_lChild[nChild]->DisplayLeafs(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) *
		glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
}
void Octant::ClearEntityList(void)
{
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		m_pChild[nChild]->ClearEntityList();
	}
	m_EntityList.clear();
}
void Octant::ConstructTree(uint a_nMaxLevel)
{
	//If this method is tried to be applied to something else
	//other than the root, don't.
	if (m_uLevel != 0)
		return;

	m_uMaxLevel = a_nMaxLevel;

	m_uOctantCount = 1;
	
	//ClearEntityList();
	m_EntityList.clear();

	//clear the tree
	KillBranches();
	m_lChild.clear();

	//If the base tree
	if (ContainsMoreThan(m_uIdealEntityCount))
	{
		Subdivide();
	}

	//Add octant ID to Entities
	AssignIDtoEntity();

	//construct the list of objects
	ConstructList();
}
void Octant::AssignIDtoEntity(void)
{
	//traverse until you reach a leaf
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		m_pChild[nChild]->AssignIDtoEntity();
	}
	if (m_uChildren == 0) //if this is a leaf
	{
		uint nEntities = m_pEntityMngr->GetEntityCount();
		for (uint nIndex = 0; nIndex < nEntities; nIndex++)
		{
			if (IsColliding(nIndex))
			{
				m_EntityList.push_back(nIndex);
				m_pEntityMngr->AddDimension(nIndex, m_uID);
			}
		}
	}
}

void Octant::ConstructList(void)
{
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		m_pChild[nChild]->ConstructList();
	}

	if (m_EntityList.size() > 0)
	{
		m_pRoot->m_lChild.push_back(this);
	}
}
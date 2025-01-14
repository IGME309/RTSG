#include "Space.h"
using namespace RTSG;
//  Space
uint Space::m_uNodeCount = 0;
uint Space::m_uMaxLevel = 2;
Space::Space(uint a_uMaxLevel)
{
	/*
	* This constructor is meant to be used ONLY on the root Space, there is already a working constructor
	* that will take a size and a center to create a new space
	*/

	Init();//Init the default values

	m_uNodeCount = 0;
	m_uID = m_uNodeCount;
	m_uMaxLevel = a_uMaxLevel;

	//create a rigid body that encloses all the objects in this Space, 
	//to subdivide the Space based on will create x * y * z children. Children
	//will not have children of their own
	std::vector<vector3> lMinMax; //Will hold all of the Min and Max vectors each Bounding Object
	//Count the entities
	uint uEntities = m_pEntityMngr->GetEntityCount();
	//for each one of them
	for (uint i = 0; i < uEntities; i++)
	{
		//get the entity
		Entity* pEntity = m_pEntityMngr->GetEntity(i);
		//get its rigid body
		RigidBody* pRigidBody = pEntity->GetRigidBody();
		//get its max and mins into the list
		lMinMax.push_back(pRigidBody->GetMinGlobal());
		lMinMax.push_back(pRigidBody->GetMaxGlobal());
	}
	//make a new rigid body around the objects
	m_pRigidBody = new RigidBody(lMinMax);
	//Increment the Space count
	m_uNodeCount++;
	//Subdivide the space based on the arguments
	Subdivide();
	//Once the tree is constructed check where the entities are located
	AssignIDstoEntities();
}
//Private constructor
Space::Space(vector3 a_v3Center, vector3 a_v3Size)
{
	//This can only be applied to children not the root
	if (m_uNodeCount < 1)
		return;

	//Will create the Space object based on the center and size but will not construct children
	Init();
	std::vector<vector3> lMinMax;
	lMinMax.push_back(a_v3Center - (a_v3Size / 2.0f));//Min
	lMinMax.push_back(a_v3Center + (a_v3Size / 2.0f));//Max
	m_pRigidBody = new RigidBody(lMinMax);
	m_uID = m_uNodeCount;
	m_uNodeCount++;
}
bool Space::IsColliding(uint a_uRBIndex)
{
	//If the index given is larger than the number of elements in 
	//the entity manager there is no collision
	if (a_uRBIndex >= m_pEntityMngr->GetEntityCount())
		return false;

	//Get the rigid body of the Entity queried
	Entity* pEntity = m_pEntityMngr->GetEntity(a_uRBIndex);
	RigidBody* pRigidBody = pEntity->GetRigidBody();
	//Ask if the rigid body of the entity is colliding with this Space
	return m_pRigidBody->IsColliding(pRigidBody, false);
}
void Space::Display(uint a_nIndex)
{
	//If a value larger than the count of nodes is sent render all
	if (a_nIndex > m_uNodeCount)
	{
		Display();
		return;
	}

	//Traverse the children
	for (uint uChild = 0; uChild < m_uChildren; uChild++)
	{
		if (m_pChild[uChild])
		{
			m_pChild[uChild]->Display(a_nIndex);//recursive behavior
		}
	}

	//Once the specified index is found, render it
	if (m_uID == a_nIndex)
	{
		vector3 v3Center = m_pRigidBody->GetCenterGlobal();
		vector3 v3Size = m_pRigidBody->GetHalfWidth() * 2.0f;
		//render the wire cube
		m_pModelMngr->AddSpecialToRenderList(
			RTSG::eBTX_SPECIALMODEL::CUBEWHITE,
			glm::translate(v3Center) * glm::scale(v3Size));
	}
}
void Space::Display()
{
	//Traverse the children
	for (uint uChild = 0; uChild < m_uChildren; uChild++)
	{
		if (m_pChild[uChild])
		{
			m_pChild[uChild]->Display(); //recursive behavior
		}
	}

	//Render the space
	vector3 v3Center = m_pRigidBody->GetCenterGlobal();
	vector3 v3Size = m_pRigidBody->GetHalfWidth() * 2.0f;
	//render the wire cube
	m_pModelMngr->AddSpecialToRenderList(
		RTSG::eBTX_SPECIALMODEL::CUBEWHITE,
		glm::translate(v3Center) * glm::scale(v3Size));
}
void Space::Subdivide(void)
{
	//If the max level has been reached stop
	if (m_uLevel >= m_uMaxLevel)
		return;

	//If this Space has been subdivided already, return without changes
	if (m_uChildren != 0)
		return;

	//create as many entities as needed
	m_uChildren = 8;//It will always divide evenly
	m_pChild = new PNode[m_uChildren];

	//each child will be the same size, the parents divided by how many we need
	vector3 v3ChildrenSize = m_pRigidBody->GetHalfWidth() * 2.0f;
	v3ChildrenSize.x /= 2.0f;
	v3ChildrenSize.y /= 2.0f;
	v3ChildrenSize.z /= 2.0f;
	//The center of each children will be at different positions
	vector3 v3ChildrenCenter = v3ChildrenSize / 2.0f;
	/*
	* We will iterate from left to right, bottom to top, front to back
	*/
	uint index = 0;
	vector3 v3ParentMin = m_pRigidBody->GetMinGlobal();
	vector3 v3CurrentPosition = v3ParentMin + v3ChildrenCenter;
	for (uint z = 0; z < 2; z++)
	{
		for (uint y = 0; y < 2; y++)
		{
			for (uint x = 0; x < 2; x++)
			{
				m_pChild[index] = new Space(v3CurrentPosition, v3ChildrenSize);
				m_pChild[index]->m_uLevel = m_uLevel + 1;
				m_pChild[index]->Subdivide();
				v3CurrentPosition.x += v3ChildrenSize.x;
				index++;
			}
			v3CurrentPosition.x = v3ParentMin.x + v3ChildrenCenter.x;
			v3CurrentPosition.y += v3ChildrenSize.y;
		}
		v3CurrentPosition.x = v3ParentMin.x + v3ChildrenCenter.x;
		v3CurrentPosition.y = v3ParentMin.y + v3ChildrenCenter.y;
		v3CurrentPosition.z += v3ChildrenSize.z;
	}
}
void Space::AssignIDstoEntities(void)
{
	//Traverse the children
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->AssignIDstoEntities();
	}
	//Only Assign IDs to leaf nodes, otherwise its brute force
	if (IsLeaf())
	{
		//for each entity in the entity manager check if its colliding
		//with this leaf, if it is then assign this ID to the entity's 
		//space list of spaces, this ID will act as the space ID
		uint nEntities = m_pEntityMngr->GetEntityCount();
		for (uint nIndex = 0; nIndex < nEntities; nIndex++)
		{
			//Check if this Space is colliding with the entity
			if (IsColliding(nIndex))
			{
				//if it is then add the uid as the space for the entity
				m_pEntityMngr->AddSpace(nIndex, m_uID);
			}
		}
	}
}
void Space::Init(void)
{
	m_uID = 0;
	m_uLevel = 0;
	m_uChildren = 0;
	m_pRigidBody = nullptr;
	m_pChild = nullptr;

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();
}
void Space::Swap(Space& other)
{
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_uChildren, other.m_uChildren);
	std::swap(m_uMaxLevel, other.m_uMaxLevel);
	std::swap(m_pRigidBody, other.m_pRigidBody);
	std::swap(m_pChild, other.m_pChild);

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();
}
void Space::Release(void)
{
	//recursive behavior, get to the children first then release root
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->Release();
	}
	//Once a Leaf is reach release its content
	SafeDelete(m_pRigidBody);
	if (m_pChild != nullptr)
	{
		delete[] m_pChild;
		m_pChild = nullptr;
		
	}
	//This will only happen on root
	if (m_uLevel == 0)
	{
		uint uCount = m_pEntityMngr->GetEntityCount();
		for (uint i = 0; i < uCount; i++)
		{
			Entity* pEntity = m_pEntityMngr->GetEntity(i);
			pEntity->ClearSpaceSet();
		}
	}
}
//The big 3
Space::Space(Space const& other)
{
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_uChildren = other.m_uChildren;
	m_uMaxLevel = other.m_uMaxLevel;
	m_pRigidBody = other.m_pRigidBody;
	m_pChild = other.m_pChild;

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();
}
Space& Space::operator=(Space const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Space temp(other);
		Swap(temp);
	}
	return *this;
}
Space::~Space() { Release(); };
//Accessors
vector3 Space::GetCenterGlobal(void) { return m_pRigidBody->GetCenterGlobal(); }
vector3 Space::GetMinGlobal(void) { return m_pRigidBody->GetMinGlobal(); }
vector3 Space::GetMaxGlobal(void) { return m_pRigidBody->GetMaxGlobal(); }
bool Space::IsLeaf(void) { return m_pChild == nullptr; } //Is it childless?
uint Space::GetNodeCount(void) { return m_uNodeCount; }
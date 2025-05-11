#include "Space.h"
using namespace RTSG;
//  Space
uint Node::m_uSpaceCount = 0;
uint Node::m_uMaxLevel = 3;
uint Node::m_uIdealEntityCount = 5;
Node::Node(uint a_uMaxLevel, uint a_uIdealEntityCount)
{
	/*
	* This constructor is meant to be used ONLY on the root Space, there is already a working constructor
	* that will take a size and a center to create a new space
	*/

	Init();//Init the default values

	m_uSpaceCount = 0;
	m_uID = m_uSpaceCount;

	m_uMaxLevel = a_uMaxLevel;

	m_uIdealEntityCount = m_uIdealEntityCount;

	//create a rigid body that encloses all the objects in this octant, if necessary you will need
	//to subdivide the octant based on how many objects are in it already an how many you IDEALLY
	//want in it, remember each subdivision will create 8 children for this octant but not all children
	//of those children will have children of their own

	std::vector<vector3> lMinMax; //Will hold all of the Min and Max vectors each Bounding Object
	//Example values, they are hard coded, do not use them
	lMinMax.push_back(vector3());
	lMinMax.push_back(vector3(10.0f));

	//make a new rigid body around the objects
	m_pRigidBody = new RigidBody(lMinMax);
	
	//Increment the Space count on each Space created
	m_uSpaceCount++;
	
	//Subdivide the space based on the arguments
		
	//Once the tree is constructed check what entity corresponds to what Space
	AssignIDstoEntities();
}
//Private constructor
Node::Node(vector3 a_v3Center, vector3 a_v3Size)
{
	//This can only be applied to children not the root
	//This constructor only takes the center and the size not the entities
	if (m_uSpaceCount < 1)
		return;

	//Will create the Space object based on the center and size but will not construct children
	Init();
	std::vector<vector3> lMinMax;
	lMinMax.push_back(vector3(0.0f));//Min value hardcoded 
	lMinMax.push_back(vector3(2.0f));//Max value hardcoded
	m_pRigidBody = new RigidBody(lMinMax);
	m_uID = m_uSpaceCount;//ID of the current Space
	m_uSpaceCount++;//Increment the count of the Spaces
}
bool Node::IsColliding(uint a_uRBIndex)
{
	//Get how many objects there are in the world
	//If the index given is larger than the number of elements in the bounding object there is no collision
	//As the Octree will never rotate or scale this collision is as easy as an Axis Alligned Bounding Box
	//Get all vectors in global space (the octant ones are already in Global)
	return true; // for the sake of startup code
}
bool Node::ContainsAtLeast(uint a_nEntities)
{
	//This method will count how many entities are contained in the current Space
	//if there are at least a_nEntities return true
	return false;//hardcoded for class purposes
}
void Node::Subdivide(void)
{
	//For this method IF YOU HAVE NOT REACHED the maximum level
	//you want to subdivide the current Space into 8 children
	//Then divide the children if that child has more than the
	//ideal count of entities
}
void Node::AssignIDstoEntities(void)
{
	//Traverse the tree and on leafs check for all entities
	//that are colliding with the current Space, then use
	//m_pEntityMngr->AddDimension(nIndex, m_uID); so the
	//entity knows they belong to this space/dimension/Space
}
#pragma region DOES NOT NEED CHANGES
void Node::Init(void)
{
	m_uID = 0;
	m_uLevel = 0;
	m_uChildren = 0;

	m_pRigidBody = nullptr;
	m_pChild[8] = { nullptr };

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();
}
void Node::Swap(Node& other)
{
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_uChildren, other.m_uChildren);

	std::swap(m_pRigidBody, other.m_pRigidBody);
	for (uint uChild = 0; uChild < m_uChildren; uChild++)
	{
		m_pChild[uChild] = other.m_pChild[uChild];
	}

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();
}
void Node::Release(void)
{
	//recursive behavior, get to the children first then release root
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		m_pChild[nChild]->Release();
	}
	//Once a Leaf is reach release its content
	SafeDelete(m_pRigidBody);
	
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		if (m_pChild[nChild] != nullptr)
		{
			delete m_pChild[nChild];
			m_pChild[nChild] = nullptr;
		}
	}

	m_uChildren = 0;

	//at root make sure to release the entity manager
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
Node::Node(Node const& other)
{
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_uChildren = other.m_uChildren;
	
	m_pRigidBody = other.m_pRigidBody;
	for (uint uChild = 0; uChild < m_uChildren; uChild++)
	{
		m_pChild[uChild] = other.m_pChild[uChild];
	}

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();
}
Node& Node::operator=(Node const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Node temp(other);
		Swap(temp);
	}
	return *this;
}

void Node::Display(uint a_nIndex)
{
	//If a value larger than the count of Spaces is sent render all
	if (a_nIndex > m_uSpaceCount)
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
void Node::Display()
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
Node::~Node() { Release(); };
//Accessors
vector3 Node::GetCenterGlobal(void) { return m_pRigidBody->GetCenterGlobal(); }
vector3 Node::GetMinGlobal(void) { return m_pRigidBody->GetMinGlobal(); }
vector3 Node::GetMaxGlobal(void) { return m_pRigidBody->GetMaxGlobal(); }
bool Node::IsLeaf(void) { return m_uChildren == 0; } //Is it childless?
uint Node::GetSpaceCount(void) { return m_uSpaceCount; }
#pragma endregion
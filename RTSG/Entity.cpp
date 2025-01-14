#include "RTSG\Physics\Entity.h"
using namespace RTSG;
std::map<String, Entity*> Entity::m_IDMap;
//  Accessors
Solver* Entity::GetSolver(void) { return m_pSolver; }
bool Entity::HasThisRigidBody(RigidBody* a_pRigidBody) { return m_pRigidBody == a_pRigidBody; }
RigidBody::PRigidBody* Entity::GetColliderArray(void) { return m_pRigidBody->GetColliderArray(); }
uint Entity::GetCollidingCount(void) { return m_pRigidBody->GetCollidingCount(); }
matrix4 Entity::GetModelMatrix(void){ return m_m4ToWorld; }
void Entity::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (!m_bInMemory)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_pRigidBody->SetModelMatrix(m_m4ToWorld);

	//experimental way of calculating a matrix components
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(m_m4ToWorld, scale, rotation, translation, skew, perspective);

	m_pSolver->SetPosition(translation);
	m_pSolver->SetSize(scale);

	//m_pSolver->SetPosition(vector3(m_m4ToWorld[3]));
}
Model* Entity::GetModel(void){return m_pModel;}
RigidBody* Entity::GetRigidBody(void){	return m_pRigidBody; }
bool Entity::IsInitialized(void){ return m_bInMemory; }
String Entity::GetUniqueID(void) { return m_sUniqueID; }
void Entity::SetAxisVisible(bool a_bVisible) { m_bAxisVisible = a_bVisible; }
void Entity::SetRBVisible(bool a_bVisible) { m_bRBVisible = a_bVisible; }

void Entity::SetPosition(vector3 a_v3Position) { if(m_pSolver) m_pSolver->SetPosition(a_v3Position); }
vector3 Entity::GetPosition(void)
{
	if (m_pSolver != nullptr)
		return m_pSolver->GetPosition();
	return vector3();
}

void Entity::SetVelocity(vector3 a_v3Velocity) { if (m_pSolver) m_pSolver->SetVelocity(a_v3Velocity); }
vector3 Entity::GetVelocity(void)
{
	if (m_pSolver != nullptr)
		return m_pSolver->GetVelocity();
	return vector3();
}

void Entity::SetMass(float a_fMass) { if (m_pSolver) m_pSolver->SetMass(a_fMass); }
float Entity::GetMass(void)
{
	if (m_pSolver != nullptr)
		return m_pSolver->GetMass();
	return 1.0f;
}
//  Entity
void Entity::Init(void)
{
	m_pModelMngr = ModelManager::GetInstance();
	m_bInMemory = false;
	m_bAxisVisible = false;
	m_bRBVisible = true;
	m_pModel = nullptr;
	m_pRigidBody = nullptr;
	m_SpaceArray = nullptr;
	m_m4ToWorld = IDENTITY_M4;
	m_sUniqueID = "";
	m_nSpaceCount = 0;
	m_bUsePhysicsSolver = false;
	m_pSolver = nullptr;
}
void Entity::Swap(Entity& other)
{
	m_bInMemory = false;
	std::swap(m_pModel, other.m_pModel);
	std::swap(m_pRigidBody, other.m_pRigidBody);
	std::swap(m_m4ToWorld, other.m_m4ToWorld);
	std::swap(m_pModelMngr, other.m_pModelMngr);
	std::swap(m_bInMemory, other.m_bInMemory);
	std::swap(m_sUniqueID, other.m_sUniqueID);
	std::swap(m_bAxisVisible, other.m_bAxisVisible);
	std::swap(m_bRBVisible, other.m_bRBVisible);
	std::swap(m_nSpaceCount, other.m_nSpaceCount);
	std::swap(m_SpaceArray, other.m_SpaceArray);
	std::swap(m_pSolver, other.m_pSolver);
}
void Entity::Release(void)
{
	m_pModelMngr = nullptr;
	//it is not the job of the entity to release the model, 
	//it is for the mesh manager to do so.
	m_pModel = nullptr;
	if (m_SpaceArray)
	{
		delete[] m_SpaceArray;
		m_SpaceArray = nullptr;
	}
	SafeDelete(m_pRigidBody);
	SafeDelete(m_pSolver);
	m_IDMap.erase(m_sUniqueID);
}
//The big 3
Entity::Entity(Model* a_pModel, String a_sUniqueID)
{
	Init();
	//If there is no model return
	if (!a_pModel)
		return;
	//If the model is not initialized return
	if (a_pModel->GetName() == "")
		return;

	//if the model is loaded
	m_pModelMngr->AddModel(m_pModel);
	GenUniqueID(a_sUniqueID);
	m_sUniqueID = a_sUniqueID;
	m_IDMap[a_sUniqueID] = this;
	m_pRigidBody = new RigidBody(m_pModel->GetVertexList()); //generate a rigid body
	m_bInMemory = true; //mark this entity as viable
	m_pSolver = new Solver();
}
Entity::Entity(String a_sFileName, String a_sUniqueID)
{
	Init();
	String sName = m_pModelMngr->LoadModel(a_sFileName);
	if (sName == "")
		return;

	//if the model is loaded
	m_pModel = m_pModelMngr->GetModel(sName);
	GenUniqueID(a_sUniqueID);
	m_sUniqueID = a_sUniqueID;
	m_IDMap[a_sUniqueID] = this;
	m_pRigidBody = new RigidBody(m_pModel->GetVertexList()); //generate a rigid body
	m_bInMemory = true; //mark this entity as viable
	m_pSolver = new Solver();
	
	
}
Entity::Entity(Entity const& other)
{
	m_bInMemory = other.m_bInMemory;
	m_pModel = other.m_pModel;
	//generate a new rigid body we do not share the same rigid body as we do the model
	m_pRigidBody = new RigidBody(m_pModel->GetVertexList()); 
	m_m4ToWorld = other.m_m4ToWorld;
	m_pModelMngr = other.m_pModelMngr;
	m_sUniqueID = other.m_sUniqueID;
	m_bAxisVisible = other.m_bAxisVisible;
	m_bRBVisible = other.m_bRBVisible;
	m_nSpaceCount = other.m_nSpaceCount;
	m_SpaceArray = other.m_SpaceArray;
	m_pSolver = new Solver(*other.m_pSolver);
}
Entity& Entity::operator=(Entity const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		Entity temp(other);
		Swap(temp);
	}
	return *this;
}
Entity::~Entity(){Release();}
//--- Methods
void Entity::AddToRenderList()
{
	//if not in memory return
	if (!m_bInMemory)
		return;

	//draw model
	m_pModel->AddToRenderList(m_m4ToWorld);
	
	//draw rigid body
	if(m_bRBVisible)
		m_pRigidBody->AddToRenderList();

	if (m_bAxisVisible)
		m_pModelMngr->AddAxisToRenderList(m_m4ToWorld);
	
}
Entity* Entity::GetEntity(String a_sUniqueID)
{
	//look the entity based on the unique id
	auto entity = m_IDMap.find(a_sUniqueID);
	//if not found return nullptr, if found return it
	return entity == m_IDMap.end() ? nullptr : entity->second;
}
void Entity::GenUniqueID(String& a_sUniqueID)
{
	static uint index = 0;
	String sName = a_sUniqueID;
	Entity* pEntity = GetEntity(a_sUniqueID);
	//while Entity exists keep changing name
	while (pEntity)
	{
		a_sUniqueID = sName + "_" + std::to_string(index);
		index++;
		pEntity = GetEntity(a_sUniqueID);
	}
	return;
}
void Entity::AddSpace(uint a_uSpace)
{
	//we need to check that this space is not already allocated in the list
	if (IsInSpace(a_uSpace))
		return;//it is, so there is no need to add

	//insert the entry
	uint* pTemp;
	pTemp = new uint[m_nSpaceCount + 1];
	if(m_SpaceArray)
	{
		memcpy(pTemp, m_SpaceArray, sizeof(uint) * m_nSpaceCount);
		delete[] m_SpaceArray;
		m_SpaceArray = nullptr;
	}
	pTemp[m_nSpaceCount] = a_uSpace;
	m_SpaceArray = pTemp;

	++m_nSpaceCount;

	SortSpaces();
}
void Entity::RemoveSpace(uint a_uSpace)
{
	//if there are no spaces return
	if (m_nSpaceCount == 0)
		return;

	//we look one by one if its the one wanted
	for (uint i = 0; i < m_nSpaceCount; i++)
	{
		if (m_SpaceArray[i] == a_uSpace)
		{
			//if it is, then we swap it with the last one and then we pop
			std::swap(m_SpaceArray[i], m_SpaceArray[m_nSpaceCount - 1]);
			uint* pTemp;
			pTemp = new uint[m_nSpaceCount - 1];
			if (m_SpaceArray)
			{
				memcpy(pTemp, m_SpaceArray, sizeof(uint) * (m_nSpaceCount-1));
				delete[] m_SpaceArray;
				m_SpaceArray = nullptr;
			}
			m_SpaceArray = pTemp;
			
			--m_nSpaceCount;
			SortSpaces();
			return;
		}
	}
}
void Entity::ClearSpaceSet(void)
{
	if (m_SpaceArray)
	{
		delete[] m_SpaceArray;
		m_SpaceArray = nullptr;
	}
	m_nSpaceCount = 0;
}
bool Entity::IsInSpace(uint a_uSpace)
{
	//see if the entry is in the set
	for (uint i = 0; i < m_nSpaceCount; i++)
	{
		if (m_SpaceArray[i] == a_uSpace)
			return true;
	}
	return false;
}
bool Entity::SharesSpace(Entity* const a_pOther)
{
	
	//special case: if there are no spaces on either Entity
	//then they live in the special global space
	if (0 == m_nSpaceCount)
	{
		//if no spatial optimization all cases should fall here as every 
		//entity is by default, under the special global space only
		if(0 == a_pOther->m_nSpaceCount)
			return true;
	}

	//for each space on both Entities we check if there is a common space
	for (uint i = 0; i < m_nSpaceCount; ++i)
	{
		for (uint j = 0; j < a_pOther->m_nSpaceCount; j++)
		{
			if (m_SpaceArray[i] == a_pOther->m_SpaceArray[j])
				return true; //as soon as we find one we know they share dimensionality
		}
	}

	//could not find a common space
	return false;
}
bool Entity::IsColliding(Entity* const other)
{
	//if not in memory return
	if (!m_bInMemory || !other->m_bInMemory)
		return true;

	//if the entities are not living in the same space
	//they are not colliding
	if (!SharesSpace(other))
		return false;

	return m_pRigidBody->IsColliding(other->GetRigidBody());
}
void Entity::ClearCollisionList(void)
{
	m_pRigidBody->ClearCollidingList();
}
void Entity::SortSpaces(void)
{
	std::sort(m_SpaceArray, m_SpaceArray + m_nSpaceCount);
}
void Entity::ApplyForce(vector3 a_v3Force)
{
	m_pSolver->ApplyForce(a_v3Force);
}
void Entity::Update(void)
{
	if (m_bUsePhysicsSolver)
	{
		m_pSolver->Update();
		SetModelMatrix(glm::translate(m_pSolver->GetPosition()) * glm::scale(m_pSolver->GetSize()));
	}
}
void Entity::ResolveCollision(Entity* a_pOther)
{
	if (m_bUsePhysicsSolver)
	{
		m_pSolver->ResolveCollision(a_pOther->GetSolver());
	}
}
void Entity::UsePhysicsSolver(bool a_bUse)
{
	m_bUsePhysicsSolver = a_bUse;
}

void Entity::SetNewSolver(Solver* a_pNewSolver)
{
	//Check if the solver is different than the current one
	if (a_pNewSolver != m_pSolver)
	{
		// check the current solver exists and release it 
		SafeDelete(m_pSolver);
		m_pSolver = a_pNewSolver;
	}
}
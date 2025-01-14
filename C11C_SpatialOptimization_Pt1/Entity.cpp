#include "Entity.h"

std::map<String, Entity*> Entity::m_IDMap;
//  Accessors
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
}
RTSG::Model* Entity::GetModel(void){return m_pModel;}
RigidBody* Entity::GetRigidBody(void){	return m_pRigidBody; }
bool Entity::IsInitialized(void){ return m_bInMemory; }
String Entity::GetUniqueID(void) { return m_sUniqueID; }
void Entity::SetAxisVisible(bool a_bSetAxis) { m_bSetAxis = a_bSetAxis; }
//  Entity
void Entity::Init(void)
{
	m_pModelMngr = RTSG::ModelManager::GetInstance();
	m_bInMemory = false;
	m_bSetAxis = false;
	m_pModel = nullptr;
	m_pRigidBody = nullptr;
	m_DimensionArray = nullptr;
	m_m4ToWorld = IDENTITY_M4;
	m_sUniqueID = "";
	m_nDimensionCount = 0;
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
	std::swap(m_bSetAxis, other.m_bSetAxis);
	std::swap(m_nDimensionCount, other.m_nDimensionCount);
	std::swap(m_DimensionArray, other.m_DimensionArray);
}
void Entity::Release(void)
{
	m_pModelMngr = nullptr;
	//it is not the job of the entity to release the model, 
	//it is for the mesh manager to do so.
	m_pModel = nullptr;
	if (m_DimensionArray)
	{
		delete[] m_DimensionArray;
		m_DimensionArray = nullptr;
	}
	SafeDelete(m_pRigidBody);
	m_IDMap.erase(m_sUniqueID);
}
//The big 3
Entity::Entity(RTSG::Model* a_pModel, String a_sUniqueID)
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
	m_bSetAxis = other.m_bSetAxis;
	m_nDimensionCount = other.m_nDimensionCount;
	m_DimensionArray = other.m_DimensionArray;
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
void Entity::AddToRenderList(bool a_bDrawRigidBody)
{
	//if not in memory return
	if (!m_bInMemory)
		return;

	//draw model
	m_pModel->AddToRenderList(m_m4ToWorld);
	
	//draw rigid body
	if(a_bDrawRigidBody)
		m_pRigidBody->AddToRenderList();

	if (m_bSetAxis)
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
void Entity::AddDimension(uint a_uDimension)
{
	//we need to check that this dimension is not already allocated in the list
	if (IsInDimension(a_uDimension))
		return;//it is, so there is no need to add

	//insert the entry
	uint* pTemp;
	pTemp = new uint[m_nDimensionCount + 1];
	if(m_DimensionArray)
	{
		memcpy(pTemp, m_DimensionArray, sizeof(uint) * m_nDimensionCount);
		delete[] m_DimensionArray;
		m_DimensionArray = nullptr;
	}
	pTemp[m_nDimensionCount] = a_uDimension;
	m_DimensionArray = pTemp;

	++m_nDimensionCount;

	SortDimensions();
}
void Entity::RemoveDimension(uint a_uDimension)
{
	//if there are no dimensions return
	if (m_nDimensionCount == 0)
		return;

	//we look one by one if its the one wanted
	for (uint i = 0; i < m_nDimensionCount; i++)
	{
		if (m_DimensionArray[i] == a_uDimension)
		{
			//if it is, then we swap it with the last one and then we pop
			std::swap(m_DimensionArray[i], m_DimensionArray[m_nDimensionCount - 1]);
			uint* pTemp;
			pTemp = new uint[m_nDimensionCount - 1];
			if (m_DimensionArray)
			{
				memcpy(pTemp, m_DimensionArray, sizeof(uint) * (m_nDimensionCount-1));
				delete[] m_DimensionArray;
				m_DimensionArray = nullptr;
			}
			m_DimensionArray = pTemp;
			
			--m_nDimensionCount;
			SortDimensions();
			return;
		}
	}
}
void Entity::ClearDimensionSet(void)
{
	if (m_DimensionArray)
	{
		delete[] m_DimensionArray;
		m_DimensionArray = nullptr;
	}
	m_nDimensionCount = 0;
}
bool Entity::IsInDimension(uint a_uDimension)
{
	//see if the entry is in the set
	for (uint i = 0; i < m_nDimensionCount; i++)
	{
		if (m_DimensionArray[i] == a_uDimension)
			return true;
	}
	return false;
}
bool Entity::SharesDimension(Entity* const a_pOther)
{
	
	//special case: if there are no dimensions on either Entity
	//then they live in the special global dimension
	if (0 == m_nDimensionCount)
	{
		//if no spatial optimization all cases should fall here as every 
		//entity is by default, under the special global dimension only
		if(0 == a_pOther->m_nDimensionCount)
			return true;
	}

	//for each dimension on both Entities we check if there is a common dimension
	for (uint i = 0; i < m_nDimensionCount; ++i)
	{
		for (uint j = 0; j < a_pOther->m_nDimensionCount; j++)
		{
			if (m_DimensionArray[i] == a_pOther->m_DimensionArray[j])
				return true; //as soon as we find one we know they share dimensionality
		}
	}

	//could not find a common dimension
	return false;
}
bool Entity::IsColliding(Entity* const other)
{
	//if not in memory return
	if (!m_bInMemory || !other->m_bInMemory)
		return true;

	//if the entities are not living in the same dimension
	//they are not colliding
	if (!SharesDimension(other))
		return false;

	return m_pRigidBody->IsColliding(other->GetRigidBody());
}
void Entity::ClearCollisionList(void)
{
	m_pRigidBody->ClearCollidingList();
}
void Entity::SortDimensions(void)
{
	std::sort(m_DimensionArray, m_DimensionArray + m_nDimensionCount);
}

void Entity::Update(void)
{
}
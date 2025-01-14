#include "Entity.h"
std::vector<Entity*> Entity::m_entityList;
//  Accessors
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
	m_bSetAxis = true;
	m_pModel = nullptr;
	m_pRigidBody = nullptr;
	m_m4ToWorld = IDENTITY_M4;
	m_sUniqueID = "";
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
}
void Entity::Release(void)
{
	m_pModelMngr = nullptr;
	//it is not the job of the entity to release the model, 
	//it is for the mesh manager to do so.
	m_pModel = nullptr;
	SafeDelete(m_pRigidBody);
}
//The big 3
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
	m_pRigidBody = new RigidBody(m_pModel->GetVertexList()); //generate a rigid body
	m_bInMemory = true; //mark this entity as viable
	m_entityList.push_back(this);//add this object to the list of objects
}
Entity::Entity(Entity const& other)
{
	m_bInMemory = other.m_bInMemory;
	m_pModel = other.m_pModel;
	//generate a new rigid body we do not share the same rigid body as other
	m_pRigidBody = new RigidBody(m_pModel->GetVertexList()); 
	m_m4ToWorld = other.m_m4ToWorld;
	m_pModelMngr = other.m_pModelMngr;
	m_sUniqueID = other.m_sUniqueID;
	m_bSetAxis = other.m_bSetAxis;
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
	//Look for the ID, if found return the entity
	for each (Entity* entity in m_entityList)
	{
		if (entity->GetUniqueID() == a_sUniqueID)
			return entity;
	}
	//if not found return null
	return nullptr;
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
bool Entity::IsColliding(Entity* const other)
{
	//if not in memory return
	if (!m_bInMemory || !other->m_bInMemory)
		return true;

	return m_pRigidBody->IsColliding(other->GetRigidBody());
}
void Entity::Update(void)
{
	//get the count of entities created
	uint uSize = m_entityList.size();
	for (uint i = 0; i < uSize; i++)
	{
		RigidBody* pRB = m_entityList[i]->GetRigidBody();
		pRB->SetColorAABB(C_WHITE);
	}
	//check collision with all the objects in the list
	for (uint i = 0; i < uSize; i++)
	{
		for (uint j = i + 1; j < uSize; j++)
		{
			if (m_entityList[i]->IsColliding(m_entityList[j]))
			{
				RigidBody* pRB = m_entityList[i]->GetRigidBody();
				pRB->SetColorAABB(C_RED);
				pRB = m_entityList[j]->GetRigidBody();
				pRB->SetColorAABB(C_RED);
			}
		}
	}
}
#include "EntityManager.h"

//  EntityManager
EntityManager* EntityManager::m_pInstance = nullptr;
void EntityManager::Init(void)
{
	m_uEntityCount = 0;
	m_mEntityArray = nullptr;
}
void EntityManager::Release(void)
{
	for (uint uEntity = 0; uEntity < m_uEntityCount; ++uEntity)
	{
		Entity* pEntity = m_mEntityArray[uEntity];
		SafeDelete(pEntity);
	}
	m_uEntityCount = 0;
	m_mEntityArray = nullptr;
}
EntityManager* EntityManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new EntityManager();
	}
	return m_pInstance;
}
void EntityManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
int EntityManager::GetEntityIndex(String a_sUniqueID)
{
	//look one by one for the specified unique id
	for (uint uIndex = 0; uIndex < m_uEntityCount; ++uIndex)
	{
		if (a_sUniqueID == m_mEntityArray[uIndex]->GetUniqueID())
			return uIndex;
	}
	//if not found return -1
	return -1;
}
//Accessors
uint EntityManager::GetEntityCount(void) {	return m_uEntityCount; }
RTSG::Model* EntityManager::GetModel(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return nullptr;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->GetModel();
}
RTSG::Model* EntityManager::GetModel(String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetModel();
	}
	return nullptr;
}
RigidBody* EntityManager::GetRigidBody(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return nullptr;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->GetRigidBody();
}
RigidBody* EntityManager::GetRigidBody(String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetRigidBody();
	}
	return nullptr;
}
matrix4 EntityManager::GetModelMatrix(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return matrix4();

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->GetModelMatrix();
}
matrix4 EntityManager::GetModelMatrix(String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetModelMatrix();
	}
	return IDENTITY_M4;
}
void EntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->SetModelMatrix(a_m4ToWorld);
	}
}
void EntityManager::SetAxisVisibility(bool a_bVisibility, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->SetAxisVisible(a_bVisibility);
}
void EntityManager::SetAxisVisibility(bool a_bVisibility, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->SetAxisVisible(a_bVisibility);
	}
}
void EntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	m_mEntityArray[a_uIndex]->SetModelMatrix(a_m4ToWorld);
}
//The big 3
EntityManager::EntityManager(){Init();}
EntityManager::EntityManager(EntityManager const& a_pOther){ }
EntityManager& EntityManager::operator=(EntityManager const& a_pOther) { return *this; }
EntityManager::~EntityManager(){Release();};
// other methods
void EntityManager::Update(void)
{
	//Clear all collisions
	for (uint i = 0; i < m_uEntityCount; i++)
	{
		m_mEntityArray[i]->ClearCollisionList();
	}
	
	//check collisions
	for (uint i = 0; i < m_uEntityCount; i++)
	{
		for (uint j = i + 1; j < m_uEntityCount; j++)
		{
			//if objects are colliding resolve the collision
			if (m_mEntityArray[i]->IsColliding(m_mEntityArray[j]))
			{
				//TODO: Do something about the collision
			}
		}
		//Update each entity
		m_mEntityArray[i]->Update();
	}
}
void EntityManager::AddEntry(Entity* a_pEntity)
{
	//create a new temp array with one extra entry
	PEntity* tempArray = new PEntity[m_uEntityCount + 1];
	//start from 0 to the current count
	memcpy(tempArray, m_mEntityArray, sizeof(PEntity) * m_uEntityCount);
	tempArray[m_uEntityCount] = a_pEntity;

	//if there was an older array delete
	if (m_mEntityArray)
	{
		delete[] m_mEntityArray;
	}
	//make the member pointer the temp pointer
	m_mEntityArray = tempArray;
	//add one entity to the count
	++m_uEntityCount;
}
String EntityManager::AddEntity(RTSG::Model* a_pModel, String a_sUniqueID)
{
	//Create a temporal entity to store the object
	Entity* pTemp = new Entity(a_pModel, a_sUniqueID);
	//if I was able to generate it add it to the list
	if (pTemp->IsInitialized())
	{
		AddEntry(pTemp);
	}
	return pTemp->GetUniqueID();
}
String EntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	//Create a temporal entity to store the object
	Entity* pTemp = new Entity(a_sFileName, a_sUniqueID);
	//if I was able to generate it add it to the list
	if (pTemp->IsInitialized())
	{
		AddEntry(pTemp);
	}
	return pTemp->GetUniqueID();
}
void EntityManager::RemoveEntity(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	// if out of bounds choose the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	// if the entity is not the very last we swap it for the last one
	if (a_uIndex != m_uEntityCount - 1)
	{
		std::swap(m_mEntityArray[a_uIndex], m_mEntityArray[m_uEntityCount - 1]);
	}
	
	//and then pop the last one
	//create a new temp array with one less entry
	PEntity* tempArray = new PEntity[m_uEntityCount - 1];
	Entity* pEntity = m_mEntityArray[m_uEntityCount - 1];
	memcpy(tempArray, m_mEntityArray, sizeof(PEntity) * (m_uEntityCount - 1));
	SafeDelete(pEntity);
	//start from 0 to the current count
	//for (uint i = 0; i < m_uEntityCount - 1; ++i)
	//{
	//	tempArray[i] = m_mEntityArray[i];
	//}
	//if there was an older array delete
	if (m_mEntityArray)
	{
		delete[] m_mEntityArray;
	}
	//make the member pointer the temp pointer
	m_mEntityArray = tempArray;
	//add one entity to the count
	--m_uEntityCount;
}
void EntityManager::RemoveEntity(String a_sUniqueID)
{
	int nIndex = GetEntityIndex(a_sUniqueID);
	RemoveEntity((uint)nIndex);
}
String EntityManager::GetUniqueID(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return "";

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->GetUniqueID();
}
Entity* EntityManager::GetEntity(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return nullptr;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex];
}
void EntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{
	//if out of bounds will do it for all
	if (a_uIndex >= m_uEntityCount)
	{
		//add for each one in the entity list
		for (a_uIndex = 0; a_uIndex < m_uEntityCount; ++a_uIndex)
		{
			m_mEntityArray[a_uIndex]->AddToRenderList(a_bRigidBody);
		}
	}
	else //do it for the specified one
	{
		m_mEntityArray[a_uIndex]->AddToRenderList(a_bRigidBody);
	}
}
void EntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->AddToRenderList(a_bRigidBody);
	}
}
void EntityManager::AddDimension(uint a_uIndex, uint a_uDimension)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->AddDimension(a_uDimension);
}
void EntityManager::AddDimension(String a_sUniqueID, uint a_uDimension)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->AddDimension(a_uDimension);
	}
}
void EntityManager::RemoveDimension(uint a_uIndex, uint a_uDimension)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->RemoveDimension(a_uDimension);
}
void EntityManager::RemoveDimension(String a_sUniqueID, uint a_uDimension)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->RemoveDimension(a_uDimension);
	}
}
void EntityManager::ClearDimensionSetAll(void)
{
	for (uint i = 0; i < m_uEntityCount; ++i)
	{
		ClearDimensionSet(i);
	}
}
void EntityManager::ClearDimensionSet(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->ClearDimensionSet();
}
void EntityManager::ClearDimensionSet(String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->ClearDimensionSet();
	}
}
bool EntityManager::IsInDimension(uint a_uIndex, uint a_uDimension)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return false;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->IsInDimension(a_uDimension);
}
bool EntityManager::IsInDimension(String a_sUniqueID, uint a_uDimension)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->IsInDimension(a_uDimension);
	}
	return false;
}
bool EntityManager::SharesDimension(uint a_uIndex, Entity* const a_pOther)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return false;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->SharesDimension(a_pOther);
}
bool EntityManager::SharesDimension(String a_sUniqueID, Entity* const a_pOther)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->SharesDimension(a_pOther);
	}
	return false;
}
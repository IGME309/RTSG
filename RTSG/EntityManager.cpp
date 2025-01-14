#include "RTSG\Physics\EntityManager.h"
using namespace RTSG;
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
Model* EntityManager::GetModel(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return nullptr;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->GetModel();
}
Model* EntityManager::GetModel(String a_sUniqueID)
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
void EntityManager::SetRBVisibility(bool a_bVisibility, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return; 

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->SetRBVisible(a_bVisibility);
}
void EntityManager::SetRBVisibility(bool a_bVisibility, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->SetRBVisible(a_bVisibility);
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
				m_mEntityArray[i]->ResolveCollision(m_mEntityArray[j]);
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
String EntityManager::AddEntity(Model* a_pModel, String a_sUniqueID)
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
void EntityManager::AddEntityToRenderList(uint a_uIndex)
{
	//if out of bounds will do it for all
	if (a_uIndex >= m_uEntityCount)
	{
		//add for each one in the entity list
		for (a_uIndex = 0; a_uIndex < m_uEntityCount; ++a_uIndex)
		{
			m_mEntityArray[a_uIndex]->AddToRenderList();
		}
	}
	else //do it for the specified one
	{
		m_mEntityArray[a_uIndex]->AddToRenderList();
	}
}
void EntityManager::AddEntityToRenderList(String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->AddToRenderList();
	}
}
void EntityManager::AddSpace(uint a_uIndex, uint a_uSpace)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->AddSpace(a_uSpace);
}
void EntityManager::AddSpace(String a_sUniqueID, uint a_uSpace)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->AddSpace(a_uSpace);
	}
}
void EntityManager::RemoveSpace(uint a_uIndex, uint a_uSpace)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->RemoveSpace(a_uSpace);
}
void EntityManager::RemoveSpace(String a_sUniqueID, uint a_uSpace)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->RemoveSpace(a_uSpace);
	}
}
void EntityManager::ClearSpaceSetAll(void)
{
	for (uint i = 0; i < m_uEntityCount; ++i)
	{
		ClearSpaceSet(i);
	}
}
void EntityManager::ClearSpaceSet(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->ClearSpaceSet();
}
void EntityManager::ClearSpaceSet(String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->ClearSpaceSet();
	}
}
bool EntityManager::IsInSpace(uint a_uIndex, uint a_uSpace)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return false;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->IsInSpace(a_uSpace);
}
bool EntityManager::IsInSpace(String a_sUniqueID, uint a_uSpace)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->IsInSpace(a_uSpace);
	}
	return false;
}
bool EntityManager::SharesSpace(uint a_uIndex, Entity* const a_pOther)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return false;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->SharesSpace(a_pOther);
}
bool EntityManager::SharesSpace(String a_sUniqueID, Entity* const a_pOther)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->SharesSpace(a_pOther);
	}
	return false;
}
Solver* EntityManager::GetSolver(String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity exists return its solver
	if (pTemp)
		return pTemp->GetSolver();

	return nullptr;
}
Solver* EntityManager::GetSolver(uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return nullptr;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->GetSolver();
}

void EntityManager::SetNewSolver(Solver* a_pNewSolver, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity does not exists return
	if (pTemp)
		pTemp->SetNewSolver(a_pNewSolver);
	//if there is no such entity return with no changes
	return;
}
void EntityManager::SetNewSolver(Solver* a_pNewSolver, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	m_mEntityArray[a_uIndex]->SetNewSolver(a_pNewSolver);
}

void EntityManager::ApplyForce(vector3 a_v3Force, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity does not exists return
	if(pTemp)
		pTemp->ApplyForce(a_v3Force);
	return;
}
void EntityManager::ApplyForce(vector3 a_v3Force, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->ApplyForce(a_v3Force);
}
void EntityManager::SetPosition(vector3 a_v3Position, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity does not exists return
	if (pTemp)
	{
		pTemp->SetPosition(a_v3Position);
	}
	return;
}
void EntityManager::SetPosition(vector3 a_v3Position, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	m_mEntityArray[a_uIndex]->SetPosition(a_v3Position);

	return;
}
void EntityManager::SetMass(float a_fMass, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);
	//if the entity does not exists return
	if (pTemp)
	{
		pTemp->SetMass(a_fMass);
	}
	return;
}
void EntityManager::SetMass(float a_fMass, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	m_mEntityArray[a_uIndex]->SetMass(a_fMass);

	return;
}
void EntityManager::UsePhysicsSolver(bool a_bUse, String a_sUniqueID)
{
	//Get the entity
	Entity* pTemp = Entity::GetEntity(a_sUniqueID);

	//if the entity does not exists return
	if (pTemp)
		pTemp->UsePhysicsSolver(a_bUse);
	return;
}
void EntityManager::UsePhysicsSolver(bool a_bUse, uint a_uIndex)
{
	//if the list is empty return
	if (m_uEntityCount == 0)
		return;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_mEntityArray[a_uIndex]->UsePhysicsSolver(a_bUse);
}
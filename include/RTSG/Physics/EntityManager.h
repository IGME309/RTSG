/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __ENTITYMANAGER_H_
#define __ENTITYMANAGER_H_

#include "RTSG\Physics\Entity.h"

namespace RTSG
{

//System Class
class BTXDLL EntityManager
{
	typedef Entity* PEntity; //Entity Pointer
	uint m_uEntityCount = 0; //number of elements in the list
	PEntity* m_mEntityArray = nullptr; //array of Entity pointers
	static EntityManager* m_pInstance; // Singleton pointer
public:
	/*
	Usage: Gets the singleton pointer
	Arguments: ---
	Output: singleton pointer
	*/
	static EntityManager* GetInstance();
	/*
	Usage: Releases the content of the singleton
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Gets the index (from the list of entities) of the entity specified by UniqueID
	ARGUMENTS: String a_sUniqueID -> queried index
	OUTPUT: index from the list of entities, -1 if not found
	*/
	int GetEntityIndex(String a_sUniqueID);

	/*
	USAGE: Will add an entry to the list of entities
	ARGUMENTS:
	-	Entity* a_pEntity -> Entity to add
	OUTPUT: ---
	*/
	void AddEntry(Entity* a_pEntity);

	/*
	USAGE: Will add an entity to the list based on the provided model
	ARGUMENTS:
	-	Model* a_pModel -> Model to add
	-	String a_sUniqueID -> Name wanted as identifier, if not available will generate one
	OUTPUT: ---
	*/
	String AddEntity(Model* a_pModel, String a_sUniqueID = "NA");

	/*
	USAGE: Will add an entity to the list
	ARGUMENTS:
	-	String a_sFileName -> Name of the model to load
	-	String a_sUniqueID -> Name wanted as identifier, if not available will generate one
	OUTPUT: ---
	*/
	String AddEntity(String a_sFileName, String a_sUniqueID = "NA");
	/*
	USAGE: Deletes the Entity Specified by unique ID and removes it from the list
	ARGUMENTS: uint a_uIndex -> index of the queried entry, if < 0 asks for the last one added
	OUTPUT: ---
	*/
	void RemoveEntity(uint a_uIndex);
	/*
	USAGE: Deletes the Entity Specified by unique ID and removes it from the list
	ARGUMENTS: String a_sUniqueID -> Unique Identifier
	OUTPUT: ---
	*/
	void RemoveEntity(String a_sUniqueID);
	/*
	USAGE: Gets the uniqueID name of the entity indexed
	ARGUMENTS: uint a_uIndex = -1 -> index of the queried entry, if < 0 asks for the last one added
	OUTPUT: UniqueID of the entity, if the list is empty will return blank
	*/
	String GetUniqueID(uint a_uIndex = -1);
	/*
	USAGE: Gets the uniqueID name of the entity indexed
	ARGUMENTS: uint a_uIndex = -1 -> index of the queried entry, if < 0 asks for the last one added
	OUTPUT: UniqueID of the entity, if the list is empty will return blank
	*/
	Entity* GetEntity(uint a_uIndex = -1);
	/*
	USAGE: Will update the Entity manager
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Gets the model associated with this entity
	ARGUMENTS: uint a_uIndex = -1 -> index in the list of entities; if less than 0 it will add it to the last in the list
	OUTPUT: Model
	*/
	Model* GetModel(uint a_uIndex = -1);
	/*
	USAGE: Gets the model associated with this entity
	ARGUMENTS: String a_sUniqueID -> id of the queried entity
	OUTPUT: Model
	*/
	Model* GetModel(String a_sUniqueID);
	/*
	USAGE: Gets the Rigid Body associated with this entity
	ARGUMENTS: uint a_uIndex = -1 -> index in the list of entities; if less than 0 it will add it to the last in the list
	OUTPUT: Rigid Body
	*/
	RigidBody* GetRigidBody(uint a_uIndex = -1);
	/*
	USAGE: Gets the Rigid Body associated with this entity
	ARGUMENTS: String a_sUniqueID -> id of the queried entity
	OUTPUT: Rigid Body
	*/
	RigidBody* GetRigidBody(String a_sUniqueID);
	/*
	USAGE: Gets the model matrix associated with this entity
	ARGUMENTS: uint a_uIndex = -1 -> index in the list of entities; if less than 0 it will add it to the last in the list
	OUTPUT: model to world matrix
	*/
	matrix4 GetModelMatrix(uint a_uIndex = -1);
	/*
	USAGE: Gets the model matrix associated with this entity
	ARGUMENTS: String a_sUniqueID -> id of the queried entity
	OUTPUT: model to world matrix
	*/
	matrix4 GetModelMatrix(String a_sUniqueID);
	/*
	USAGE: Sets the model matrix associated to the entity specified in the ID
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> model matrix to set
	-	uint a_uIndex = -1 -> index in the list of entities; if less than 0 it will add it to the last in the list
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex = -1);
	/*
	USAGE: Sets the model matrix associated to the entity specified in the ID
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> model matrix to set
	-	String a_sUniqueID -> id of the queried entity
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID);
	/*
	USAGE: Sets the axis visibility associated to the entity specified in the ID
	ARGUMENTS: 
	-	bool a_bVisibility -> visibility of the axis
	-	uint a_uIndex = -1 -> index in the list of entities; if less than 0 it will add it to the last in the list
	OUTPUT: ---
	*/
	void SetAxisVisibility(bool a_bVisibility, uint a_uIndex = -1);
	/*
	USAGE: Sets the axis visibility associated to the entity specified in the ID
	ARGUMENTS:
	-	bool a_bVisibility -> visibility of the axis
	-	String a_sUniqueID -> id of the queried entity
	OUTPUT: ---
	*/
	void SetAxisVisibility(bool a_bVisibility, String a_sUniqueID);
	/*
	USAGE: Sets the RigidBody visibility associated to the entity specified in the ID
	ARGUMENTS:
	-	bool a_bVisibility -> visibility of the Rigid Body
	-	uint a_uIndex = -1 -> index in the list of entities; if less than 0 it will add it to the last in the list
	OUTPUT: ---
	*/
	void SetRBVisibility(bool a_bVisibility, uint a_uIndex = -1);
	/*
	USAGE: Sets the RigidBody visibility associated to the entity specified in the ID
	ARGUMENTS:
	-	bool a_bVisibility -> visibility of the Rigid Body
	-	String a_sUniqueID -> id of the queried entity
	OUTPUT: ---
	*/
	void SetRBVisibility(bool a_bVisibility, String a_sUniqueID);
	
	/*
	USAGE: Will add the specified entity to the render list
	ARGUMENTS:
	-	uint a_uIndex = -1 -> index (from the list) of the entity queried if < 0 will add all
	OUTPUT: ---
	*/
	void AddEntityToRenderList(uint a_uIndex = -1);
	/*
	USAGE: Will add the specified entity by uniqueID to the render list
	ARGUMENTS:
	-	String a_sUniqueID -> unique identifier of the entity queried
	OUTPUT: ---
	*/
	void AddEntityToRenderList(String a_sUniqueID);
	/*
	USAGE: Will set a space to the Entity
	ARGUMENTS:
	-	uint a_uIndex -> index (from the list) of the entity queried if < 0 will use the last one
	-	uint a_uDimension -> space to set
	OUTPUT: ---
	*/
	void AddSpace(uint a_uIndex, uint a_uSpace);
	/*
	USAGE: Will set a space to the Entity
	ARGUMENTS:
	-	String a_sUniqueID -> unique identifier of the entity queried
	-	uint a_uDimension -> space to set
	OUTPUT: ---
	*/
	void AddSpace(String a_sUniqueID, uint a_uSpace);
	/*
	USAGE: Will remove the entity from the specified space
	ARGUMENTS:
	-	uint a_uIndex -> index (from the list) of the entity queried if < 0 will use the last one
	-	uint a_uDimension -> space to remove
	OUTPUT: ---
	*/
	void RemoveSpace(uint a_uIndex, uint a_uSpace);
	/*
	USAGE: Will remove the entity from the specified space
	ARGUMENTS:
	-	String a_sUniqueID -> unique identifier of the entity queried
	-	uint a_uDimension -> space to remove
	OUTPUT: ---
	*/
	void RemoveSpace(String a_sUniqueID, uint a_uSpace);
	/*
	USAGE: will remove all spaces from all entities
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearSpaceSetAll(void);
	/*
	USAGE: will remove all spaces from entity
	ARGUMENTS: uint a_uIndex -> index (from the list) of the entity queried if < 0 will use the last one
	OUTPUT: ---
	*/
	void ClearSpaceSet(uint a_uIndex);
	/*
	USAGE: will remove all spaces from entity
	ARGUMENTS: String a_sUniqueID -> unique identifier of the entity queried
	OUTPUT: ---
	*/
	void ClearSpaceSet(String a_sUniqueID);
	/*
	USAGE: Will ask if the Entity is located in a particular space
	ARGUMENTS:
	-	uint a_uIndex -> index (from the list) of the entity queried if < 0 will use the last one
	-	uint a_uDimension -> space queried
	OUTPUT: result
	*/
	bool IsInSpace(uint a_uIndex, uint a_uSpace);
	/*
	USAGE: Will ask if the Entity is located in a particular space
	ARGUMENTS:
	-	String a_sUniqueID -> unique identifier of the entity queried
	-	uint a_uDimension -> space queried
	OUTPUT: result
	*/
	bool IsInSpace(String a_sUniqueID, uint a_uSpace);
	/*
	USAGE: Asks if this entity shares a space with the incoming one
	ARGUMENTS:
	-	uint a_uIndex -> index (from the list) of the entity queried if < 0 will use the last one
	-	Entity* const a_pOther -> queried entity
	OUTPUT: shares at least one space?
	*/
	bool SharesSpace(uint a_uIndex, Entity* const a_pOther);
	/*
	USAGE: Asks if this entity shares a space with the incoming one
	ARGUMENTS:
	-	String a_sUniqueID -> unique identifier of the entity queried
	-	Entity* const a_pOther -> queried entity
	OUTPUT: shares at least one space?
	*/
	bool SharesSpace(String a_sUniqueID, Entity* const a_pOther);
	/*
	USAGE: Will return the count of Entities in the system
	ARGUMENTS: ---
	OUTPUT: Entity count
	*/
	uint GetEntityCount(void);

	/*
	Usage: Gets the solver for the entity
	Arguments:
	-	String a_sUniqueID -> ID of the Entity
	Output: Solver
	*/
	Solver* GetSolver(String a_sUniqueID);

	/*
	Usage: Gets the solver for the entity
	Arguments: 
	-	uint a_uIndex = -1 -> ID of the Entity if < 0 last object added
	Output: Solver
	*/
	Solver* GetSolver(uint a_uIndex = -1);
	
	/*
	Usage: Sets a new solver for the entity, if the solver exists,
		   it released the previous one first
	Arguments:
	-	Solver* a_pNewSolver -> New Solver to Use
	-	String a_sUniqueID -> ID of the Entity
	Output: ---
	*/
	void SetNewSolver(Solver* a_pNewSolver, String a_sUniqueID);

	/*
	Usage: Sets a new solver for the entity, if the solver exists,
		   it released the previous one first
	Arguments: 
	-	Solver* a_pNewSolver -> New Solver to Use
	-	uint a_uIndex = -1 -> ID of the Entity if < 0 last object added
	Output: ---
	*/
	void SetNewSolver(Solver* a_pNewSolver, uint a_uIndex = -1);

	/*
	USAGE: applies a force to the specified object
	ARGUMENTS:
	-	vector3 a_v3Force -> force to apply
	-	String a_sUniqueID -> ID of the Entity
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force, String a_sUniqueID);
	/*
	USAGE: applies a force to the specified entity
	ARGUMENTS:
	-	vector3 a_v3Force -> force to apply
	-	uint a_uIndex = -1 -> ID of the Entity if < 0 last object added
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force, uint a_uIndex = -1);
	/*
	USAGE: Sets the position of the specified entity
	ARGUMENTS:
	-	vector3 a_v3Position -> position to set
	-	String a_sUniqueID -> ID of the Entity
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position, String a_sUniqueID);
	/*
	USAGE: Sets the position of the specified entity
	ARGUMENTS:
	-	vector3 a_v3Position -> position to set
	-	uint a_uIndex = -1 -> ID of the Entity if < 0 last object added
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position, uint a_uIndex = -1);
	/*
	USAGE: Sets the mass of the specified entity
	ARGUMENTS:
	-	float a_fMass -> mass to set
	-	String a_sUniqueID -> ID of the Entity
	OUTPUT: ---
	*/
	void SetMass(float a_fMass, String a_sUniqueID);
	/*
	USAGE: Sets the mass of the specified entity
	ARGUMENTS:
	-	float a_fMass -> mass to set
	-	uint a_uIndex = -1 -> ID of the Entity if < 0 last object added
	OUTPUT: ---
	*/
	void SetMass(float a_v3Mass, uint a_uIndex = -1);
	/*
	USAGE: Sets the using physics solver flag for the specified object
	ARGUMENTS:
	-	bool a_bUse -> Using physics?
	-	String a_sUniqueID -> ID of the Entity
	OUTPUT: ---
	*/
	void UsePhysicsSolver(bool a_bUse, String a_sUniqueID);
	/*
	USAGE: Sets the using physics solver flag for the specified object
	ARGUMENTS:
	-	bool a_bUse -> Using physics?
	-	uint a_uIndex = -1 -> ID of the Entity if < 0 last object added
	OUTPUT: ---
	*/
	void UsePhysicsSolver(bool a_bUse = true, uint a_uIndex = -1);
private:
	/*
	Usage: constructor
	Arguments: ---
	Output: class object instance
	*/
	EntityManager(void);
	/*
	Usage: copy constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	EntityManager(EntityManager const& a_pOther);
	/*
	Usage: copy assignment operator
	Arguments: class object to copy
	Output: ---
	*/
	EntityManager& operator=(EntityManager const& a_pOther);
	/*
	Usage: destructor
	Arguments: ---
	Output: ---
	*/
	~EntityManager(void);
	/*
	Usage: releases the allocated member pointers
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: initializes the singleton
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};//class

} //namespace STR

#endif //__MYENTITYMANAGER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
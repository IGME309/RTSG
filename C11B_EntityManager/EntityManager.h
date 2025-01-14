/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2023/10
----------------------------------------------*/
#ifndef __MYENTITYMANAGER_H_
#define __MYENTITYMANAGER_H_

#include "Entity.h"


//System Class
class EntityManager
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
	RTSG::Model* GetModel(uint a_uIndex = -1);
	/*
	USAGE: Gets the model associated with this entity
	ARGUMENTS: String a_sUniqueID -> id of the queried entity
	OUTPUT: Model
	*/
	RTSG::Model* GetModel(String a_sUniqueID);
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
	USAGE: Sets the model matrix associated to the entity specified in the ID
	ARGUMENTS:
	-	bool a_bVisibility -> visibility of the axis
	-	String a_sUniqueID -> id of the queried entity
	OUTPUT: ---
	*/
	void SetAxisVisibility(bool a_bVisibility, String a_sUniqueID);
	/*
	USAGE: Will add the specified entity to the render list
	ARGUMENTS:
	-	uint a_uIndex = -1 -> index (from the list) of the entity queried if < 0 will add all
	-	bool a_bRigidBody = false -> draw rigid body?
	OUTPUT: ---
	*/
	void AddEntityToRenderList(uint a_uIndex = -1, bool a_bRigidBody = false);
	/*
	USAGE: Will add the specified entity by uniqueID to the render list
	ARGUMENTS:
	-	String a_sUniqueID -> unique identifier of the entity queried
	-	bool a_bRigidBody = false -> draw rigid body?
	OUTPUT: ---
	*/
	void AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody = false);
	
	/*
	USAGE: Will return the count of Entities in the system
	ARGUMENTS: ---
	OUTPUT: Entity count
	*/
	uint GetEntityCount(void);

	
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

#endif //__MYENTITYMANAGER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
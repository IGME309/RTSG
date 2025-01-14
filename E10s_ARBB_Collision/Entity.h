/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2023/10
----------------------------------------------*/
#ifndef __MYENTITY_H_
#define __MYENTITY_H_

#include "RTSG\RTSG.h"
#include "RTSG\TypeDefs.h"
#include "RigidBody.h"


//System Class
class Entity
{
	bool m_bInMemory = false; //loaded flag
	bool m_bSetAxis = false; //render axis flag
	String m_sUniqueID = ""; //Unique identifier name

	RTSG::Model* m_pModel = nullptr; //Model associated with this Entity
	RigidBody* m_pRigidBody = nullptr; //Rigid Body associated with this Entity

	matrix4 m_m4ToWorld = IDENTITY_M4; //Model matrix associated with this Entity
	RTSG::ModelManager* m_pModelMngr = nullptr; //For rendering shapes

	static std::vector<Entity*> m_entityList; //a list of the unique ID's

public:
	/*
	Usage: Constructor that specifies the name attached to the Entity
	Arguments:
	-	String a_sFileName -> Name of the model to load
	-	String a_sUniqueID -> Name wanted as identifier, if not available will generate one
	Output: class object instance
	*/
	Entity(String a_sFileName, String a_sUniqueID = "NA");
	/*
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	Entity(Entity const& other);
	/*
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	Entity& operator=(Entity const& other);
	/*
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~Entity(void);
	/*
	Usage: Changes object contents for other object's
	Arguments: other -> object to swap content from
	Output: ---
	*/
	void Swap(Entity& other);
	/*
	USAGE: Gets the model matrix associated with this entity
	ARGUMENTS: ---
	OUTPUT: model to world matrix
	*/
	matrix4 GetModelMatrix(void);
	/*
	USAGE: Sets the model matrix associated with this entity
	ARGUMENTS: matrix4 a_m4ToWorld -> model matrix to set
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	/*
	USAGE: Gets the model associated with this entity
	ARGUMENTS: ---
	OUTPUT: Model
	*/
	RTSG::Model* GetModel(void);
	/*
	USAGE: Gets the Rigid Body associated with this entity
	ARGUMENTS: ---
	OUTPUT: Rigid Body
	*/
	RigidBody* GetRigidBody(void);
	/*
	USAGE: Will reply to the question, is the Entity Initialized?
	ARGUMENTS: ---
	OUTPUT: initialized?
	*/
	bool IsInitialized(void);
	/*
	USAGE: Adds the entity to the render list
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AddToRenderList(bool a_bDrawRigidBody = true);
	/*
	USAGE: Tells if this entity is colliding with the incoming one
	ARGUMENTS: Entity* const other -> inspected entity
	OUTPUT: are they colliding?
	*/
	bool IsColliding(Entity* const other);
	/*
	USAGE: Gets the Entity specified by unique ID, nullptr if not exists
	ARGUMENTS: String a_sUniqueID -> unique ID if the queried entity
	OUTPUT: Entity specified by unique ID, nullptr if not exists
	*/
	static Entity* GetEntity(String a_sUniqueID);
	/*
	USAGE: Will generate a unique id based on the name provided
	ARGUMENTS: String& a_sUniqueID -> desired name
	OUTPUT: will output though the argument
	*/
	void GenUniqueID(String& a_sUniqueID);
	/*
	USAGE: Gets the Unique ID name of this model
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	String GetUniqueID(void);
	/*
	USAGE: Sets the visibility of the axis of this Entity
	ARGUMENTS: bool a_bSetAxis = true -> axis visible?
	OUTPUT: ---
	*/
	void SetAxisVisible(bool a_bSetAxis = true);
	/*
	USAGE: Updates the Entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);

private:
	/*
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};//class


#endif //__MYENTITY_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
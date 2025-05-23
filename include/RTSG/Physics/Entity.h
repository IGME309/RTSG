/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "RTSG\Mesh\ModelManager.h"
#include "RTSG\Physics\RigidBody.h"
#include "RTSG\Physics\Solver.h"

namespace RTSG
{

//System Class
class BTXDLL Entity
{
	bool m_bInMemory = false; //loaded flag
	bool m_bAxisVisible = false; //render axis flag
	bool m_bRBVisible = false; //render RB flag
	String m_sUniqueID = ""; //Unique identifier name

	uint m_nSpaceCount = 0; //tells how many spaces this entity lives in
	uint* m_SpaceArray = nullptr; //Spaces on which this entity is located

	Model* m_pModel = nullptr; //Model associated with this Entity
	RigidBody* m_pRigidBody = nullptr; //Rigid Body associated with this Entity

	matrix4 m_m4ToWorld = IDENTITY_M4; //Model matrix associated with this Entity
	ModelManager* m_pModelMngr = nullptr; //For rendering shapes

	static std::map<String, Entity*> m_IDMap; //a map of the unique ID's

	bool m_bUsePhysicsSolver = false; //Indicates if we will use a physics solver 

	Solver* m_pSolver = nullptr; //Physics Solver

public:
	/*
	Usage: Constructor based on a Model pointer
	Arguments:
	-	Model* a_pModel -> Loaded Model to create an entity around
	-	String a_sUniqueID -> Name wanted as identifier, if not available will generate one
	Output: class object instance
	*/
	Entity(Model* a_pModel, String a_sUniqueID = "NA");

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
	Model* GetModel(void);
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
	void AddToRenderList(void);
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
	void SetAxisVisible(bool a_bVisible = true);
	/*
	USAGE: Sets the visibility of the RigidBody of this Entity
	ARGUMENTS: bool a_bSetAxis = true -> axis visible?
	OUTPUT: ---
	*/
	void SetRBVisible(bool a_bVisible = true);
	/*
	USAGE: Will set a space to the Entity
	ARGUMENTS: uint a_uSpace -> space to set
	OUTPUT: ---
	*/
	void AddSpace(uint a_uSpace);
	/*
	USAGE: Will remove the entity from the specified space
	ARGUMENTS: uint a_uSpace -> space to remove
	OUTPUT: ---
	*/
	void RemoveSpace(uint a_uSpace);
	/*
	USAGE: will remove all spaces from entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearSpaceSet(void);
	/*
	USAGE: Will ask if the Entity is located in a particular space
	ARGUMENTS: uint a_uSpace -> space queried
	OUTPUT: result
	*/
	bool IsInSpace(uint a_uSpace);
	/*
	USAGE: Asks if this entity shares a space with the incoming one
	ARGUMENTS: Entity* const a_pOther -> queried entity
	OUTPUT: shares at least one space?
	*/
	bool SharesSpace(Entity* const a_pOther);

	/*
	USAGE: Clears the collision list of this entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearCollisionList(void);

	/*
	USAGE: Will sort the array of spaces
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void SortSpaces(void);

	/*
	USAGE: Gets the array of rigid bodies pointer this one is colliding with
	ARGUMENTS: ---
	OUTPUT: list of colliding rigid bodies
	*/
	RigidBody::PRigidBody* GetColliderArray(void);
	
	/*
	USAGE: Returns the number of objects colliding with this one
	ARGUMENTS: ---
	OUTPUT: colliding count
	*/
	uint GetCollidingCount(void);

	/*
	USAGE: Asks this Entity if this is the rigid body that belogs to it
	ARGUMENTS: RigidBody* a_pRigidBody -> Queried Rigid Body
	OUTPUT: is this your rigid body?
	*/
	bool HasThisRigidBody(RigidBody* a_pRigidBody);

	/*
	USAGE: Asks the entity to resolve the collision with the incoming one
	ARGUMENTS: Entity* a_pOther -> Queried entity
	OUTPUT: ---
	*/
	void ResolveCollision(Entity* a_pOther);

	/*
	USAGE: Gets the solver applied to this Entity
	ARGUMENTS: ---
	OUTPUT: Solver applied
	*/
	Solver* GetSolver(void);
	/*
	USAGE: Applies a force to the solver
	ARGUMENTS: vector3 a_v3Force -> force to apply
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force);
	/*
	USAGE: Sets the position of the solver
	ARGUMENTS: vector3 a_v3Position -> position to set
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Gets the position of the solver
	ARGUMENTS: ---
	OUTPUT: position of the solver
	*/
	vector3 GetPosition(void);

	/*
	USAGE: Sets the velocity of the solver
	ARGUMENTS: vector3 a_v3Velocity -> velocity to set
	OUTPUT: ---
	*/
	void SetVelocity(vector3 a_v3Velocity);
	/*
	USAGE: Gets the velocity of the solver
	ARGUMENTS: ---
	OUTPUT: velocity of the solver
	*/
	vector3 GetVelocity(void);

	/*
	USAGE: Sets the mass of the solver
	ARGUMENTS: float a_fMass -> mass to set
	OUTPUT: ---
	*/
	void SetMass(float a_fMass);
	/*
	USAGE: Gets mass of the solver
	ARGUMENTS: ---
	OUTPUT: mass of the object
	*/
	float GetMass(void);

	/*
	USAGE: Updates the Entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Resolves using physics solver or not in the update
	ARGUMENTS: bool a_bUse = true -> using physics solver?
	OUTPUT: ---
	*/
	void UsePhysicsSolver(bool a_bUse = true);

	/*
	Usage: Sets a new solver for the entity, if the solver exists,
		   it released the previous one first
	Arguments: New Solver to Use
	Output: ---
	*/
	void SetNewSolver(Solver* a_pNewSolver);

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

  //EXPIMP_TEMPLATE template class BTXDLL std::vector<Entity>;
EXPIMP_TEMPLATE template class BTXDLL std::vector<Entity*>;

} //namespace Simplex

#endif //__MYENTITY_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
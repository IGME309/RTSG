/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2023/11
----------------------------------------------*/
#ifndef __SPACECLASS_H_
#define __SPACECLASS_H_

#include "RTSG\RTSG.h"
#include "RTSG\TypeDefs.h"

//System Class
class Space
{
	typedef Space* PNode; //This will be used for a pointer array of pointers
	static uint m_uNodeCount; //will store the number of nodes instantiated
	
	uint m_uID = 0; //Will store the current ID for this Space
	uint m_uLevel = 0; //Will store the current level of the Space (either 0 at root or 1 for subdv)
	uint m_uChildren = 0;// Number of children on the Space (only the root will have children)

	uint m_uSubX = 1;//Number of divisions in X
	uint m_uSubY = 1;//Number of divisions in Y
	uint m_uSubZ = 1;//Number of divisions in Z

	RTSG::RigidBody* m_pRigidBody = nullptr; //To display the Space and calculate intersections with entities
	PNode* m_pChild = nullptr;//Will store the addresses of the children of the current Space

	RTSG::ModelManager* m_pModelMngr = nullptr; //So we can draw boxes
	RTSG::EntityManager* m_pEntityMngr = nullptr; //So we can read the information for each entity
		
public:
	/*
	USAGE: Constructor for root only, will create an Space containing all Entities in the manager
	ARGUMENTS:
	- uint a_nSubdivisionsX -> Sets the number of subdivisions horizontally
	- uint a_nSubdivisionsY -> Sets the number of subdivisions vertically
	- uint a_nSubdivisionsZ -> Sets the number of subdivisions deeply
	OUTPUT: class object
	*/
	Space(uint a_nSubdivisionsX = 1, uint a_nSubdivisionsY = 1, uint a_nSubdivisionsZ = 1);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Space(void);

	/*
	USAGE: Gets the center of the Space in global scape
	ARGUMENTS: ---
	OUTPUT: Center of the Space in global space
	*/
	vector3 GetCenterGlobal(void);

	/*
	USAGE: Gets the min corner of the Space in global space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	vector3 GetMinGlobal(void);

	/*
	USAGE: Gets the max corner of the Space in global space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	vector3 GetMaxGlobal(void);

	/*
	USAGE: Gets the count of nodes existing
	ARGUMENTS: ---
	OUTPUT: Space count
	*/
	uint GetNodeCount(void);

	/*
	USAGE:	Asks if there is a collision with the Entity in the manager specified
			by its index
	ARGUMENTS:
	- int a_uRBIndex -> Index of the Entity in the Entity Manager
	OUTPUT: check of the collision
	*/
	bool IsColliding(uint a_uRBIndex);

	/*
	USAGE: Displays the Space volume specified by Space ID
	ARGUMENTS:
	- uint a_nIndex -> Space to be displayed.
	OUTPUT: ---
	*/
	void Display(uint a_nIndex);

	/*
	USAGE: Displays this Space volume in the color specified
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Display(void);

	/*
	USAGE: allocates 8 smaller nodes in the child list of this Space
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Subdivide(void);

	/*
	USAGE: Asks the Space if it does not contain any children (its a leaf)
	ARGUMENTS: ---
	OUTPUT: It contains no children
	*/
	bool IsLeaf(void);

	/*
	USAGE: Traverse the tree up to the leafs and sets the objects in them to the index
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AssignIDstoEntities(void);

private:
	/*
	USAGE: Constructor
	ARGUMENTS:
	- vector3 a_v3Center -> Center of the Space in global space
	- float a_fSize -> size of each side of the Space volume
	OUTPUT: class object
	*/
	Space(vector3 a_v3Center, vector3 a_v3Size);

	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	Space(Space const& other);

	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	Space& operator=(Space const& other);

	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);

	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- Space& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(Space& other);
};//class


#endif //__NODECLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */
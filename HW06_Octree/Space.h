/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2023/11
----------------------------------------------*/
#ifndef __SpaceCLASS_H_
#define __SpaceCLASS_H_

#include "RTSG\RTSG.h"
#include "RTSG\TypeDefs.h"

//System Class
class Node
{
	static uint m_uSpaceCount; //will store the number of Spaces instantiated
	static uint m_uMaxLevel;//will store the maximum level an octant can go to
	static uint m_uIdealEntityCount; //will tell how many Entities this object will contain ideally (may have more or less)

	uint m_uID = 0; //Will store the current ID for this Space
	uint m_uLevel = 0; //Will store the current level of the Space (either 0 at root or 1 for subdv)
	uint m_uChildren = 0;// Number of children on the Space (only the root will have children)
	
	RTSG::RigidBody* m_pRigidBody = nullptr; //To display the Space and calculate intersections with entities
	Node* m_pChild[8] = { nullptr };//Will store the addresses of the children of the current Space

	RTSG::ModelManager* m_pModelMngr = nullptr; //So we can draw boxes
	RTSG::EntityManager* m_pEntityMngr = nullptr; //So we can read the information for each entity
		
public:
	/*
	USAGE: Constructor for root only, will create an Space containing all Entities in the manager
	ARGUMENTS:
		- uint a_nMaxLevel = 2 -> Sets the maximum level of subdivision
		- uint nIdealEntityCount = 5 -> Sets the ideal level of objects per octant
	OUTPUT: class object
	*/
	Node(uint a_uMaxLevel = 2, uint a_uIdealEntityCount = 5);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Node(void);

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
	USAGE: Gets the count of Spaces existing
	ARGUMENTS: ---
	OUTPUT: Space count
	*/
	uint GetSpaceCount(void);

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
	USAGE: allocates 8 smaller Spaces in the child list of this Space
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
	Node(vector3 a_v3Center, vector3 a_v3Size);

	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	Node(Node const& other);

	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	Node& operator=(Node const& other);

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
	void Swap(Node& other);

	/*
	USAGE: Asks the Octant if it contains more than this many Rigid Bodies
	ARGUMENTS:
	- uint a_nEntities -> Number of Entities to query
	OUTPUT: It contains at least this many Entities
	*/
	bool ContainsAtLeast(uint a_nEntities);
};//class


#endif //__SpaceCLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */
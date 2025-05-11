/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2023/11
----------------------------------------------*/
#ifndef __NODECLASS_H_
#define __NODECLASS_H_

#include "RTSG\RTSG.h"
#include "RTSG\TypeDefs.h"

//System Class
class Node
{
	typedef Node* PNode; //This will be used for a pointer array of pointers
	static uint m_uNodes; //will store the number of nodes instantiated
	
	uint m_uID = 0; //Will store the current ID for this node
	uint m_uLevel = 0; //Will store the current level of the node (either 0 at root or 1 for subdv)
	uint m_uChildren = 0;// Number of children on the node (only the root will have children)
	uint m_uSubX = 1;//Number of divisions in X
	uint m_uSubY = 1;//Number of divisions in Y
	uint m_uSubZ = 1;//Number of divisions in Z
	RTSG::RigidBody* m_pRigidBody = nullptr; //To display the node and calculate intersections with entities
	Node* m_pParent = nullptr;// Will store the address of the parent of current node (root has no parent)
	PNode* m_pChild = nullptr;//Will store the addresses of the children of the current node

	RTSG::ModelManager* m_pModelMngr = nullptr; //So we can draw boxes
	RTSG::EntityManager* m_pEntityMngr = nullptr; //So we can read the information for each entity
		
public:
	/*
	USAGE: Constructor for root only, will create an node containing all Entities in the manager
	ARGUMENTS:
	- uint a_nSubdivisionsX -> Sets the number of subdivisions horizontally
	- uint a_nSubdivisionsY -> Sets the number of subdivisions vertically
	- uint a_nSubdivisionsZ -> Sets the number of subdivisions deeply
	OUTPUT: class object
	*/
	Node(uint a_nSubdivisionsX = 1, uint a_nSubdivisionsY = 1, uint a_nSubdivisionsZ = 1);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Node(void);

	/*
	USAGE: Gets the center of the node in global scape
	ARGUMENTS: ---
	OUTPUT: Center of the node in global space
	*/
	vector3 GetCenterGlobal(void);

	/*
	USAGE: Gets the min corner of the node in global space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	vector3 GetMinGlobal(void);

	/*
	USAGE: Gets the max corner of the node in global space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	vector3 GetMaxGlobal(void);

	/*
	USAGE:	Asks if there is a collision with the Entity in the manager specified
			by its index
	ARGUMENTS:
	- int a_uRBIndex -> Index of the Entity in the Entity Manager
	OUTPUT: check of the collision
	*/
	bool IsColliding(uint a_uRBIndex);

	/*
	USAGE: Displays the node volume specified by node ID
	ARGUMENTS:
	- uint a_nIndex -> node to be displayed.
	OUTPUT: ---
	*/
	void Display(uint a_nIndex);

	/*
	USAGE: Displays this node volume in the color specified
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Display(void);

	/*
	USAGE: allocates 8 smaller nodes in the child list of this node
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Subdivide(void);

	/*
	USAGE: returns the parent of the node
	ARGUMENTS: ---
	OUTPUT: node object (parent) nullptr if root
	*/
	Node* GetParent(void);

	/*
	USAGE: Asks the node if it does not contain any children (its a leaf)
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
	- vector3 a_v3Center -> Center of the node in global space
	- float a_fSize -> size of each side of the node volume
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
	- node& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(Node& other);
};//class


#endif //__NODECLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */
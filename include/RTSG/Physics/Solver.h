/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __SOLVER_H_
#define __SOLVER_H_

#include "RTSG\Physics\RigidBody.h"

namespace RTSG
{

class BTXDLL Solver
{
protected:
	vector3 m_v3Acceleration = ZERO_V3; //Acceleration of the Solver
	vector3 m_v3Position = ZERO_V3; //Position of the Solver
	vector3 m_v3Size = vector3(1.0f); //Size of the Solver
	vector3 m_v3Velocity = ZERO_V3; //Velocity of the Solver
	float m_fSeparationStrength = 0.04f; //Force that separates two objects colliding
	vector3 m_v3Gravity = vector3(0.0f, -0.035f, 0.0f);
	float m_fMass = 1.0f; //Mass of the solver
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: object instance
	*/
	Solver(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: object to copy
	OUTPUT: object instance
	*/
	Solver(Solver const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: object to copy
	OUTPUT: this instance
	*/
	Solver& operator=(Solver const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Solver(void);
	/*
	USAGE: Content Swap
	ARGUMENTS: object to swap content with
	OUTPUT: ---
	*/
	void Swap(Solver& other);

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
	USAGE: Sets the Size of the solver
	ARGUMENTS: vector3 a_v3Size -> position to set
	OUTPUT: ---
	*/
	void SetSize(vector3 a_v3Size);
	/*
	USAGE: Gets the size of the solver
	ARGUMENTS: ---
	OUTPUT: size of the solver
	*/
	vector3 GetSize(void);

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
	USAGE: Sets the gravity of the solver
	ARGUMENTS: vector3 a_v3Gravity -> gravity to set
	OUTPUT: ---
	*/
	void SetGravity(vector3 a_v3Gravity = vector3(0.0f, -0.035f, 0.0f));
	/*
	USAGE: Gets the gravity of the solver
	ARGUMENTS: ---
	OUTPUT: gravity of the solver
	*/
	vector3 GetGravity(void);

	/*
	USAGE: Sets the Strength two objects will take to separate themselves
	ARGUMENTS: float a_fStrength -> separation Strength
	OUTPUT: ---
	*/
	void SetSeparationStrength(float a_fStrength = 0.04f);
	/*
	USAGE: Gets the Strength two objects will take to separate themselves
	ARGUMENTS: ---
	OUTPUT: separation strength 
	*/
	float GetSeparationStrength(void);

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
	USAGE: Applies friction to the movement
	ARGUMENTS: float a_fFriction = 0.1f -> friction to apply negative friction gets minimized to 0.01f
	OUTPUT: ---
	*/
	virtual void ApplyFriction(float a_fFriction = 0.1f);
	/*
	USAGE: Applies a force to the solver
	ARGUMENTS: vector3 a_v3Force -> Force to apply
	OUTPUT: ---
	*/
	virtual void ApplyForce(vector3 a_v3Force);
	/*
	USAGE: Updates the Solver
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void);
	/*
	USAGE: Resolve the collision between two solvers
	ARGUMENTS: Solver* a_pOther -> other solver to resolve collision with
	OUTPUT: ---
	*/
	virtual void ResolveCollision(Solver* a_pOther);
protected:
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

EXPIMP_TEMPLATE template class BTXDLL std::vector<Solver>;
EXPIMP_TEMPLATE template class BTXDLL std::vector<Solver*>;

} //namespace Simplex

#endif //__SOLVER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
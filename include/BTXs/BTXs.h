/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __BTXSFRAMEWORK_H_
#define __BTXSFRAMEWORK_H_

#pragma warning( disable : 4251 )
#include <vector>

// Include the GL extension Wrangler
#include <GL\glew.h>
#include <GL\wglew.h>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\matrix_decompose.hpp>

#ifdef EXP_STLs
#	define BTXsDLL __declspec(dllexport)
#else
#	define BTXsDLL __declspec(dllimport)
#endif

namespace BTXs
{
	typedef unsigned int uint;
	typedef std::string String;
	typedef glm::vec2 vector2;
	typedef glm::vec3 vector3;
	typedef glm::vec4 vector4;
	typedef glm::mat3 matrix3;
	typedef glm::mat4 matrix4;
	typedef glm::quat quaternion;

	enum eCAMERAMODE
	{
		CAM_PERSP = 0,
		CAM_ORTHO_X = 1,
		CAM_ORTHO_Y = 2,
		CAM_ORTHO_Z = 3,
	};

	enum eSATResults
	{
		SAT_NONE = 0,

		SAT_AX,
		SAT_AY,
		SAT_AZ,

		SAT_BX,
		SAT_BY,
		SAT_BZ,

		SAT_AXxBX,
		SAT_AXxBY,
		SAT_AXxBZ,

		SAT_AYxBX,
		SAT_AYxBY,
		SAT_AYxBZ,

		SAT_AZxBX,
		SAT_AZxBY,
		SAT_AZxBZ,
	};

	/*
	USAGE: Generates triangles that form the desired shape
	ARGUMENTS:
		-	float a_fRadius -> radius
		-	float a_fHeight -> how tall is the mesh
		-	int a_nSubdivisions -> divisions of the cap
	OUTPUT: cloud of points of the mesh, each 3 will make a face
	*/
	BTXsDLL std::vector<vector3> GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions);
	/*
	USAGE: Generates triangles that form the desired shape
	ARGUMENTS:
	-	float a_fRadius -> radius
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions on the cap
	OUTPUT: cloud of points of the mesh, each 3 will make a face
	*/
	BTXsDLL std::vector<vector3> GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions);
	
	/*
	USAGE: Generates triangles that form the desired shape
	ARGUMENTS:
	-	float a_fOuterRadius -> outer radius
	-	float a_fInnerRadius -> inner radius
	-	float a_fHeight -> how tall is the mesh
	-	int a_nSubdivisions -> divisions on the cap
	OUTPUT: cloud of points of the mesh, each 3 will make a face
	*/
	BTXsDLL std::vector<vector3> GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions);

	/*
		USAGE: Generates a torus mesh
		ARGUMENTS:
		-	float a_fOuterRadius -> Outer radius
		-	float a_fInnerRadius -> Inner Radius
		-	int a_nSubdivisionHeight -> divisions vertical
		-	int a_nSubdivisionAxis -> divisions along the roundness of the mesh
		OUTPUT: ---
		*/
	BTXsDLL std::vector<vector3> GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsHeight, int a_nSubdivisionsAxis);

	/*
		USAGE: Generates a Sphere mesh
		ARGUMENTS:
		-	float a_fRadius -> radius of the sphere
		-	int a_nSubdivisions -> Number of divisions, 12 recommended
		OUTPUT: ---
		*/
	BTXsDLL std::vector<vector3> GenerateSphere(float a_fRadius, int a_nSubdivisions);

	/*
		USAGE: Generates a line Sphere mesh
		ARGUMENTS:
		-	float a_fRadius -> radius of the sphere
		-	int a_nSubdivisions -> Number of divisions, 5 recommended
		OUTPUT: --- icosahedron
		NOTES: Based on Giovanni Aleman's method
		*/
	BTXsDLL std::vector<vector3> GenerateIcosahedron(float a_fRadius, int a_nSubdivisions);

	/*
	USAGE: Generates a unit size star mesh
	ARGUMENTS:
	-	uint a_uSubdivisions -> points of the star
	-	float fRadius1 = 1.0f -> radius of the outer points
	-	float fRadius2 = 0.5f -> radius of the inner points
	-	vector3 a_v3Color = C_WHITE -> color of the shape
	OUTPUT: ---
	*/
	BTXsDLL std::vector<vector3> GenerateStar(uint a_uSubdivisions, float fRadius1, float fRadius2);


	/*
	USAGE: Generates a Helix (Spring)
	ARGUMENTS:
	-	uint a_uSubdivisions -> points of the circular part of the spring and divisions of the circumference
	-	float fRadius1 = 1.0f -> radius of the circular part
	-	float fRadius2 = 0.5f -> distance from the center of the world to the center of each circle
	-   uint a_nLenght = 2, Number of connected toruses.
	-	vector3 a_v3Color = C_WHITE -> color of the shape
	OUTPUT: ---
	*/
	BTXsDLL std::vector<vector3> GenerateHelix(uint a_uSubdivisions = 12, float a_fRadius1 = 1.0f, float a_fRadius2 = 0.5f, uint a_nLenght = 2);

	/*
		USAGE: Will calculate the Separation Axis Test returning what was the separation axis
		ARGUMENTS:
		-	matrix4 mToWorldA -> Matrix of object A
		-	vector3 v3HalfWidthA -> Halfwidth of object A
		-	vector3 v3CenterGlobalA -> Center in global space of object A
			matrix4 mToWorldB -> Matrix of object B
			vector3 v3HalfWidthB -> Halfwidth of object B
			vector3 v3CenterGlobalB -> Center in global space of object B
		OUTPUT: eSATResults as its uint value
		*/
	BTXsDLL eSATResults ComputeSAT(matrix4 mToWorldA, vector3 v3HalfWidthA, vector3 v3CenterGlobalA,
		matrix4 mToWorldB, vector3 v3HalfWidthB, vector3 v3CenterGlobalB);
} //namespace BTXs


#endif //__BTXSFRAMEWORK_H_
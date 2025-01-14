/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __MYCAMERACLASS_H_
#define __MYCAMERACLASS_H_

#include "RTSG\RTSG.h"
#include "RTSG\TypeDefs.h"

class Camera
{
	vector3 m_v3Position = vector3(0.0f, 0.0f, 10.0f); //Where my camera is located
	vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f); //What I'm looking at
	vector3 m_v3Up = vector3(0.0f, 1.0f, 0.0f); //What is up

	vector3 m_v3Forward = vector3(0.0f, 0.0f,-1.0f); //View vector
	vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f); //where my head is pointing up
	vector3 m_v3Rightward = vector3(0.0f, 1.0f, 0.0f); //What is to my right
	
	matrix4 m_m4View; //View matrix
	matrix4 m_m4Projection; //Projection Matrix

	bool m_bPerspective = true;//if false, it will be orthographic

	float m_fFOV = 45.0f; //Field of View
	vector2 m_v2ScreenSize = vector2(1280.0f, 720.0f); //Width and Height of the screen
	vector2 m_v2NearFarPlane = vector2(0.001f, 1000.0f); //How near or far I can see
	vector2 m_v2HorizontalView = vector2(-5.0f, 5.0f); //How much I can see horizontally in ortho
	vector2 m_v2VerticalView = vector2(-5.0f, 5.0f); //How much I can see vertically in ortho
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: the class object
	*/
	Camera();

	/*
	USAGE: constructor
	ARGUMENTS:
	-	vector3 a_v3Position -> Where my camera is located
	-	vector3 a_v3Target -> What I'm looking at
	-	vector3 a_v3Upward -> What is up
	OUTPUT: ---
	*/
	Camera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);

	/*
	USAGE: Copy constructor
	ARGUMENTS: MyCamera const& other -> object to copy
	OUTPUT: ---
	*/
	Camera(Camera const& other);

	/*
	USAGE: Copy Assignment operator
	ARGUMENTS: MyCamera const& other -> object to copy
	OUTPUT: ---
	*/
	Camera& operator=(Camera const& other);

	/*
	USAGE: Initialize the class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);

	/*
	USAGE: Release pointers in the class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE: swap the content with an incoming object
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Swap(Camera& other);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Camera(void);

	/*
	USAGE: Sets the position of the camera
	ARGUMENTS: vector3 a_v3Position -> Position where we want the camera to be
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);

	/*
	USAGE: Gets the position of the camera
	ARGUMENTS: ---
	OUTPUT: position of the camera
	*/
	vector3 GetPosition(void);

	/*
	USAGE: Sets the position of the camera
	ARGUMENTS: vector3 a_v3Target -> What we want the camera to look at
	OUTPUT: ---
	*/
	void SetTarget(vector3 a_v3Target);

	/*
	USAGE: Gets the position of the camera
	ARGUMENTS: ---
	OUTPUT: position of the camera
	*/
	vector3 GetTarget(void);

	/*
	USAGE: Sets the position of the camera
	ARGUMENTS: vector3 a_v3Up -> What up means in the world
	OUTPUT: ---
	*/
	void SetUp(vector3 a_v3Up);

	/*
	USAGE: Gets the position of the camera
	ARGUMENTS: ---
	OUTPUT: position of the camera
	*/
	vector3 GetUp(void);

	/*
	USAGE: Gets the projection matrix of the camera
	ARGUMENTS: ---
	OUTPUT: projection matrix of the camera
	*/
	matrix4 GetProjectionMatrix(void);

	/*
	USAGE: Gets the view matrix of the camera
	ARGUMENTS: ---
	OUTPUT: view matrix of the camera
	*/
	matrix4 GetViewMatrix(void);

	/*
	USAGE: Resets the camera to default values
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ResetCamera(void);

	/*
	USAGE: Set the position target and up of the camera at once
	ARGUMENTS:
	-	vector3 a_v3Position -> Where my camera is located
	-	vector3 a_v3Target -> What I'm looking at
	-	vector3 a_v3Upward -> What is up
	OUTPUT: ---
	*/
	void SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward = AXIS_Y);

	/*
	USAGE: Calculate what the camera should be looking at with the values of position target and up
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateViewMatrix(void);

	/*
	USAGE: Calculate how the camera sees the world
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateProjectionMatrix(void);

	/*
	USAGE: Check if using a perspective camera
	ARGUMENTS: ---
	OUTPUT: True if Perspective, false if Orthographic
	*/
	bool GetPerspectiveFlag();
	/*
	USAGE: Set the use of perspective or orthographic projection
	ARGUMENTS: bool a_bFlag -> true for Perspective, false for ortho
	OUTPUT: ---
	*/
	void SetPerspectiveFlag(bool a_bFlag);

	/*
	USAGE: Gets the Field Of View proportion 
	ARGUMENTS: ---
	OUTPUT: FOV (1 is completelly squared)
	*/
	float GetFOV(void);
	/*
	USAGE: Sets the Field Of View proportion 
	ARGUMENTS: float a_v2Input -> Field of view (normally between 45-90) in degrees
	OUTPUT: ---
	*/
	void SetFOV(float a_fInput);

	/*
	USAGE: Gets the dimentions of the screen
	ARGUMENTS: ---
	OUTPUT: Horizontal and Vertical values of the screen
	*/
	vector2 GetScreenSize(void);
	/*
	USAGE: Sets the values of the screen size
	ARGUMENTS: vector2 a_v2Input -> Horizontal and vertical values
	OUTPUT: ---
	*/
	void SetScreenSize(vector2 a_v2Input);

	/*
	USAGE: Gets how close and far away the camera can see
	ARGUMENTS: ---
	OUTPUT: Near Far planes
	*/
	vector2 GetNearFarPlanes(void);
	/*
	USAGE: Sets how close and far away the camera can see
	ARGUMENTS: vector2 a_v2Input -> near and far values
	OUTPUT: ---
	*/
	void SetNearFarPlanes(vector2 a_v2Input);

	/*
	USAGE: Gets how much to the left and right an Ortho camera can see
	ARGUMENTS: ---
	OUTPUT: Left and Right
	*/
	vector2 GetHorizontalView(void);
	/*
	USAGE: Sets how much to the left and right an ortho projection can see
	ARGUMENTS: vector2 a_v2Input -> Left and Right
	OUTPUT: ---
	*/
	void SetHorizontalView(vector2 a_v2Input);

	/*
	USAGE: Gets how much to the Down and Up an Ortho camera can see
	ARGUMENTS: ---
	OUTPUT: Down and Up
	*/
	vector2 GetVerticalView(void);
	/*
	USAGE: Sets how much to the Down and Up an ortho projection can see
	ARGUMENTS: vector2 a_v2Input -> Down and Up
	OUTPUT: ---
	*/
	void SetVerticalview(vector2 a_v2Input);



};

#endif //__MYCAMERACLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */
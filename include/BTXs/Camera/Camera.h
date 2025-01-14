/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __CAMERASCLASS_H_
#define __CAMERASCLASS_H_

#include "BTXs\BTXs.h"

namespace BTXs
{
	//Camera Class
	class BTXsDLL Camera
	{
	protected:
		bool m_bFPS = true; //If set to false will behave like a flight simulator camera

		eCAMERAMODE m_nMode = eCAMERAMODE::CAM_PERSP; //Sets the mode the camera will display

		float m_fFOV = 45.0f; //Field of View
		float m_fWidth = 1280.0f; //Width of the screen
		float m_fHeight = 720.0f; //Height of the screen

		vector2 m_v2NearFar = vector2(0.001f, 1000.0f); //Near and Far planes

		vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f); //Where my camera is located
		vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f); //What the camera is looking at
		vector3 m_v3Above = vector3(0.0f, 1.0f, 0.0f); //What is above the camera position

		vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f); //Line of sight
		vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f); //Up line
		vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f); //side line

		vector3 m_v3PitchYawRoll = vector3(0.0f); //Orientation in Euler

		matrix4 m_m4Projection = matrix4(1.0f); //Projection Matrix
		matrix4 m_m4View = matrix4(1.0f); //View matrix

	public:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT: class object
		*/
		Camera(void);

		/*
		USAGE: Constructor with parameters
		ARGUMENTS:
		-	vector3 a_v3Position -> Where my camera is located
		-	vector3 a_v3Target -> What I'm looking at
		-	vector3 a_v3Upward -> What is up
		OUTPUT: ---
		*/
		Camera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);

		/*
		USAGE: Copy Constructor
		ARGUMENTS: Camera const& other -> object to copy
		OUTPUT: ---
		*/
		Camera(Camera const& other);

		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS: Camera const& other -> object to copy
		OUTPUT: ---
		*/
		Camera& operator=(Camera const& other);

		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~Camera(void);

		/*
		USAGE: Gets the View matrix from the camera
		ARGUMENTS: ---
		OUTPUT: view matrix
		*/
		matrix4 GetViewMatrix(void);

		/*
		USAGE: Gets the Projection matrix from the camera
		ARGUMENTS: ---
		OUTPUT: projection matrix
		*/
		matrix4 GetProjectionMatrix(void);

		/*
		USAGE: Gets the ModelViewProjection matrix from the camera
		ARGUMENTS: matrix4 a_m4ModelToWorld -> model matrix to evaluate
		OUTPUT: ModelViewProjection matrix
		*/
		matrix4 GetMVP(matrix4 a_m4ModelToWorld);

		/*
		USAGE: Gets the ViewProjection matrix from the camera
		ARGUMENTS: ---
		OUTPUT: View projection matrix
		*/
		matrix4 GetVP(void);

		/*
		USAGE:  Gets the position of the camera
		ARGUMENTS: ---
		OUTPUT: position of the camera
		*/
		vector3 GetPosition(void);

		/*
		USAGE:  Gets the forward vector of the camera
		ARGUMENTS: ---
		OUTPUT: forward vector of the camera
		*/
		vector3 GetForward(void);

		/*
		USAGE:  Gets the upward vector of the camera
		ARGUMENTS: ---
		OUTPUT: upward vector of the camera
		*/
		vector3 GetUpward(void);

		/*
		USAGE:  Gets the sidewards vector of the camera
		ARGUMENTS: ---
		OUTPUT: rightward vector of the camera
		*/
		vector3 GetRightward(void);

		/*
		USAGE:  Sets the Forward vector of the camera
		ARGUMENTS: vector3 a_v3Input -> input vector
		OUTPUT: ---
		*/
		void SetForward(vector3 a_v3Input);

		/*
		USAGE:  Sets the Upward vector of the camera
		ARGUMENTS: vector3 a_v3Input -> input vector
		OUTPUT: ---
		*/
		void SetUpward(vector3 a_v3Input);

		/*
		USAGE:  Sets the Forward vector of the camera
		ARGUMENTS: vector3 a_v3Input -> input vector
		OUTPUT: ---
		*/
		void SetRightward(vector3 a_v3Input);

		/*
		USAGE: Changes the near and far planes
		ARGUMENTS:
		-	float a_fNear -> near clipping plane
		-	float a_fFar -> far clipping plane
		OUTPUT:
		*/
		void SetNearFarPlanes(float a_fNear, float a_fFar);

		/*
		USAGE: Calculates the projection based on the camera values
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CalculateProjection(void);

		/*
		USAGE: Calculates the view based on the camera values
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CalculateView(void);

		/*
		USAGE: Set Field of View
		ARGUMENTS: input field of view
		OUTPUT: ---
		*/
		void SetFOV(float a_fFOV);

		/*
		USAGE: Sets the camera at the specified position
		ARGUMENTS: vector3 a_v3Position -> input
		OUTPUT: ---
		*/
		void SetPosition(vector3 a_v3Position);

		/*
		USAGE: Sets the target of the camera to the specified position
		ARGUMENTS: vector3 a_vTarget -> point to look at
		OUTPUT: ---
		*/
		void SetTarget(vector3 a_v3Target);

		/*
		USAGE: Sets the camera at the specified position and target
		ARGUMENTS:
		-	vector3 a_v3Position -> position of the camera
		-	vector3 a_v3Target -> target to look at
		-	vector3 a_v3Upward -> what up means
		OUTPUT:
		*/
		void SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);

		/*
		USAGE: Translates the camera forward or backward
		ARGUMENTS: float a_fDistance = 0.1f -> amount of movement
		OUTPUT: ---
		*/
		void MoveForward(float a_fDistance = 0.1f);

		/*
		USAGE: Translates the camera Upward or downward
		ARGUMENTS: float a_fDistance = 0.1f -> amount of movement
		OUTPUT: ---
		*/
		void MoveVertical(float a_fDistance = 0.1f);

		/*
		USAGE: Translates the camera right or left
		ARGUMENTS: float a_fDistance = 0.1f -> amount of movement
		OUTPUT: ---
		*/
		void MoveSideways(float a_fDistance = 0.1f);

		/*
		USAGE: Rotates the camera Pitch
		ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
		OUTPUT: ---
		*/
		void ChangePitch(float a_fDegree = 0.001f);

		/*
		USAGE: Rotates the camera Yaw
		ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
		OUTPUT: ---
		*/
		void ChangeYaw(float a_fDegree = 0.001f);

		/*
		USAGE: Rotates the camera Roll
		ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
		OUTPUT: ---
		*/
		void ChangeRoll(float a_fDegree = 0.001f);

		/*
		USAGE: Sets the camera in First Person Shooter mode, if false it will work like an aircraft
		ARGUMENTS: float a_fDegree = 0.01f -> degree of rotation
		OUTPUT: ---
		*/
		void SetFPS(bool a_bFPS = true);

		/*
		USAGE: Sets the camera in Perspective mode, if false it will work as an orthographic camera
		ARGUMENTS: BTO_CAMERAMODE a_nMode = BTO_CAMERAMODE::CAM_PERSP -> mode to set
		OUTPUT: ---
		*/
		void SetCameraMode(eCAMERAMODE a_nMode = eCAMERAMODE::CAM_PERSP);

		/*
		USAGE: Returns the current value for the camera mode
		ARGUMENTS: ---
		OUTPUT: mode of the camera
		*/
		eCAMERAMODE GetCameraMode(void);

		/*
		USAGE: Resets the value of the camera
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void ResetCamera(void);

	protected:
		/*
		USAGE: Releases the object from memory
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);

		/*
		USAGE: Initialize the object's fields
		ARGUMENTS:
		-	vector3 a_v3Position -> position of the camera
		-	vector3 a_v3Target -> what we are looking at
		-	vector3 a_v3Upward -> what is up
		OUTPUT: ---
		*/
		void Init(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);

		/*
		USAGE: Swaps the contents of the object with another object's content
		ARGUMENTS:
		OUTPUT: ---
		*/
		void Swap(Camera& other);

		/*
		USAGE: Sets the resolution of the window for projection calculations
		ARGUMENTS: vector2 a_v2WidhtHeight vector containing width and height (in that order)
		OUTPUT: ---
		*/
		void SetWidthAndHeightOfDisplay(vector2 a_v2WidhtHeight);
	};

}//namespace BTX

#endif //__CAMERASCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2023/09
----------------------------------------------*/
#ifndef __APPLICATIONCLASS_H_
#define __APPLICATIONCLASS_H_

#include "RTSG\RTSG.h"
#include "RTSG\TypeDefs.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"

#include "imgui\ImGuiObject.h"

#include "SolverExt.h"

class Application
{
private:
	String m_sToPrint = "Hi there, hello!";
	String m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	static ImGuiObject gui; //GUI object

	uint m_uRenderCallCount = 0; //count of render calls per frame

	vector3 m_v3Mouse = vector3(); //position of the mouse in the window
	bool m_bFPC = false;// First Person Camera flag
	bool m_bArcBall = false;// Arcball flag
	quaternion m_qArcBall; //ArcBall quaternion

	vector4 m_v4ClearColor; //Color of the scene
	bool m_bRunning = false; //Is app running?

	sf::Window* m_pWindow = nullptr; //SFML window

	RTSG::SystemSingleton* m_pSystem = nullptr; //Singleton of the system
	RTSG::ModelManager* m_pModelMngr = nullptr; //Mesh Manager
	RTSG::CameraManager* m_pCameraMngr = nullptr; //Singleton for the camera manager
	RTSG::EntityManager* m_pEntityMngr = nullptr; //Singleton for the Entities

	bool m_bFocused = true; //is the window focused?
	float m_fMovementSpeed = 0.1f; //how fast the camera will move
	bool m_bModifier = false; //is shift pressed?

public:
#pragma region Constructor / Run / Destructor
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	Application();
	
	/*
	USAGE: Initializes the window and rendering context
	ARGUMENTS:
	-	String a_sApplicationName -> Name of the window if blank will use project Name
	-	int size -> formated size, relate to BTX_RESOLUTIONS
	-	bool a_bFullscreen = false -> is the window fullscreen?
	-	bool a_bBorderless = false -> is the window borderless?
	OUTPUT: ---
	*/
	void Init(String a_sApplicationName = "", int a_uSize = RTSG::eBTX_RESOLUTIONS::RES_C_1280x720_16x9_HD,
		bool a_bFullscreen = false, bool a_bBorderless = false);
	
	/*
	USAGE: Initializes the window and rendering context
	ARGUMENTS:
	-	String a_sApplicationName = "" -> Name of the window if blank will use project Name
	-	uint a_nWidth -> Window Width
	-	uint a_nHeight -> Window Height
	-	bool a_bFullscreen -> is the window fullscreen?
	-	bool a_bBorderless -> is the window borderless?
	OUTPUT: ---
	*/
	void Init(String a_sApplicationName, uint a_uWidth, uint a_uHeight, bool a_bFullscreen, bool a_bBorderless);
	
	/*
	USAGE: Runs the main loop of this class DO NOT OVERRIDE
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Run(void);
	
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Application(void);
#pragma endregion

private:
#pragma region Initialization / Release
	/*
	USAGE: Initialize the window
	ARGUMENTS: String a_sWindowName = "GLFW" -> Window name
	OUTPUT: ---
	*/
	void InitWindow(String a_sWindowName = "Application");
	
	/*
	USAGE: Initializes user specific variables, this is executed right after InitWindow,
	the purpose of this member function is to initialize member variables specific for this project.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitVariables(void);
	
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReadConfig(void);
	
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void WriteConfig(void);
	
	/*
	USAGE: Releases the application
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
#pragma endregion

#pragma region Main Loop
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Display(void);
	
	/*
	USAGE: Clears the OpenGL screen by the specified color
	ARGUMENTS: vector4 a_v4ClearColor = vector4(-1.0f) -> Color to clear the screen with
	OUTPUT: ---
	*/
	void ClearScreen(vector4 a_v4ClearColor = vector4(-1.0f));
#pragma endregion

#pragma region Application Controls
	/*
	USAGE: Manage constant keyboard state
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyboard(void);
	
	/*
	USAGE: Manage constant keyboard state
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ArcBall(float a_fSensitivity = 0.1f);
	
	/*
	USAGE: Manages the rotation of the camera a_fSpeed is a factor of change
	ARGUMENTS: float a_fSpeed = 0.005f
	OUTPUT: ---
	*/
	void CameraRotation(float a_fSpeed = 0.005f);
#pragma endregion

#pragma region Process Events
	/*
	USAGE: Resizes the window
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Reshape(void);
	
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyPressed(sf::Event a_event);
	
	/*
	USAGE: Manage the response of key releases
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyReleased(sf::Event a_event);
	
	/*
	USAGE: Manage the response of mouse movement
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouseMovement(sf::Event a_event);
	
	/*
	USAGE: Manage the response of mouse key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMousePressed(sf::Event a_event);
	
	/*
	USAGE: Manage the response of mouse key release
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouseReleased(sf::Event a_event);
	
	/*
	USAGE: Manage the response of mouse scrolling
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouseScroll(sf::Event a_event);
#pragma endregion

#pragma region GUI
	/*
	USAGE: Initialize gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitIMGUI(void);
	
	/*
	USAGE: Draw gui elements
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void DrawGUI(void);
	
	/*
	USAGE: //release gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ShutdownGUI(void);
	
	/*
	USAGE: Render gui lists
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void RenderDrawLists(ImDrawData* draw_data);
	
	/*
	USAGE: Creates fonts for gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	bool CreateFontsTexture(void);
	
	/*
	USAGE: Create OpenGL resources for gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	bool CreateDeviceObjects(void);
	
	/*
	USAGE: creates a new frame for gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void NewFrame(void);
#pragma endregion

#pragma region The Rule of Three
	/*
	USAGE: copy constructor, private so it does not let object copy
	ARGUMENTS: GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	Application(Application const& input);
	
	/*
	USAGE: copy assignment, private so it does not let object copy
	ARGUMENTS: GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	Application& operator=(Application const& input);

#pragma endregion
};

#endif //__APPLICATIONCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
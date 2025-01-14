#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Load a model for example with complex models
	m_pSteve = new RTSG::Model("Minecraft\\Steve.obj");
	m_pCreeper = new RTSG::Model("Minecraft\\Creeper.obj");
	
	//create a new camera
	m_pCamera = new Camera();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	//CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//View variables:
	vector3 v3Position(0.0f, 2.0f, 3.0f);//Where the camera is
	vector3 v3Target(0.0f, 2.0f, 0.0f);//What the camera is looking at
	vector3 v3Up(0.0f, 1.0f, 0.0f);//What is upwards for the camera
	m_pCamera->SetPositionTargetAndUpward(v3Position, v3Target, v3Up);

	static uint uClock = m_pSystem->GenClock();//Clock to count
	static float fTimer = 0.0f;//Timer to keep track
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);//Time since last call to this clock
	fTimer += fDeltaTime;//Append the delta to the timer
	//fTimer will increment as seconds increment
	
	//Projection Variables:
	bool bPerspective = true;
	float fFOV = 90.0f;
	vector2 v2NearFar = vector2(0.0001f, 1000.0f);
	vector2 v2ScreenSize = vector2(m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight());
	vector2 v2LeftRight = vector2(-2.2f, 2.2f);
	vector2 v2DownUp = vector2(-2.2f, 2.2f);

	//Send values to the camera
	m_pCamera->SetPerspectiveFlag(bPerspective);
	m_pCamera->SetFOV(fFOV);
	m_pCamera->SetScreenSize(v2ScreenSize);
	m_pCamera->SetNearFarPlanes(v2NearFar);
	m_pCamera->SetHorizontalView(v2LeftRight);
	m_pCamera->SetVerticalview(v2DownUp);
		
	//Render the models with the specified View and Projections
	matrix4 m4View = m_pCamera->GetViewMatrix();
	matrix4 m4Projection = m_pCamera->GetProjectionMatrix();

	m_pSteve->Render(m4Projection, m4View, matrix4());
	m_pCreeper->Render(m4Projection, m4View, glm::translate(matrix4(), vector3(-0.5f, 0.0f, -1.0f)));

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();
		
	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release the models
	SafeDelete(m_pSteve);
	SafeDelete(m_pCreeper);

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}
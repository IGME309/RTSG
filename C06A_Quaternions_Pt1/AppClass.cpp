#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//initializing the model
	/*
	* Different than in the video-lecture models dont render themselves,
	* they now require the Model manager to render, so we load the model and
	* then we add them to the manager
	*/
	m_pModel = new RTSG::Model("Minecraft\\Steve.obj");
	m_pModelMngr->AddModel(m_pModel);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1);

	//Get a timer
	static uint uClock = m_pSystem->GenClock();
	float fTimer = m_pSystem->GetTimeSinceStart(uClock);
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);

	matrix4 m4OrientX = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.x), vector3(1.0f, 0.0f, 0.0f));
	matrix4 m4OrientY = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.y), vector3(0.0f, 1.0f, 0.0f));
	matrix4 m4OrientZ = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.z), vector3(0.0f, 0.0f, 1.0f));

	matrix4 m4Orientation = m4OrientX * m4OrientY * m4OrientZ;
	m_m4Creeper = m4Orientation;

	//example on how even a quaternion if generated though Euler will have Gimbal Lock
	//vector3 v3Temp(glm::radians(m_v3Orientation.x), glm::radians(m_v3Orientation.y), glm::radians(m_v3Orientation.z));
	//m_m4Steve = RTSG::ToMatrix4(quaternion(vector3(v3Temp)));
	
	//Attach the model matrix that takes me from the world coordinate system
	m_pModelMngr->AddModelToRenderList(m_pModel, m_m4Creeper);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

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
	//Release Model
	//As we attached the model to the model manager it will release that model for us

	//release GUI
	ShutdownGUI();
}
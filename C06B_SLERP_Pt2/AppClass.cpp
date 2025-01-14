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
	m_pModel = new RTSG::Model("Minecraft\\Creeper.obj");
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

	//Change the orientation from quaternion to matrix form to use it in shaders
	quaternion q1;
	quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(0.0f, 0.0f, 1.0f));
	float fPercentage = RTSG::MapValue(fTimer, 0.0f, 5.0f, 0.0f, 1.0f);
	quaternion qSLERP = glm::mix(q1, q2, fPercentage);
	m_m4Creeper = glm::toMat4(qSLERP);
	
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
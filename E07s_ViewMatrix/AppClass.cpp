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
	m_pModel = new RTSG::Model("Minecraft\\Steve.obj");
	
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
	
	static uint uClock = m_pSystem->GenClock();//Clock to count
	static float fTimer = 0.0f;//Timer to keep track
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);//Time since last call to this clock
	fTimer += fDeltaTime;//Append the delta to the timer
	//fTimer will increment equally as seconds increment

	//Camera position
	static vector3 v3Position(0.0f, 0.0f, 10.0f); //Setting the initial position
	v3Position += vector3(0.0f, 0.0f, fTimer * -0.1f); //It will move a 10th of a second
	m_pCamera->SetPosition(v3Position);

	//Camera position
	static float fAngle = 0.0f; //setting the angle
	m_pCamera->SetPosition(v3Position);//Setting the Position
	m_pCamera->SetTarget(v3Position + vector3(0.0f, 0.0f, -1.0f));//Setting the Target
	
	//Setting what up means in the world
	m_pCamera->SetUp(vector3(glm::cos(glm::radians(fAngle)), glm::sin(glm::radians(fAngle)), 0.0f));
	fAngle += fTimer * 5.0f;

	//Render the model in the specified positions
	matrix4 m4Model;
	matrix4 m4View = m_pCamera->GetViewMatrix();
	matrix4 m4Projection = m_pCamera->GetProjectionMatrix();
	m_pModel->Render(m4Projection, m4View, m4Model);

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
	//Release the model
	SafeDelete(m_pModel);

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}
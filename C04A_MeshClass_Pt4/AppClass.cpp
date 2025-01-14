#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	m_pMesh1 = new Mesh();
	m_pMesh1->GenerateCube(1.0f, C_PURPLE);

	m_pMesh2 = new Mesh();
	m_pMesh2->GenerateCube(1.0f, C_YELLOW);
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
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4Model = RTSG::ToMatrix4(m_qArcBall);
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	m_pMesh1->Render(m4Projection, m4View, m4Model);
	m_pMesh2->Render(m4Projection, m4View, glm::translate(IDENTITY_M4, vector3(2.0f)));

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

	SafeDelete(m_pMesh1);
	SafeDelete(m_pMesh2);

	//release GUI
	ShutdownGUI();
}
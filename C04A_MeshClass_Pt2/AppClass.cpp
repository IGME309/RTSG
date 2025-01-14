#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 5.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	m_pMesh1 = new Mesh();

	m_pMesh1->AddVertexPosition(vector3(0.0f, 0.0f, 0.0f));
	m_pMesh1->AddVertexPosition(vector3(1.0f, 0.0f, 0.0f));
	m_pMesh1->AddVertexPosition(vector3(0.0f, 1.0f, 0.0f));

	m_pMesh1->AddVertexColor(RTSG::C_RED);
	m_pMesh1->AddVertexColor(RTSG::C_GREEN);
	m_pMesh1->AddVertexColor(RTSG::C_BLUE);

	m_pMesh1->CompileOpenGL3X();
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

	//release GUI
	ShutdownGUI();
}
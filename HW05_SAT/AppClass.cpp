#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	m_pModelMngr = ModelManager::GetInstance();

	//creeper
	m_sCreeper = m_pModelMngr->LoadModel("Minecraft\\Creeper.obj");
	m_pCreeperRB = new MyRigidBody(m_pModelMngr->GetVertexList(m_sCreeper));

	//steve
	m_sSteve = m_pModelMngr->LoadModel("Minecraft\\Steve.obj");
	m_pSteveRB = new MyRigidBody(m_pModelMngr->GetVertexList(m_sSteve));
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Set model matrix to the creeper
	matrix4 m4Creeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	m_pCreeperRB->SetModelMatrix(m4Creeper);
	m_pModelMngr->AddAxisToRenderList(m4Creeper);

	//Set model matrix to Steve
	matrix4 m4Steve = glm::translate(vector3(2.25f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	m_pSteveRB->SetModelMatrix(m4Steve);
	m_pModelMngr->AddAxisToRenderList(m4Steve);

	bool bColliding = m_pCreeperRB->IsColliding(m_pSteveRB);

	m_pModelMngr->AddModelToRenderList(m_sCreeper, m4Creeper);
	m_pCreeperRB->AddToRenderList();

	m_pModelMngr->AddModelToRenderList(m_sSteve, m4Steve);
	m_pSteveRB->AddToRenderList();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	matrix4 m4Model = ToMatrix4(m_qArcBall);//model matrix

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
	//release GUI
	ShutdownGUI();
}
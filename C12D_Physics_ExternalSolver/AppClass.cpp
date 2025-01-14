#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 15.0f, 100.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Models to load
	uint uCount = 1000;
#ifndef DEBUG
	uCount = 2500;
#endif // DEBUG
	//Message for the App
	m_sToPrint = std::to_string(uCount) + " objects!";
	//Create the objects and position them inside of a random position in a sphere
	for (uint i = 0; i < uCount; i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube");//Add cube entities
		m_pEntityMngr->UsePhysicsSolver();

		//No need to release solver as that is handled in the entity itself
		SolverExt* pSolver = new SolverExt();
		m_pEntityMngr->SetNewSolver(pSolver);

		vector3 v3Position = vector3(glm::sphericalRand(30.0f));//make a position
		m_pEntityMngr->SetModelMatrix(glm::translate(v3Position), -1);//place the last one
		
		//m_pEntityMngr->SetMass(0.5f);
	}
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
	
	matrix4 m4Model = RTSG::ToMatrix4(m_qArcBall);//model matrix

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
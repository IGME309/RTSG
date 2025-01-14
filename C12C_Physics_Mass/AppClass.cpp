#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 15.0f, 30.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Create Steve
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_pEntityMngr->UsePhysicsSolver();

	//Gravity Force
	vector3 v3Gravity = vector3(0.0f, -0.035f, 0.0f);
	float fSeparationStrenght = 0.04f;
	
	//Make a new custom solver
	RTSG::Solver* pSolver = new RTSG::Solver();
	pSolver->SetGravity(v3Gravity);
	pSolver->SetSeparationStrength(fSeparationStrenght);
	m_pEntityMngr->SetNewSolver(pSolver);

	for (int i = 0; i < 100; i++)
	{
		//Create cubes
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i));
		m_pEntityMngr->UsePhysicsSolver();		

		//Make a new custom solver
		pSolver = new RTSG::Solver();
		pSolver->SetGravity(v3Gravity);
		pSolver->SetSeparationStrength(fSeparationStrenght);
		m_pEntityMngr->SetNewSolver(pSolver);

		//This needs to be last as if you dont set the model matrix after assigning
		//the new solver it will not know about the matrix
		vector3 v3Position = vector3(glm::sphericalRand(12.0f));
		v3Position.y = 0.0f;
		matrix4 m4Position = glm::translate(v3Position);

		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));//either this or the 2 below

		//m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(i) / 50.0f));
		//m_pEntityMngr->SetMass(i / 50.0f);
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
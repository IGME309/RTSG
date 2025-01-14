#include "AppClass.h"
void Application::InitVariables(void)
{
	//Message for the App
	m_sToPrint = "This are two objects, not only one!";
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 10.0f), vector3(), AXIS_Y);//Set Camera position
	
	//Model to load
	m_sModel = "SphereCube.obj";
	//Load said model
	m_pModelMngr->LoadModel(m_sModel);
	//Create a new Rigid Body
	m_pRB = new RigidBody();

	//Initialize Rigid Body
	m_pRB->SetCenterGlobal(vector3(0.0f, 0.0f, 0.0f));
	m_pRB->SetHalfWidth(vector3(3.0f, 5.0f, 1.0f));
	m_pRB->SetRadius(5.0f);
}
void Application::Update(void)
{
	m_pSystem->Update();//Update the system
	ArcBall();//Is the arcball active?
	CameraRotation(); //Is the first person camera active?

	//Add the model matrix to the RB
	m_pRB->SetModelMatrix(OrientByArcball());

	//Add the Rigid Body to the render List
	m_pRB->AddToRenderList();

	//Add the Model to the render list
	m_pModelMngr->AddModelToRenderList(m_sModel, OrientByArcball());
		
	m_pEntityMngr->Update(); //Update Entity Manager
	m_pEntityMngr->AddEntityToRenderList(-1); //Add objects to render list
}
void Application::Display(void)
{
	ClearScreen(); // Clear the screen
	m_pModelMngr->AddSkyboxToRenderList(); // draw a skybox
	m_uRenderCallCount = m_pModelMngr->Render(); //render list call
	m_pModelMngr->ClearRenderList(); //clear the render list
	DrawGUI(); //draw gui
	m_pWindow->display(); //end the frame (swap front and back buffers)
}
void Application::Release(void)
{
	//Release the memory of the Rigid Body
	SafeDelete(m_pRB);

	ShutdownGUI();//release GUI
}
#include "AppClass.h"
void Application::InitVariables(void)
{
	//Message for the App
	m_sToPrint = "This are two objects, not only one!";
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 10.0f), vector3(), AXIS_Y);//Set Camera position
	
	//Models to load
	m_sModel1 = "Minecraft\\Creeper.obj";
	m_sModel2 = "Minecraft\\Steve.obj";
	//Load said models
	m_pModelMngr->LoadModel(m_sModel1);
	m_pModelMngr->LoadModel(m_sModel2);
	//Create new Rigid Bodies
	m_pRB1 = new RigidBody(m_pModelMngr->GetVertexList(m_sModel1));
	m_pRB2 = new RigidBody(m_pModelMngr->GetVertexList(m_sModel2));
}
void Application::Update(void)
{
	m_pSystem->Update();//Update the system
	ArcBall();//Is the arcball active?
	CameraRotation(); //Is the first person camera active?

	//Translate models to new position
	matrix4 m4Model1 = glm::translate(m_v3Position);
	matrix4 m4Model2 = glm::translate(vector3(1.5f, 0.0f, 0.0f));

	//Add the model matrix to the RB
	m_pRB1->SetModelMatrix(m4Model1);
	m_pRB2->SetModelMatrix(m4Model2);

	//Reset the Colors
	m_pRB1->SetColorAABB(C_WHITE);
	m_pRB2->SetColorAABB(C_WHITE);
	m_sToPrint = "They are not colliding";
	
	//check if they are colliding
	if (m_pRB1->IsColliding(m_pRB2))
	{
		//No need to check if RB2 is colliding with RB1
		//as both would yield the same result
		m_pRB1->SetColorAABB(C_RED);
		m_pRB2->SetColorAABB(C_RED);
		m_sToPrint = "They ARE colliding!!!!!!!!";
	}

	//Add the Rigid Body to the render List
	m_pRB1->AddToRenderList();
	m_pRB2->AddToRenderList();

	//Add the Model to the render list
	m_pModelMngr->AddModelToRenderList(m_sModel1, m4Model1);
	m_pModelMngr->AddModelToRenderList(m_sModel2, m4Model2);
		
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
	SafeDelete(m_pRB1);
	SafeDelete(m_pRB2);

	ShutdownGUI();//release GUI
}
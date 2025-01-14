#include "AppClass.h"
void Application::InitVariables(void)
{
	//Message for the App
	m_sToPrint = "The ARBB should be around the OBB";
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 5.0f), vector3(), AXIS_Y);//Set Camera position
	
	//Models to load
	m_pEntity1 = new Entity("Minecraft\\Creeper.obj", "Creeper");
	m_pEntity2 = new Entity("Minecraft\\Steve.obj", "Steve");
}
void Application::Update(void)
{
	m_pSystem->Update();//Update the system
	ArcBall();//Is the arcball active?
	CameraRotation(); //Is the first person camera active?

	//Translate models to new position
	matrix4 m4Model1 = glm::translate(m_v3Position) * OrientByArcball();
	matrix4 m4Model2 = glm::translate(vector3(1.5f, 0.0f, 0.0f));

	//Add the model matrix to the entities
	m_pEntity1->SetModelMatrix(m4Model1);
	m_pEntity2->SetModelMatrix(m4Model2);

	//Update the entities
	m_pEntity1->Update();
	m_pEntity2->Update();

	//Render the models
	m_pEntity1->AddToRenderList(true);
	m_pEntity2->AddToRenderList(true);
		


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
	SafeDelete(m_pEntity1);
	SafeDelete(m_pEntity2);

	ShutdownGUI();//release GUI
}
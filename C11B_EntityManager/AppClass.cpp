#include "AppClass.h"
void Application::InitVariables(void)
{
	//Message for the App
	m_sToPrint = "Entity Manager handles all objects";
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 1.5f, 5.0f), vector3(0.0f, 1.25f, 4.0f), AXIS_Y);//Set Camera position
	
	//Models to load
	m_pMyEntityMngr = EntityManager::GetInstance();
	m_pMyEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper");
	m_pMyEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_pMyEntityMngr->AddEntity("Minecraft\\Zombie.obj", "Zombie");
	m_pMyEntityMngr->AddEntity("Minecraft\\Cow.obj", "Cow");
	m_pMyEntityMngr->AddEntity("Minecraft\\Pig.obj", "Pig");
}
void Application::Update(void)
{
	m_pSystem->Update();//Update the system
	ArcBall();//Is the arcball active?
	CameraRotation(); //Is the first person camera active?

	//Translate models to new position
	matrix4 m4Model1 = glm::translate(m_v3Position) * OrientByArcball();
	
	//Add the model matrix to the entities
	m_pMyEntityMngr->SetModelMatrix(m4Model1, "Steve");
	m_pMyEntityMngr->SetModelMatrix(glm::translate(vector3(-1.5f, 0.0f, 0.0f)), "Creeper");
	m_pMyEntityMngr->SetModelMatrix(glm::translate(vector3(1.5f, 0.0f, 0.0f)), "Zombie");
	m_pMyEntityMngr->SetModelMatrix(glm::translate(vector3(2.5f, 0.0f, 0.0f)), "Cow");
	m_pMyEntityMngr->SetModelMatrix(glm::translate(vector3(-2.5f, 0.0f, 0.0f)), "Pig");
	m_pMyEntityMngr->Update();
	
	//Render the entieies
	//-1 means all of the entities
	m_pMyEntityMngr->AddEntityToRenderList(-1, true);
	

	m_pEntityMngr->Update(); //Update Entity Manager (the one in the system)
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
	m_pMyEntityMngr->ReleaseInstance();

	ShutdownGUI();//release GUI
}
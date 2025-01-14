#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

#pragma region THINGS I DONT NEED IN THIS APP	
	//The camera is set / we do not use it in this application
	//RTSG::vector3 v3Position(0.0f, 0.0f, 5.0f);
	//RTSG::vector3 v3Target(RTSG::ZERO_V3);
	//RTSG::vector3 v3Upward(RTSG::AXIS_Y);
	//m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
#pragma endregion

	//We don't have to recompile the shader each time (its outside the program now)
	//so we use the shader manager to just give us the ID of the shader we want to use
	RTSG::ShaderManager* pShaderManager = RTSG::ShaderManager::GetInstance(); //get the singleton
	shaderProgramID = pShaderManager->GetShaderID("Minimal"); //use it to load the Basic shader
	glUseProgram(shaderProgramID); //we tell OpenGL this is the shader we want to use

	//The following is the same as above in a single line... it is gross don't do it!
	//glUseProgram(RTSG::ShaderManager::GetInstance()->GetShaderID("Minimal"));
	
	//Make a new array of vertices, each 3 will be a 3D point for the triangle
	GLfloat positions[] = { -0.25f, -0.25f, 0.0f, 0.25f, -0.25f, 0.0f, 0.0f, 0.25f, 0.0f };
	
	//Reminder: the following allocate memory for the VAO (the stage of the play) and the VBO
	//(The actors of the scene) in the graphics card

	// Create Vertex Array Object
	glGenVertexArrays(1, &vao);//allocate one new stage in the graphics card and give me the address
	glBindVertexArray(vao);//make that address the active one

	// Create Vertex Buffer Object
	glGenBuffers(1, &vbo);//allocate one new space for an actor and give me the address
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//make that actor the active one
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);//tell it how to use it

	// Get the Attribute of position from the shader program, this basically constructs the triangle
	GLint positionBufferID = glGetAttribLocation(shaderProgramID, "positionBuffer");
	glEnableVertexAttribArray(positionBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

#pragma region THINGS I DONT NEED IN THIS APP
	//Is the arcball active? / Not used in this application
	//ArcBall();

	//Is the first person camera active? / not used in this application
	//CameraRotation();

	//Update Entity Manager / not used in this application
	//m_pEntityMngr->Update();

	//Add objects to render list / not used in this application
	//m_pEntityMngr->AddEntityToRenderList(-1, true);
#pragma endregion
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
#pragma region THINGS I DONT NEED IN THIS APP
	// draw a skybox / not used in this application
	//m_pModelMngr->AddSkyboxToRenderList();

	//render list call / not used in this application
	//m_uRenderCallCount = m_pModelMngr->Render(); 

	//clear the render list / not used in this application
	//m_pModelMngr->ClearRenderList();
#pragma endregion

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
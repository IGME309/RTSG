#include "AppClass.h"

void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	//We don't have to recompile the shader each time (its outside the program now)
	//so we use the shader manager to just give us the ID of the shader we want to use
	RTSG::ShaderManager* pShaderManager = RTSG::ShaderManager::GetInstance(); //get the singleton
	shaderProgramID = pShaderManager->GetShaderID("Minimal"); //use it to load the Basic shader
	glUseProgram(shaderProgramID); //we tell OpenGL this is the shader we want to use
	
	//Make a new array of vertices, each 3 will be a 3D point for the triangle
	//GLfloat positions[] = { -0.25f, -0.25f, 0.0f, 0.25f, -0.25f, 0.0f, 0.0f, 0.25f, 0.0f };

	//We will do it instead through a list of vertices (3D vectors / vector3s)
	int vertexCount = 3;
	int vectorSize = 3;
	std::vector<vector3> vertexPosition;
	vertexPosition.push_back(vector3(-0.25f, -0.25f, 0.0f));
	vertexPosition.push_back(vector3( 0.25f, -0.25f, 0.0f));
	vertexPosition.push_back(vector3( 0.0f, 0.25f, 0.0f));

	//Example of creating an offset when the object is CREATED
	for (uint i = 0; i < vertexCount; i++)
		vertexPosition[i].x += 2.5f;

	matrix4 m4Model;
	//Modify the diagonal, which is the scale
	m4Model[0][0] *= 0.25f;
	m4Model[1][1] *= 0.25f;
	m4Model[2][2] *= 0.25f;

	for (uint i = 0; i < vertexCount; i++)
		vertexPosition[i] = m4Model * vector4(vertexPosition[i], 1.0f);
		
	//Reminder: the following allocate memory for the VAO (the stage of the play) and the VBO
	//(The actors of the scene) in the graphics card

	// Create Vertex Array Object
	glGenVertexArrays(1, &vao);//allocate one new stage in the graphics card and give me the address
	glBindVertexArray(vao);//make that address the active one

	// Create Vertex Buffer Object
	glGenBuffers(1, &vbo);//allocate one new space for an actor and give me the address
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//make that actor the active one
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);//tell it how to use it
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vectorSize * sizeof(vector3), &vertexPosition[0], GL_STATIC_DRAW);

	// Get the Attribute of position from the shader program, this basically constructs the triangle
	GLint positionBufferID = glGetAttribLocation(shaderProgramID, "positionBuffer");
	glEnableVertexAttribArray(positionBufferID);
	glVertexAttribPointer(0, vectorSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
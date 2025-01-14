#include "AppClass.h"

void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	//We don't have to recompile the shader each time (its outside the program now)
	//so we use the shader manager to just give us the ID of the shader we want to use
	RTSG::ShaderManager* pShaderManager = RTSG::ShaderManager::GetInstance(); //get the singleton
	shaderProgramID = pShaderManager->GetShaderID("Basic"); //use it to load the Basic shader
	glUseProgram(shaderProgramID); //we tell OpenGL this is the shader we want to use
	
	//We will do it instead through a list of vertices (3D vectors / vector3s)
	int vertexCount = 3;
	int vectorSize = 3;
	
	//we have a container for positions
	std::vector<vector3> vertexPosition;
	vertexPosition.push_back(vector3(-0.25f, -0.25f, 0.0f));
	vertexPosition.push_back(vector3( 0.25f, -0.25f, 0.0f));
	vertexPosition.push_back(vector3( 0.0f, 0.25f, 0.0f));

	//we have a container for colors
	std::vector<vector3> vertexColor;
	vertexColor.push_back(RTSG::C_RED);
	vertexColor.push_back(RTSG::C_GREEN);
	vertexColor.push_back(RTSG::C_BLUE);

	//we have a container for everything going in order PosColPosColPosCol
	std::vector<vector3> vertexList;
	for (uint i = 0; i < vertexCount; i++)
	{
		vertexList.push_back(vertexPosition[i]);
		vertexList.push_back(vertexColor[i]);
	}
		
	//Reminder: the following allocate memory for the VAO (the stage of the play) and the VBO
	//(The actors of the scene) in the graphics card

	// Create Vertex Array Object
	glGenVertexArrays(1, &vao);//allocate one new stage in the graphics card and give me the address
	glBindVertexArray(vao);//make that address the active one

	// Create Vertex Buffer Object
	glGenBuffers(1, &vbo);//allocate one new space for an actor and give me the address
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//make that actor the active one
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vectorSize * sizeof(vector3), &vertexList[0], GL_STATIC_DRAW);
	
	//count the attributes
	int attributeCount = 2;

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, vectorSize, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, vectorSize, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//View and projection matrix
	matrix4 m4Model = RTSG::IDENTITY_M4;
	matrix4 m4View;//view matrix
	matrix4 m4Projection;//projection matrix

	//the following can be a member field or a global variable to keep the value of the
	//last frame, but this is the only place they are ever used so the best thing we can
	//do is make them live in their own permanent sub stack (static)
	static float progress = 0.0f; //starting point for the LERP
	static float fDelta = 0.001f; //reason of change for the displacement
	static vector3 start(0.0f, 0.0f, 0.0f); //starting point
	static vector3 end(1.0f, 0.0f, 0.0f); //ending point

	//in a lerp funtion if the progress is larger than 1 (or 100%) the function will just keep going
	vector3 pos = glm::lerp(start, end, progress); //current position

	m4Model = glm::translate(RTSG::IDENTITY_M4, pos); //change the position of the object
	
	progress += fDelta; //increment the progress

	//read uniforms from the shader and send values
	GLuint MVP = glGetUniformLocation(shaderProgramID, "MVP");//Model View Projection
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4Projection * m4View * m4Model));
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
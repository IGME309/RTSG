/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __SHADERMANAGER_H_
#define __SHADERMANAGER_H_

#include "RTSG\system\Shader.h"

namespace RTSG
{

//ShaderManager singleton
class BTXDLL ShaderManager
{
	uint m_uShaderCount = 0; //Number of shaders

	static ShaderManager* m_pInstance; // Singleton
	
	std::vector<Shader> m_vShader; //vector of shaders
	std::map<String, int> m_map;//Indexer of Shaders

public:
	/*
	USAGE: Singleton accessor
	ARGUMENTS:
	OUTPUT:
	*/
	static ShaderManager* GetInstance();

	/*
	USAGE: Singleton Release
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	
	/*
	USAGE: Compiles a shader program and returns the OpenGL identifier
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	/*
	USAGE: Asks the manager for the OpenGL identifier for the specified name
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint GetShaderID(String a_sName);

	/*
	USAGE: Asks the manager for the OpenGL identifier for the specified index
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint GetShaderID(uint a_nIndex);

	/*
	USAGE: Ask for the Index in the vector of the specified shader name
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyShader(String a_sName);

private:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	ShaderManager(void);

	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	ShaderManager(ShaderManager const& other);

	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	ShaderManager& operator=(ShaderManager const& other);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ShaderManager(void);

	/*
	USAGE: Release Memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE: Initialize variables
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

} //namespace STR

#endif //__SHADERMANAGER_H_
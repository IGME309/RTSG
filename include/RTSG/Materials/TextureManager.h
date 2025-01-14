/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __TEXTUREMANAGER_H_
#define __TEXTUREMANAGER_H_

#include "RTSG\Materials\Texture.h"


namespace RTSG
{

//TextureManager Singleton
class BTXDLL TextureManager
{
	std::map<String,int> m_map;//indexer

public:
	std::vector<Texture*> m_textureList; //Vector of Textures

	/*
	USAGE: Singleton Accessor
	ARGUMENTS:
	OUTPUT:
	*/
	static TextureManager* GetInstance();

	/*
	USAGE: Singleton Destructor
	ARGUMENTS:
	OUTPUT: ---
	*/
	static void ReleaseInstance();
	
	/*
	USAGE: Returns the ID number of the texture, -1 if it does not exist.
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyTexure(String sName);

	/*
	USAGE: Loads a texture and returns the ID of where its stored in the vector
	ARGUMENTS:
	OUTPUT:
	*/
	int LoadTexture(String sName);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	static void SaveScreenshot(String a_sTextureName = "ScreenShot");

	/*
	USAGE: Returns the number of textures in the vector
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetTextureCount(void);

	/*
	USAGE: Returns the OpenGL Buffer ID in the vector location of the provided Index
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint ReturnGLIndex(uint a_nIndex);

private:
	/*
	USAGE: Singleton
	ARGUMENTS:
	OUTPUT:
	*/
	static TextureManager* m_pInstance;

	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	TextureManager(void);

	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	TextureManager(const TextureManager& other);

	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	TextureManager& operator=(const TextureManager& other);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~TextureManager(void);

	/*
	USAGE: Release the fields in the class
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

#endif __TEXTUREMANAGER_H_
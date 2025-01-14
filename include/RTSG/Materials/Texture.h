/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __TEXTURECLASS_H_
#define __TEXTURECLASS_H_

#include "RTSG\System\SystemSingleton.h"
#include "RTSG\System\FileReader.h"
#include "FreeImage\FreeImage.h"

namespace RTSG
{
	class BTXDLL Texture
	{
		GLuint m_nTextureID = 0;
		SystemSingleton* m_pSystem = nullptr;
		String m_sName = "NULL";
		String m_sFileName = "NULL";
		String m_sAbsoluteRoute = "";

	public:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT: class object
		*/
		Texture(void);
		
		/*
		USAGE: Copy Constructor
		ARGUMENTS:
		OUTPUT:
		*/
		Texture(const Texture& other);
		
		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS:
		OUTPUT:
		*/
		Texture& operator=(const Texture& other);

		/*
		USAGE: Release the fields in the class
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);

		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~Texture(void);

		/*
		USAGE: Loads the specified file onto this texture
		ARGUMENTS:
			String a_sFileName -> name of the file, if path not define will look
			under the textures folder
		OUTPUT: success
		*/
		bool LoadTexture(String a_sFileName);

		//Accessors
		/*
		USAGE: Returns the OpenGL Identifier
		ARGUMENTS: ---
		OUTPUT:
		*/
		GLuint GetGLTextureID(void);
		//__declspec(property(get = GetGLTextureID)) GLuint GLTextureID;

		/*
		USAGE: Returns the name of the texture
		ARGUMENTS: ---
		OUTPUT:
		*/
		String GetName(void);
		//__declspec(property(get = GetTextureName)) String TextureName;

		/*
		USAGE: Returns the filename of the texture
		ARGUMENTS: ---
		OUTPUT:
		*/
		String GetFileName(void);
		//__declspec(property(get = GetTextureFileName)) String TextureFileName;

		/*
		USAGE: Returns the file folder of the texture
		ARGUMENTS: ---
		OUTPUT:
		*/
		String GetAbsoluteRoute(void);

	private:
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Init(void); //Initializes the variables
	};

	EXPIMP_TEMPLATE template class BTXDLL std::vector<Texture>;
	EXPIMP_TEMPLATE template class BTXDLL std::vector<Texture*>;
} //namespace STR

#endif //_TEXTURECLASS_H
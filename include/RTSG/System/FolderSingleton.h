/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __BTXFOLDER_H_
#define __BTXFOLDER_H_

#include "RTSG\System\Definitions.h"

namespace RTSG
{

//Folder Class
class BTXDLL FolderSingleton
{
	String m_sRoot = "";
	String m_sData = "";
	String m_sBTO = "";
	String m_sOBJ = "";
	String m_sAudio = "";
	String m_sTextures = "";
	String m_sShaders = "";

	static FolderSingleton* m_pInstance;
public:
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	static FolderSingleton* GetInstance(void);

	/*
	USAGE: Singleton Destructor
	ARGUMENTS:
	OUTPUT: ---
	*/
	static void ReleaseInstance();
	
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderRoot(String a_sInput);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderRoot(void);
	//__declspec(property(put = SetFolderRoot, get = GetFolderRoot)) String Root;

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderData(String a_sInput);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderData(void);
	//__declspec(property(put = SetFolderData, get = GetFolderData)) String Data;

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderAudio(String a_sInput);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderAudio(void);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMBTO(String a_sInput);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMBTO(void);
	//__declspec(property(put = SetFolderMBTO, get = GetFolderMBTO)) String MBTO;

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMOBJ(String a_sInput);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMOBJ(void);
	//__declspec(property(put = SetFolderMOBJ, get = GetFolderMOBJ)) String MOBJ;

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderTextures(String a_sInput);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderTextures(void);
	//__declspec(property(put = SetFolderTextures, get = GetFolderTextures)) String Textures;

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderShaders(String a_sInput);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderShaders(void);
	//__declspec(property(put = SetFolderShaders, get = GetFolderShaders)) String Shaders;

private:
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	FolderSingleton(void);
	
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	FolderSingleton(const FolderSingleton& other);
	
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	FolderSingleton& operator=(const FolderSingleton& other);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~FolderSingleton(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetRealProgramPath(void);
};

} //namespace STR

#endif //__BTXFOLDER_H_
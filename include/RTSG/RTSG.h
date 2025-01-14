/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __SRTFRAMEWORK_H_
#define __SRTFRAMEWORK_H_

#pragma warning( disable : 4251 )

#include "RTSG\Physics\EntityManager.h"

namespace RTSG
{
	/*
	USAGE: Releases all STR Singletons
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseAllSingletons(void)
	{
		EntityManager::ReleaseInstance();
		ModelManager::ReleaseInstance();
		CameraManager::ReleaseInstance();
		MaterialManager::ReleaseInstance();
		TextureManager::ReleaseInstance();
		FolderSingleton::ReleaseInstance();
		ShaderManager::ReleaseInstance();
		SystemSingleton::ReleaseInstance();
		//GLSystem::ReleaseInstance();
		//LightManager::ReleaseInstance();
		//Text::ReleaseInstance();
	};

} //namespace STR

#endif //__SRTFRAMEWORK_H_
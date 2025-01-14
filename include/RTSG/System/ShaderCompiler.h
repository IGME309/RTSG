/*----------------------------------------------
From: http://www.opengl-tutorial.org/
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/

#ifndef __SHADERCOMPILER_H_
#define __SHADERCOMPILER_H_

#include "RTSG\System\Definitions.h"

/*
USAGE: Will load the specified files as vertex and fragment shaders
ARGUMENTS:
-	const char * vertex_file_path -> vertex shader file
-	const char * fragment_file_path -> fragment shader file
OUTPUT: opengl identifier of the loaded shader (0 if error)
*/
namespace RTSG
{

	BTXDLL GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

} //namespace STR

#endif //__SHADERCOMPILER_H_

/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __DEFINITIONS_H_
#define __DEFINITIONS_H_

// Include standard headers
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>
#include <locale>
#include <fstream>
#include <sstream>
#include <random>
#include <map>
#include <set>
#include <deque>
#include <locale>

// Include the GL extension Wrangler
#include <GL\glew.h>
#include <GL\wglew.h>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\matrix_decompose.hpp>

#ifdef EXP_STL
#	define BTXDLL __declspec(dllexport)
#	define EXPIMP_TEMPLATE
#else
#	define BTXDLL __declspec(dllimport)
#	define EXPIMP_TEMPLATE extern
#endif

/*
	USAGE: will safely delete the input pointer and initialize it to nullptr, DOES NOT WORK WITH POINTER ARRAY
*/
#define SafeDelete(p){ if(p) { delete p; p = nullptr; } }

namespace RTSG
{
	typedef unsigned int uint;
	typedef std::string String;
	typedef glm::vec2 vector2;
	typedef glm::vec3 vector3;
	typedef glm::vec4 vector4;
	typedef glm::mat3 matrix3;
	typedef glm::mat4 matrix4;
	typedef glm::quat quaternion;

	enum eBTX_RESOLUTIONS
	{
		//Resolution | Aspect Ratio | Name
		RES_WINDOWED,

		//Common resolutions
		RES_C_720x480_4x3_NTSC,
		RES_C_1280x720_16x9_HD,
		RES_C_1920x1080_16x9_FULLHD,

		RES_CV_480x720_3x4_NTSC,
		RES_CV_720x1280_9x16_HD,
		RES_CV_1080x1920_9x16_FULLHD,

		//Monitor Resolutions
		RES_M_640x480_4x3_VGA,
		RES_M_1600x900_16x9_WXGA,
		RES_M_1920x1200_16x10_WUXGA,
		RES_M_2560x1080_21x9_UWUXGA,

		RES_MV_480x640_3x4_VGA,
		RES_MV_900x1600_9x16_WXGA,
		RES_MV_1200x1920_10x16_WUXGA,
		RES_MV_1080x2560_9x21_UWUXGA,

		//Other Resolutions
		RES_O_800x600_4x3_SVGA,
		RES_O_1024x768_4x3_XGA,
		RES_O_1280x800_16x10_WXGA,
		RES_O_1600x1200_4x3_UXGA,
		RES_O_2048x1080_17x9_2K,
		RES_O_3840x2160_17x9_4K,

		//Squared Resolutions
		RES_S_600,
		RES_S_800,
		RES_S_1080,
		RES_S_1280,
	};

	enum eBTX_OUTPUT
	{
		OUT_ERR_NONE,
		OUT_ERR_GENERAL,
		OUT_ERR_FILE_MISSING,
		OUT_ERR_CONTEXT,
		OUT_ERR_MEMORY,
		OUT_ERR_NAME,
		OUT_ERR_NOT_INITIALIZED,
		OUT_ERR_FILE,
		OUT_ERR_NO_EXTENSION,
		OUT_DONE,
		OUT_RUNNING,
	};

	enum eBTX_RENDER
	{
		RENDER_NONE = 0,
		RENDER_SOLID = 1,
		RENDER_WIRE = 2,
	};

	enum eBTX_DISPLAY
	{
		BD_NONE = 0,//...
		BD_BS = 1, //Bounding Sphere
		BD_OB = 2, //Oriented Bounding Box
		BD_AB = 4, //Axis (Re)Aligned Bounding Box
	};

	enum eBTX_SPECIALMODEL
	{
		//Cubes
		CUBERED,
		CUBEGREEN,
		CUBEBLUE,
		CUBEWHITE,
		CUBEYELLOW,
		CUBECORNFLOWER,

		//Spheres
		SPHERERED,
		SPHEREGREEN,
		SPHEREBLUE,
		SPHEREWHITE,
		SPHEREYELLOW,
		SPHERECORNFLOWER,
	
	};

	/*
	USAGE: Will map a value from an original scale to a new scale
	ARGUMENTS:
	-	T valueToMap -> input value
	-	T originalScale_min ->  Start of the original scale
	-	T originalScale_max -> End of the original scale
	-	T mappedScale_min -> Start of the new scale
	-	T mappedScale_max -> end of the new scale
	OUTPUT: returns the mapped value
	*/
	template <class T>
	static T MapValue(T valueToMap, T originalScale_min, T originalScale_max, T mappedScale_min, T mappedScale_max)
	{
		return (valueToMap - originalScale_min) * (mappedScale_max - mappedScale_min) / (originalScale_max - originalScale_min) + mappedScale_min;
	}

	/*
	USAGE: Will trim the input string from when the first token is found till the end
	ARGUMENTS:
	-	String a_sInput -> input string
	-	char a_sToken -> token to be used as divider
	OUTPUT: trimmed output
	*/
	BTXDLL String CopyAfterToken(String a_sInput, char a_sToken);

	/*
	USAGE: Will take a glm::quat and return a glm::mat4 wrapping glm::mat4_cast
	ARGUMENTS: quaternion a_qInput -> quaternion to translate from
	OUTPUT: matrix4 conversion of a_qInput
	*/
	BTXDLL matrix4 ToMatrix4(quaternion a_qInput);

	/*
	USAGE: Will take a string and return an uppercase version of it
	ARGUMENTS: String a_sInput -> String to copy and make uppercase
	OUTPUT: Converted string
	*/
	BTXDLL String ToUppercase(String a_sInput);
} //namespace STR

#define PI 3.14159265358979323846
#define IDENTITY_M4 matrix4(1.0f)
#define IDENTITY_QUAT quaternion();
#define ZERO_V3 vector3(0.0f, 0.0f, 0.0f)
#define DEFAULT_V3NEG vector3(-1.0f, -1.0f, -1.0f)

#define C_BLACK vector3(0.0f, 0.0f, 0.0f)
#define C_WHITE vector3(1.0f, 1.0f, 1.0f)
#define C_GRAY vector3(0.3f, 0.3f, 0.3f)

#define C_RED vector3(1.0f, 0.0f, 0.0f)
#define C_MAGENTA vector3(1.0f, 0.0f, 1.0f)
#define C_BROWN vector3(0.6f,0.3f,0.0f)

#define C_GREEN vector3(0.0f, 1.0f, 0.0f)
#define C_GREEN_DARK vector3(0.0f, 5.0f, 0.0f)
#define C_GREEN_LIME vector3(0.33f,0.90f,0.33f)

#define C_BLUE vector3(0.0f, 0.0f, 1.0f)
#define C_BLUE_CORNFLOWER vector3(0.4f, 0.6f, 0.9f)
#define C_CYAN vector3(0.0f,1.0f,1.0f)

#define C_INDIGO vector3(0.30f, 0.0f, 0.52)

#define C_YELLOW vector3(1.0f, 1.0f, 0.0f)
#define C_ORANGE vector3(1.0f,0.5f,0.0f)
#define C_VIOLET vector3(0.54f,0.16f,0.88f)
#define C_PURPLE vector3(0.50f,0.0f,0.50f)

#define AXIS_X vector3(1.0f, 0.0f, 0.0f)
#define AXIS_XY vector3(1.0f, 1.0f, 0.0f)
#define AXIS_XZ vector3(1.0f, 0.0f, 1.0f)
#define AXIS_Y vector3(0.0f, 1.0f, 0.0f)
#define AXIS_YZ vector3(0.0f, 1.0f, 1.0f)
#define AXIS_Z vector3(0.0f, 0.0f, 1.0f)

#endif //__DEFINITIONS_H_
/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __MESHCLASS_H_
#define __MESHCLASS_H_

#include "RTSG\Materials\MaterialManager.h"
#include "RTSG\System\ShaderManager.h"
#include "BTXs\BTXs.h"

namespace RTSG
{
	/*
	A Mesh is the most basic container of a model or mesh.
	It contains the information about the material and the vertex cloud that forms it
	*/

	//Mesh Class
	class BTXDLL Mesh
	{
	protected:
		String m_sName = "NULL"; //Identifier of the Mesh

		bool m_bBinded = false; //Binded flag

		bool m_bLineObject = false; //Is this object formated to draw lines?

		uint m_uMaterialIndex = 0; //Material index of this mesh
		uint m_uVertexCount = 0; //Number of vertices in this Mesh
		uint m_uID = 0; //Identifier of the mesh (each mesh has a unique UID)

		GLuint m_VAO = 0;	//OpenGL Vertex Array Object
		GLuint m_VBO = 0;	//OpenGL Vertex Buffered Object
		GLuint m_MBO = 0;	//OpenGL Instanced Matrix per object

		GLfloat m_fLineWidth = 3.0f; //Thickness of lines.

		GLuint m_nShader = 0;	//Index of the shader

		vector3 m_v3Tint = vector3(1, 1, 1); //Color modifier
		vector3 m_v3Wireframe = vector3(0, 1, 0); //color of the wireframe

		std::vector<vector3> m_lVertex; //Composed vertex array
		std::vector<vector3> m_lVertexPos;	//List of Vertices
		std::vector<vector3> m_lVertexCol;	//List of Colors
		std::vector<vector3> m_lVertexNor;	//List of Normals
		std::vector<vector3> m_lVertexTan;	//List of Tangents
		std::vector<vector3> m_lVertexBin;	//List of Binormals
		std::vector<vector3> m_lVertexUV;	//List of UVS

		Mesh* m_pOriginal = nullptr; //Marks the Mesh this is a copy from, nullptr if this is the original
		ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
		MaterialManager* m_pMatMngr = nullptr;		//Material Manager

		static uint m_nIndexer; //Identifier count
#pragma region Construction / Destruction
		/*
		USAGE: Initialize the object's fields
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Init(void);

		/*
		USAGE: Releases the object from memory
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);

#pragma endregion
#pragma region Mesh Initialization
		/*
		USAGE: Completes the information missing to create the mesh
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CompleteMesh(vector3 a_v3Color = vector3(1.0f, 0.0f, 1.0f));

		/*
		USAGE: Disconnects OpenGL3.x from the Mesh without releasing the buffers
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void DisconnectOpenGL3X(void);

#pragma endregion
	public:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT: class object
		*/
		Mesh(void);

		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~Mesh(void);

		/*
		USAGE: Copy Constructor -> Mesh does not allow to copy
		from other Mesh objects, create an empty Mesh
		and use the Instantiate method instead
		ARGUMENTS: class object (to copy)
		OUTPUT: class object
		*/
		Mesh(Mesh& other);

		/*
		USAGE: Copy Assignment Operator -> Mesh does not allow to copy
		from other SimpleMesh objects, use the Instantiate method instead.
		ARGUMENTS: class object (to copy)
		OUTPUT: class object
		*/
		Mesh& operator=(Mesh& other);

		/*
		USAGE: Swaps the contents of the object with another object's content
		ARGUMENTS: class object  (to swap with)
		OUTPUT: ---
		*/
		void Swap(Mesh& other);

		/*
		USAGE: Will copy the information from the incoming mesh without modifying
			the original source and marking this mesh as a copy
		ARGUMENTS: class object (to Instantiate)
		OUTPUT: class object
		*/
		void Instantiate(Mesh* const other);

		/*
		USAGE: Compiles the Mesh for OpenGL 3.X use
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CompileOpenGL3X(void);

		/*
		USAGE: Completes the triangle information
		ARGUMENTS:
		- bool a_bAverageNormals = false -> soften the edges of the model
		OUTPUT: ---
		*/
		void CompleteTriangleInfo(bool a_bAverageNormals = false);

		/*
		USAGE: Calculates the missing tangents
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CalculateTangents(void);

		/*
		USAGE: Renders the mesh a_nInstances number of times on the specified positions by the a_fMatrixArray and by the
			provided camera view and projection
		ARGUMENTS:
		-	matrix4 a_mProjection -> Projection matrix
		-	matrix4 a_mView -> View matrix
		-	float* a_fMatrixArray -> Array of matrices that represent positions
		-	int a_nInstances -> Number of instances to display
		-	vector3 a_v3CameraPosition -> Position of the camera in world space
		-	int a_RenderOption = eBTO_RENDER::SOLID -> Render options SOLID | WIRE
		OUTPUT: ---
		*/
		uint Render(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances,
			vector3 a_v3CameraPosition = vector3(0), int a_RenderOption = eBTX_RENDER::RENDER_SOLID);

		/*
		USAGE: Renders the mesh 
		ARGUMENTS:
		-	vector3 a_v3CameraPosition -> Position of the camera in world space
		-	matrix4 a_mProjection -> Projection matrix
		-	matrix4 a_mView -> View matrix
		-	matrix4 a_mToWorld -> to world matrix
		-	vector3 a_v3CameraPosition -> Position of the camera in world space
		int a_RenderOption = eBTO_RENDER::SOLID -> Render options SOLID | WIRE
		OUTPUT: ---
		*/
		uint Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mWorld,
			vector3 a_v3CameraPosition = vector3(0), int a_RenderOption = eBTX_RENDER::RENDER_SOLID);

		/*
		USAGE: Renders the mesh a_nInstances number of times on the specified positions by the a_fMatrixArray and by the
		provided camera view and projection
		ARGUMENTS:
		-	matrix4 a_mProjection -> Projection matrix
		-	matrix4 a_mView -> View matrix
		-	float* a_fMatrixArray -> Array of matrices that represent positions
		-	int a_nInstances -> Number of instances to display
		OUTPUT: ---
		*/
		uint RenderWire(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances);

		/*
		USAGE: Renders the mesh a_nInstances number of times on the specified positions by the a_fMatrixArray and by the
		provided camera view and projection
		ARGUMENTS:
		-	matrix4 a_mProjection -> Projection matrix
		-	matrix4 a_mView -> View matrix
		-	float* a_fMatrixArray -> Array of matrices that represent positions
		-	int a_nInstances -> Number of instances to display
		-	vector3 a_v3CameraPosition -> Position of the camera in world space
		OUTPUT: ---
		*/
		uint RenderSolid(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances, vector3 a_v3CameraPosition);

		/*
		USAGE: Will render the line mesh using line mode, the object needs to be
		marked as a line object otherwise the method will return
		ARGUMENTS:
		-	matrix4 a_mProjection -> Projection matrix
		-	matrix4 a_mView -> View matrix
		-	float* a_fMatrixArray -> Array of matrices that represent positions
		-	int a_nInstances -> Number of instances to display
		OUTPUT: ---
		*/
		uint RenderLines(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances);

#pragma region Add Information to Mesh
		/*
		USAGE: Adds a quad to the list points in the buffer to be compiled
		//C--D
		//|  |
		//A--B
		//Will make the triangle A->B->C and then the triangle C->B->D
		ARGUMENTS:
		-	vector3 a_vBottomLeft (A)
		-	vector3 a_vBottomRight (B)
		-	vector3 a_vTopLeft (C)
		-	vector3 a_vTopRight (D)
		OUTPUT: ---
		*/
		void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);

		/*
		USAGE: Adds a tri to the list points in the buffer to be compiled
		//C
		//| \
		//A--B
		//This will make the triangle A->B->C
		ARGUMENTS:
		-	vector3 a_vBottomLeft (A)
		-	vector3 a_vBottomRight (B)
		-	vector3 a_vTopLeft (C)
		OUTPUT: ---
		*/
		void AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft);

		/*
		USAGE: Adds a quad to the list points in the buffer to be compiled
		//C--D
		//|  |
		//A--B
		//Will make the triangle A->B->C and then the triangle C->B->D
		ARGUMENTS:
		-	vector3 a_vBottomLeft (A)
		-	vector3 a_vBottomRight (B)
		-	vector3 a_vTopLeft (C)
		-	vector3 a_vTopRight (D)
		OUTPUT: ---
		*/
		void AddWireQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);

		/*
		USAGE: Adds a tri to the list points in the buffer to be compiled
		//C
		//| \
		//A--B
		//This will make the triangle A->B->C
		ARGUMENTS:
		-	vector3 a_vBottomLeft (A)
		-	vector3 a_vBottomRight (B)
		-	vector3 a_vTopLeft (C)
		OUTPUT: ---
		*/
		void AddWireTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft);

		/*
		USAGE: Sets the color of the wireframe
		ARGUMENTS: vector3 a_v3Color -> color to assign
		OUTPUT: ---
		*/
		void SetWireframeColor(vector3 a_v3Color);

		/*
		USAGE: Gets the color of the wireframe
		ARGUMENTS: ---
		OUTPUT: the color of the frame
		*/
		vector3 GetWireframeColor(void);

		/*
		USAGE: Set the shader to the newly loaded shader
		ARGUMENTS:
		-	String a_sVertexShaderName -> file name
		-	String a_sFragmentShaderName -> file name
		-	String a_sShaderName -> name of the shader
		-	vector3 a_v3Tint = DEFAULT_V3NEG -> tint color
		OUTPUT: ---
		*/
		void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName);

		/*
		USAGE: Sets the shader of the mesh to a loaded shader
		ARGUMENTS:
		-	String a_sShaderName = "Original" -> Name of the previously loaded shader
		-	vector3 a_v3Tint = DEFAULT_V3NEG -> color tint
		OUTPUT: ---
		*/
		void SetShaderProgram(String a_sShaderName = "Simplex");

		/*
		USAGE: Adds a new point to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexPosition(vector3 a_v3Input);

		/*
		USAGE: Adds a new lists of points to the vector of vertices
		ARGUMENTS:
		-	std::vector<vector3> a_v3Input -> list of vertices
		-	matrix4 a_m4ModelToWorld = IDENTITY_M4 -> vertices modifiers
		OUTPUT: ---
		*/
		void AddVertexPositionList(std::vector<vector3> a_lInput, matrix4 a_m4ModelToWorld = IDENTITY_M4);

		/*
		USAGE: Adds a new color to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexColor(vector3 a_v3Input);

		/*
		USAGE: Adds a new color list to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexColorList(std::vector<vector3> a_lInput);

		/*
		USAGE: Adds a new normal to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexNormal(vector3 a_v3Input);

		/*
		USAGE: Adds a new normal list to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexNormalList(std::vector<vector3> a_v3Input);

		/*
		USAGE: Adds a new binormal to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexBinormal(vector3 a_v3Input);

		/*
		USAGE: Adds a new binormal list to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexBinormalList(std::vector<vector3> a_v3Input);

		/*
		USAGE: Adds a new tangent to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexTangent(vector3 a_v3Input);

		/*
		USAGE: Adds a new tangent list to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexTangentList(std::vector<vector3> a_v3Input);

		/*
		USAGE: Adds a new uv to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexUV(vector3 a_v3Input);

		/*
		USAGE: Adds a new uv to the vector of vertices
		ARGUMENTS: vector3 a_v3Input -> vector input
		OUTPUT: ---
		*/
		void AddVertexUVList(std::vector<vector3> a_v3Input);

#pragma endregion
#pragma region Accessors
		/*
		USAGE: Asks the Mesh if it has been binded
		ARGUMENTS: ---
		OUTPUT: Whether its being binded or not
		*/
		bool GetBinded(void);

		/*
		USAGE: Returns the total number of vertices in this Mesh
		ARGUMENTS: ---
		OUTPUT: Number of vertices
		*/
		int GetVertexCount(void);

		/*
		USAGE: Gets the material used in the mesh by index of the material manager
		ARGUMENTS: ---
		OUTPUT: index of the material used
		*/
		int GetMaterialIndex(void);

		/*
		USAGE: Sets the material of the mesh by index of the Material manager
		ARGUMENTS: int a_nMaterialIndex -> Index of the previously loaded material
		OUTPUT: ---
		*/
		void SetMaterial(int a_nMaterialIndex);

		/*
		USAGE: Sets the material of the mesh by name
		ARGUMENTS: String a_sMaterialName -> Name of the previously loaded material
		OUTPUT: ---
		*/
		void SetMaterial(String a_sMaterialName);

		/*
		USAGE: Sets the material of the mesh by name
		ARGUMENTS:
		-	String a_sMaterialName -> Name of the previously loaded material
		-	String a_sDiffuseMapName -> Filename to be used as Diffuse Map
		-	String a_sNormalMapName -> Filename to be used as Normal Map
		-	String a_sSpecularName -> Filename to be used as Specular Map
		OUTPUT: ---
		*/
		void SetMaterial(String a_sMaterialName, String a_sDiffuseMapName, String a_sNormalMapName = "", String a_sSpecularName = "");

		/*
		USAGE: Asks the mesh for the Shader program used
		ARGUMENTS: ---
		OUTPUT: index of the shader
		*/
		GLuint GetShaderIndex(void);

		/*
		USAGE: Return the tint applied to the mesh
		ARGUMENTS: ---
		OUTPUT: tint applied to this mesh
		*/
		vector3 GetTint(void);

		/*
		USAGE: Applies a tint to the mesh
		ARGUMENTS: vector3 a_v3Tint -> color to apply to the mesh
		OUTPUT: ---
		*/
		void SetTint(vector3 a_v3Tint);

		/*
		USAGE: Set the list of vertices to the incoming one
		ARGUMENTS: std::vector<vector3> a_lVertex -> list of vertices
		OUTPUT: ---
		*/
		void SetVertexList(std::vector<vector3> a_lVertex);

		/*
		USAGE: Asks the mesh for the list of vertices
		ARGUMENTS: ---
		OUTPUT: list of vertices of this mesh
		*/
		std::vector<vector3> GetVertexList(void);

		/*
		USAGE: Set the list of colors to the incoming one
		ARGUMENTS: std::vector<vector3> a_lColor -> list of colors
		OUTPUT: ---
		*/
		void SetColorList(std::vector<vector3> a_lColor);

		/*
		USAGE: Asks the mesh for the list of Color vertices
		ARGUMENTS: ---
		OUTPUT: color list
		*/
		std::vector<vector3> GetColorList(void);

		/*
		USAGE: Set the list of UVs to the incoming one
		ARGUMENTS: std::vector<vector3> a_lUV -> list of UV
		OUTPUT: ---
		*/
		void SetUVList(std::vector<vector3> a_lUV);

		/*
		USAGE: Asks the mesh for the list of UV vertices
		ARGUMENTS: ---
		OUTPUT: uv list
		*/
		std::vector<vector3> GetUVList(void);

		/*
		USAGE: Set the list of normals to the incoming one
		ARGUMENTS: std::vector<vector3> a_lNormal -> list of normals
		OUTPUT: ---
		*/
		void SetNormalList(std::vector<vector3> a_lNormal);

		/*
		USAGE: Asks the mesh for the list of Normal vertices
		ARGUMENTS: ---
		OUTPUT: normal list
		*/
		std::vector<vector3> GetNormalList(void);

		/*
		USAGE: Set the list of tangents to the incoming one
		ARGUMENTS: std::vector<vector3> a_lTangent -> list of tangents
		OUTPUT: ---
		*/
		void SetTangentList(std::vector<vector3> a_lTangent);

		/*
		USAGE: Asks the mesh for the list of tangents
		ARGUMENTS: ---
		OUTPUT: tangent list
		*/
		std::vector<vector3> GetTangentList(void);

		/*
		USAGE: Set the list of bitangents to the incoming one
		ARGUMENTS: std::vector<vector3> a_lbitangents -> list of bitangents
		OUTPUT: ---
		*/
		void SetBitangentList(std::vector<vector3> a_lBitangent);

		/*
		USAGE: Asks the mesh for the list of bitangents
		ARGUMENTS: ---
		OUTPUT: bitangent list
		*/
		std::vector<vector3> GetBitangetList(void);

		/*
		USAGE: Asks the Mesh for its name
		ARGUMENTS: ---
		OUTPUT: Name of the mesh
		*/
		String GetName(void);

		/*
		USAGE: Sets the Mesh's name
		ARGUMENTS: String a_sName -> new name to add
		OUTPUT: ---
		*/
		virtual void SetName(String a_sName);

		/*
		USAGE: returns the VAO of the mesh
		ARGUMENTS: ---
		OUTPUT: VAO
		*/
		GLuint GetVAO(void);

		/*
		USAGE: returns the VBO of the mesh
		ARGUMENTS: ---
		OUTPUT: VAO
		*/
		GLuint GetVBO(void);

		/*
		USAGE: Returns the unique identifier of the mesh
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		uint GetUniqueIdentifier(void);

		/*
		USAGE: If this is a cloned group this will return the original one
		ARGUMENTS: ---
		OUTPUT: original group; nullptr if this is an original group
		*/
		Mesh* GetOriginal(void);

#pragma endregion
#pragma region Primitive Generation
		/*
		USAGE: Generates a plane
		ARGUMENTS:
		-	float a_fSize -> Size of each side
		-	vector3 a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GeneratePlane(float a_fSize, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);
		/*
		USAGE: Generates a circle mesh
		ARGUMENTS:
		-	float a_fRadius -> radius
		-	int a_nSubdivisions -> divisions of the cap
		-	vector3 a_v3Color -> Color of the mesh
		OUTPUT: ---
		*/
		void GenerateCircle(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);

		/*
		USAGE: Generates a cube
		ARGUMENTS:
		-	float a_fSize -> Size of each side
		-	vector3 a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateCube(float a_fSize, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a cone mesh
		ARGUMENTS:
		-	float a_fRadius -> radius
		-	float a_fHeight -> how tall is the mesh
		-	int a_nSubdivisions -> divisions of the cap
		-	vector3 a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a cylinder mesh
		ARGUMENTS:
		-	float a_fRadius -> radius
		-	float a_fHeight -> how tall is the mesh
		-	int a_nSubdivisions -> divisions on the cap
		-	vector3 a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a tube mesh
		ARGUMENTS:
		-	float a_fOuterRadius -> outer radius
		-	float a_fInnerRadius -> inner radius
		-	float a_fHeight -> how tall is the mesh
		-	int a_nSubdivisions -> divisions on the cap
		-	a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a torus mesh
		ARGUMENTS:
		-	float a_fOuterRadius -> Outer radius
		-	float a_fInnerRadius -> Inner Radius
		-	int a_nSubdivisionHeight -> divisions vertical
		-	int a_nSubdivisionAxis -> divisions along the roundness of the mesh
		-	a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a Sphere mesh
		ARGUMENTS:
		-	float a_fRadius -> radius of the sphere
		-	int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subd
		-	a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		NOTES: Based on Kiernan Brown's method
		*/
		void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a line Sphere mesh
		ARGUMENTS:
		-	float a_fRadius -> radius of the sphere
		-	int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subd
		-	a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: --- icosahedron
		NOTES: Based on Giovanni Aleman's method
		*/
		void GenerateIcosahedron(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a unit size star mesh
		ARGUMENTS:
		-	uint a_uSubdivisions -> points of the star
		-	float fRadius1 = 1.0f -> radius of the outer points
		-	float fRadius2 = 0.5f -> radius of the inner points
		-	vector3 a_v3Color = C_WHITE -> color of the shape
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateStar(uint a_uSubdivisions, float fRadius1 = 1.0f, float fRadius2 = 0.5f, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a wire cube
		ARGUMENTS:
		-	float a_fSize -> Size of each side
		-	vector3 a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateWireCube(float a_fSize, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a wire Sphere
		ARGUMENTS:
		-	float a_fRadius -> Radius of the sphere
		-	vector3 a_v3Color -> Color of the mesh
		-	matrix4 a_m4Transform -> Transform of the generated shape
		OUTPUT: ---
		*/
		void GenerateWireSphere(float a_fRadius, vector3 a_v3Color = C_WHITE, matrix4 a_m4Transform = IDENTITY_M4);

		/*
		USAGE: Generates a skybox using the skybox.png file from data folder
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void GenerateSkybox(void);

		/*
		USAGE: Generates a line using the two points and colors provided
		ARGUMENTS: ---
		OUTPUT: Returns the name of the line based on the positions and colors
		*/
		void GenerateLine(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3ColorStart, vector3 a_v3ColorEnd);



		/*
		USAGE: returns the static count of meshes
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		static uint GetStaticCount(void);

		/*
		USAGE: Will get how many times the graphics card has been called
			to render something using a Mesh object
		ARGUMENTS: ---
		OUTPUT: number of calls
		*/
		static uint GetRenderCallCount(void);

		/*
		USAGE: Will reset the render call count	called to render something using a Mesh object
		ARGUMENTS: ---
		OUTPUT: number of calls
		*/
		static void ResetRenderCallCount(void);

		/*
		USAGE: Sets the thickness of the rendered line
		ARGUMENTS: float a_fLineWidth -> how thick the line is
		OUTPUT: void
		*/
		void SetLineWidth(float a_fLineWidth = 3.0f);
#pragma endregion
	};

	//EXPIMP_TEMPLATE template class BTXDLL std::vector<Mesh>;
	EXPIMP_TEMPLATE template class BTXDLL std::vector<Mesh*>;

} //namespace STR

#endif //__MESHCLASS_H_
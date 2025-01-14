/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __MODELCLASS_H_
#define __MODELCLASS_H_

#include "RTSG\Mesh\Mesh.h"
namespace RTSG
{
	//Model Class
	class BTXDLL Model
	{
		String m_sFileName = ""; //Name of the file that made this model
		std::vector<Mesh*> m_MeshList; //list of meshes that belong to this model
		std::vector<matrix4> m_RenderListSolid; //For each mesh in the List where would we render them?
		std::vector<matrix4> m_RenderListWire; //For each mesh in the List where would we render them in wireframe?

		MaterialManager* m_pMatMngr = nullptr; //Material Manager pointer
		String m_sMaterialAppend = ""; //Name of the material based on the file

	public:
		
		/*
		Usage: Constructor
		Arguments: 
		-	String a_sFileName -> Name to give the model or file to load if a_bIsModelFile = true
		-	bool a_bIsModelFile -> Is a_sFileName the name of a file to load?
		Output: class object instance
		*/
		Model(String a_sFileName, bool a_bIsModelFile = true);

		/*
		Usage: Constructor based on a single mesh,
		Arguments: a_pMesh -> mesh to create the object around
		Output: class object instance
		*/
		Model(Mesh* a_pMesh);

		/*
		Usage: Destructor
		Arguments: ---
		Output: ---
		*/
		~Model(void);

		/*
		USAGE: Renders the mesh
		ARGUMENTS:
		-	vector3 a_v3CameraPosition -> Position of the camera in world space
		-	matrix4 a_mProjection -> Projection matrix
		-	matrix4 a_mView -> View matrix
		-	matrix4 a_mToWorld -> to world matrix
		-	vector3 a_v3CameraPosition -> Position of the camera in world space
		int a_RenderOption = BTO_RENDER::SOLID -> Render options SOLID | WIRE
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
		-	vector3 a_v3CameraPosition -> Position of the camera in world space
		-	int a_RenderOption = BTO_RENDER::SOLID -> Render options SOLID | WIRE
		OUTPUT: ---
		*/
		uint Render(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances,
			vector3 a_v3CameraPosition = vector3(0), int a_RenderOption = eBTX_RENDER::RENDER_SOLID);

		/*
		USAGE: Returns the name of the model
		ARGUMENTS: ---
		OUTPUT: Name of the model
		*/
		String GetName(void);

		/*
		USAGE: Sets the name of the model
		ARGUMENTS: a_sName -> name to set
		OUTPUT: ---
		*/
		void SetName(String a_sName);

		/*
		USAGE: 
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void AddToRenderList(matrix4 a_m4Transform, int a_RenderOption = RTSG::eBTX_RENDER::RENDER_SOLID);

		/*
		Usage: Will Get all matrix transforms for where to draw this model instanced
		Arguments: ---
		Output: transforms for each render
		*/
		std::vector<matrix4> GetRenderListSolids(void);
		/*
		Usage: Will Get all matrix transforms for where to draw this model instanced
		Arguments: ---
		Output: transforms for each render
		*/
		std::vector<matrix4> GetRenderListWires(void);
		/*
		Usage: Renders both wire and solid lists
		Arguments: 
			matrix4 a_m4Projection, 
			matrix4 a_m4View, 
			vector3 a_v3CameraPosition
		Output: ---
		*/
		uint RenderLists(matrix4 a_m4Projection, matrix4 a_m4View, vector3 a_v3CameraPosition);
		
		/*
		Usage: Will remove the objects from both render lists
		Arguments: ---
		Output: ---
		*/
		void ClearRenderLists(void);

		/*
		USAGE: Gets the vertex list of the model
		ARGUMENTS:
		OUTPUT:
		*/
		std::vector<vector3> GetVertexList();

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
		USAGE: Generates a star mesh
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
		USAGE: Sets the thickness of the rendered line
		ARGUMENTS: float a_fLineWidth -> how thick the line is
		OUTPUT: void
		*/
		void SetLineWidth(float a_fLineWidth = 3.0f);

#pragma endregion

	private:
		/*
		Usage: Copy Constructor
		Arguments: class object to copy
		Output: class object instance
		*/
		Model(Model const& other);

		/*
		Usage: Copy Assignment Operator
		Arguments: class object to copy
		Output: ---
		*/
		Model& operator=(Model const& other);

		/*
		Usage: Deallocates member fields
		Arguments: ---
		Output: ---
		*/
		void Release(void);

		/*
		Usage: Allocates member fields
		Arguments: ---
		Output: ---
		*/
		void Init(void);

		/*
		Usage: Changes object contents for other object's
		Arguments: other -> object to swap content from
		Output: ---
		*/
		void Swap(Model& other);

		/*
		Usage: Load the specified model
		Arguments: filename to open
		Output: filename
		*/
		String Load(String a_sFileName);

		/*
		Usage: Load the specified model
		Arguments: filename to open
		Output: filename
		*/
		String LoadOBJ(String a_sFileName);

		/*
		USAGE: Loads the material file for this model
		ARGUMENTS:
			String a_sFileName -> Name of the mtl file
		OUTPUT:
			Name assigned in the map
		*/
		void LoadMTL(String a_sFileName);

		/*
		Usage: Will return the pointer of the Mesh in vector by the Material Index
		Arguments: uint a_uMaterialIndex -> Index of the material
		Output: Mesh* in vector
		*/
		Mesh* IdentifyMeshByMaterialIndex(uint a_uMaterialIndex);

		/*
		Usage: Will initialize all pMeshes
		Arguments: ---
		Output: ----
		*/
		void CompileMeshes(void);
	};
}

#endif //__MODELCLASS_H_
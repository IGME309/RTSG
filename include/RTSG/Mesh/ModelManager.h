/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __MESHMANAGER_H_
#define __MESHMANAGER_H_
#include "RTSG\Mesh\Model.h"
#include "RTSG\Camera\CameraManager.h"

namespace RTSG
{

//MeshManager singleton
class BTXDLL ModelManager
{
	std::vector<Model*> m_ModelList; //List of all the Models added to the system
	std::map<String, Model*> m_ModelMap; //map of Model names and corresponding pointer
	
	static ModelManager* m_pInstance; // Singleton pointer
	ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManager* m_pMatMngr = nullptr;	//Material Manager
	CameraManager* m_pCameraMngr = nullptr;	//Camera Manager

public:
	//Singleton Methods
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static ModelManager* GetInstance();
	
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);

	/*
	USAGE: Returns the mesh specified by name from the list of Meshes
	ARGUMENTS: String a_sName -> name of the mesh
	OUTPUT: index in the list, -1 if not found
	*/
	int GetModelIndex(String a_sName);

	/*
	USAGE: Returns the mesh specified by name from the list of Meshes
	ARGUMENTS: String a_sName -> name of the mesh
	OUTPUT: Inquired mesh
	*/
	Model* GetModel(String a_sName);

	/*
	USAGE: Asks whether a Model is in the map or not
	ARGUMENTS: String a_sName -> name of the Model
	OUTPUT: is the Model in the map?
	*/
	bool IsModelInMap(String a_sName);

	/*
	USAGE: Asks whether a Model is in the map or not
	ARGUMENTS: Model* pModel -> Pointer to desired Model
	OUTPUT: is the Mesh in the map?
	*/
	bool IsModelInMap(Model* pModel);

	/*
	USAGE: Adds a mesh to the list of meshes
	ARGUMENTS: Mesh* a_pMesh -> mesh to add
	OUTPUT: index of the mesh in the list, if -1 there was an error
	*/
	Model* AddModel(Model* a_pModel);

	/*
	USAGE: Generates a plane
	ARGUMENTS:
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniPlane(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates a cube
	ARGUMENTS:
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniCube(vector3 a_v3Color = C_WHITE);

	/*
	USAGE:Generates a cone mesh
	ARGUMENTS:
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniCone(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates a cylinder mesh
	ARGUMENTS:
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniCylinder(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates a tube mesh
	ARGUMENTS:
		a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniTube(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates a torus mesh
	ARGUMENTS:
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniTorus(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates a Sphere mesh
	ARGUMENTS:
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniSphere(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates a unit size star mesh
	ARGUMENTS:
	-	vector3 a_v3Color = C_WHITE -> color of the shape
	OUTPUT: ---
	*/
	Model* GenerateUniStar(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates an IcoSphere mesh
	ARGUMENTS:
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniIcosahedron(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates an WireCube mesh
	ARGUMENTS:
	-	float a_fSize -> Size of the cube
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateUniWireCube(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates an WireSphere mesh
	ARGUMENTS:
	-	float a_fRadius -> radius of the sphere
	-	a_v3Color -> Color of the mesh
	OUTPUT: name of the generated Mesh
	*/
	Model* GenerateUniWireSphere(vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Generates a skybox using the skybox.png file from data folder
	ARGUMENTS: ---
	OUTPUT: index of the generated Mesh
	*/
	Model* GenerateSkybox(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	Model* GenerateLine(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3ColorStart, vector3 a_v3ColorEnd);

	/*
	USAGE: will return all the names already stored in the mesh list
	ARGUMENTS: ---
	OUTPUT: Names in map
	*/
	std::vector<String> GetModelNames(void);

	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddPlaneToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders the cone on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddConeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders the cylinder on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddCylinderToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders the tube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddTubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders the torus on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddTorusToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders the star on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddStarToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Renders an IcoSphere on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddIcosahedronToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE, int a_Render = eBTX_RENDER::RENDER_SOLID);
	
	/*
	USAGE: Renders an WireCube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddWireCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Renders an WireSphere on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddWireSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = C_WHITE);

	/*
	USAGE: Renders a special colored Wire Spere or Cube according to the selection
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	eBTX_SPECIALMODEL a_eSelection -> Shape to render
	OUTPUT: ---
	*/
	void AddSpecialToRenderList(eBTX_SPECIALMODEL a_eSelection, matrix4 a_m4ToWorld);

	/*
	USAGE: Renders a line in the specified positions and colors
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to draw the primitive onto
	-	vector3 a_v3Start -> Start point in local space
	-	vector3 a_v3End -> End point in local space
	-	vector3 a_v3ColorStart -> Color of the start point
	-	vector3 a_v3ColorEnd -> Color of the end point
	OUTPUT: ---
	*/
	void AddLineToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Start, vector3 a_v3End, 
		vector3 a_v3ColorStart = C_WHITE, vector3 a_v3ColorEnd = C_WHITE);

	/*
	USAGE: This add a giant inwards box to the scene at the origin which will translate along
		the camera use the argument to change the texture rendered
	ARGUMENTS:
		String a_sFileName -> name of the file to add
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddSkyboxToRenderList(String a_sFileName = "skybox.png");

	/*
	USAGE: Render an axis on the specified position
	ARGUMENTS: matrix4 a_m4ToWorld -> space on which the axis will be rendered
	OUTPUT: ---
	*/
	void AddAxisToRenderList(matrix4 a_m4ToWorld);

	/*
	USAGE: Render a grid on the specified position
	ARGUMENTS: matrix4 a_m4ToWorld -> space on which the grid will be rendered
	OUTPUT: ---
	*/
	void AddGridToRenderList(matrix4 a_m4ToWorld);

	/*
	USAGE: Render a grid based on the active camera's mode
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AddGridToRenderList();

	/*
	USAGE: Render a visual representation of the camera
	ARGUMENTS: int a_nIndex = -1 -> camera index, if less than 0 all cameras will be rendered
	OUTPUT: ---
	*/
	void AddCameraToRenderList(int a_nIndex = -1);

	/*
	USAGE: Applies a transform to display to the specified mesh by name, the mesh will be
	lookout	for in the map of meshes, using the mesh index if know will result in faster
	additions
	ARGUMENTS:
	Strin a_sMeshName -> mesh to apply transform to
	matrix4 a_m4Transform -> transform to apply
	int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddModelToRenderList(String a_sMeshName, matrix4 a_m4Transform, 
		int a_RenderOption = eBTX_RENDER::RENDER_SOLID);

	/*
	USAGE: Finds the specified mesh and speficies a transform to display
	ARGUMENTS:
		uint a_nIndex -> index of the mesh to apply transform to
		matrix4 a_m4Transform -> transform to apply
		int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddModelToRenderList(Model* pModel, matrix4 a_m4Transform, 
		int a_RenderOption = eBTX_RENDER::RENDER_SOLID);
	
	/*
	USAGE: Clears the map of transforms
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearRenderList(void);

	/*
	USAGE: Draws all the meshes in the map
	ARGUMENTS: ---
	OUTPUT: number of render calls
	*/
	uint Render(void);

	/*
	USAGE: Draws all the meshes in the map
	ARGUMENTS: ---
	OUTPUT: number of render calls
	*/
	uint Render(matrix4 a_m4Projection, matrix4 a_m4View, vector3 a_v3CameraPosition);

	/*
	USAGE: Get the number of meshes in the mesh manager
	ARGUMENTS: ---
	OUTPUT: number of meshes
	*/
	uint GetModelCount(void);

	/*
	Usage: Load the specified model
	Arguments: filename to open
	Output: filename
	*/
	String LoadModel(String a_sFileName);

	/*
	USAGE: Gets the vertex list of the model
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(String a_sName);

	/*
		USAGE: Sets the thickness of the rendered line of wire spheres
		ARGUMENTS: float a_fLineWidth -> how thick the line is
		OUTPUT: void
	*/
	void SetWireSphereThickness(float a_fLineWidth = 3.0f);

	/*
		USAGE: Sets the thickness of the rendered line of wire spheres
		ARGUMENTS: float a_fLineWidth -> how thick the line is
		OUTPUT: void
	*/
	void SetWireCubeThickness(float a_fLineWidth = 3.0f);

private:
	//Rule of 3
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	ModelManager(void);

	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	ModelManager(ModelManager const& other);

	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	ModelManager& operator=(ModelManager const& other);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ModelManager(void);

	//Other methods
	/*
	USAGE: Initializes the objects fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);

	/*
	USAGE: Releases the objects memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};

} //namespace STR

#endif //__MESHMANAGER_H_
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
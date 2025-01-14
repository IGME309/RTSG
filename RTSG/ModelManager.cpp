#include "RTSG\Mesh\ModelManager.h"
using namespace RTSG;
Model* g_pShape[12];

//  ModelManager
ModelManager* ModelManager::m_pInstance = nullptr;
enum ModelOrder
{
	SKYBOX, //0
	LINE, //1
	CUBE, //2
	CONE, //3
	CYLINDER, //4
	TUBE, //5
	PLANE, //6
	SPHERE, //7
	TORUS, //8
	ICOSAHEDRON, //9
	WIRECUBE, //10
	WIRESPHERE, //11
	STAR, //12
};
void ModelManager::Init(void)
{
	//Get singletons instance
	m_pShaderMngr = ShaderManager::GetInstance();
	m_pMatMngr = MaterialManager::GetInstance();
	m_pCameraMngr = CameraManager::GetInstance();

	//Generate basic primitives that will be used frequently
	//Needed them in a particular order, this seems the best way of making sure it happens
	//The switch is meant to have them in the right order, even if the labels change
	for (uint i = 0; i < 12; i++)
	{
		switch (i)
		{
		case ModelOrder::SKYBOX:
			GenerateSkybox();
			break;
		case ModelOrder::CUBE:
			GenerateUniCube(C_WHITE);
			break;
		case ModelOrder::CONE:
			GenerateUniCone(C_WHITE);
			break;
		case ModelOrder::CYLINDER:
			GenerateUniCylinder(C_WHITE);
			break;
		case ModelOrder::TUBE:
			GenerateUniTube(C_WHITE);
			break;
		case ModelOrder::PLANE:
			GenerateUniPlane(C_WHITE);
			break;
		case ModelOrder::SPHERE:
			GenerateUniSphere(C_WHITE);
			break;
		case ModelOrder::TORUS:
			GenerateUniTorus(C_WHITE);
			break;
		case ModelOrder::LINE:
			GenerateLine(vector3(0.0f, 0.0f, 0.0f), vector3(1.0f, 0.0f, 0.0f), C_WHITE, C_WHITE);
			break;
		case ModelOrder::ICOSAHEDRON:
			GenerateUniIcosahedron(C_WHITE);
			break;
		case ModelOrder::WIRECUBE:
			GenerateUniWireCube(C_WHITE);
			break;
		case ModelOrder::WIRESPHERE:
			GenerateUniWireSphere(C_WHITE);
			break;
		case ModelOrder::STAR:
			GenerateUniStar(C_WHITE);
			break;
		default:
			break;
		}
	}
	//special colored cubes
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBERED] = GenerateUniWireCube(C_RED);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEGREEN] = GenerateUniWireCube(C_GREEN);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEBLUE] = GenerateUniWireCube(C_BLUE);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEWHITE] = GenerateUniWireCube(C_WHITE);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEYELLOW] = GenerateUniWireCube(C_YELLOW);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBECORNFLOWER] = GenerateUniWireCube(C_BLUE_CORNFLOWER);
	
	//special colored spheres
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHERERED] = GenerateUniWireSphere(C_RED);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREGREEN] = GenerateUniWireSphere(C_GREEN);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREBLUE] = GenerateUniWireSphere(C_BLUE);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREWHITE] = GenerateUniWireSphere(C_WHITE);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREYELLOW] = GenerateUniWireSphere(C_YELLOW);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHERECORNFLOWER] = GenerateUniWireSphere(C_BLUE_CORNFLOWER);

	SetWireCubeThickness(3.0f);
	SetWireSphereThickness(1.0f);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHERERED]->SetLineWidth(5.0f);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBERED]->SetLineWidth(1.5f);
}

void ModelManager::SetWireCubeThickness(float a_fLineWidth)
{
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBERED]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEGREEN]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEBLUE]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEWHITE]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBEYELLOW]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::CUBECORNFLOWER]->SetLineWidth(a_fLineWidth);
}
void ModelManager::SetWireSphereThickness(float a_fLineWidth)
{
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHERERED]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREGREEN]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREBLUE]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREWHITE]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHEREYELLOW]->SetLineWidth(a_fLineWidth);
	g_pShape[RTSG::eBTX_SPECIALMODEL::SPHERECORNFLOWER]->SetLineWidth(a_fLineWidth);
}
void ModelManager::Release(void)
{	
	m_pShaderMngr = nullptr;
	m_pMatMngr = nullptr;
	m_pCameraMngr = nullptr;
	uint uModelCount = m_ModelList.size();
	for (uint i = 0; i < uModelCount; ++i)
	{
		Model* pModel = m_ModelList[i];
		if (pModel)
		{
			delete pModel;
			pModel = nullptr;
		}
	}

	m_ModelList.clear();
	m_ModelMap.clear();
}
ModelManager* ModelManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new ModelManager();
	}
	return m_pInstance;
}
void ModelManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
ModelManager::ModelManager(){Init();}
ModelManager::ModelManager(ModelManager const& other){ }
ModelManager& ModelManager::operator=(ModelManager const& other) { return *this; }
ModelManager::~ModelManager(){Release();};
//--- Generate shapes
Model* ModelManager::AddModel(Model* a_pModel)
{
	//check if empty pointer
	if (!a_pModel)
		return nullptr;
	
	//Check if the model is already in the list 
	//if it is, then don't add it, return the existing one
	String sName = a_pModel->GetName();
	//sName = RTSG::ToUppercase(sName);
//	a_pModel->SetName(sName);

	Model* pModel = GetModel(sName);
	if (pModel)
		return pModel;

	//If the model was not in the list add it to it
	m_ModelList.push_back(a_pModel);
	//Add it to the map
	m_ModelMap.insert(std::pair<String, Model*>(sName, a_pModel));
	//and return its name
	return a_pModel;
}
String GenerateName(int nShape, vector3 a_v3Color)
{
	String sName;
	switch (nShape)
	{
	case ModelOrder::CUBE:
		sName = "cube_(";
		break;
	case ModelOrder::CONE:
		sName = "cone_(";
		break;
	case ModelOrder::CYLINDER:
		sName = "cylinder_(";
		break;
	case ModelOrder::TUBE:
		sName = "tube_(";
		break;
	case ModelOrder::PLANE:
		sName = "plane_(";
		break;
	case ModelOrder::SPHERE:
		sName = "sphere_(";
		break;
	case ModelOrder::TORUS:
		sName = "torus_(";
		break;
	case ModelOrder::ICOSAHEDRON:
		sName = "icosahedron_(";
		break;
	case ModelOrder::WIRECUBE:
		sName = "wirecube_(";
		break;
	case ModelOrder::WIRESPHERE:
		sName = "wiresphere_(";
		break;
	case ModelOrder::STAR:
		sName = "star_(";
		break;
	default:
		break;
	}

	sName = sName +
		std::to_string(a_v3Color.x) + "," +
		std::to_string(a_v3Color.y) + "," +
		std::to_string(a_v3Color.z) + ")";

	//sName = RTSG::ToUppercase(sName);
	return sName;
}
Model* ModelManager::GenerateUniPlane(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::PLANE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GeneratePlane(1.0f, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniCube(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::CUBE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCube(1.0f, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniCone(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::CONE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCone(0.5f, 1.0f, 12, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniCylinder(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::CYLINDER, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCylinder(0.5f, 1.0f, 12, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniTube(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::TUBE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTube(0.5f, 0.35f, 1.0f, 12, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniTorus(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::TORUS, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTorus(0.5f, 0.35f, 12, 12, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniSphere(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::SPHERE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateSphere(1.0f, 6, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniStar(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::STAR, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateStar(5, 1.0f, 0.5f, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniIcosahedron(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::ICOSAHEDRON, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateIcosahedron(1.0f, 2, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniWireCube(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::WIRECUBE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateWireCube(1.0f, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateUniWireSphere(vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::WIRESPHERE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateWireSphere(1.0f, a_v3Color);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateLine(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3ColorStart, vector3 a_v3ColorEnd)
{
	//Try to find a model with this name
	String sName = "line_(" +
		std::to_string(a_v3Start.x) + "," +
		std::to_string(a_v3Start.y) + "," +
		std::to_string(a_v3Start.z) + "," +
		std::to_string(a_v3End.x) + "," +
		std::to_string(a_v3End.y) + "," +
		std::to_string(a_v3End.z) + "," +
		std::to_string(a_v3ColorStart.x) + "," +
		std::to_string(a_v3ColorStart.y) + "," +
		std::to_string(a_v3ColorStart.z) + "," +
		std::to_string(a_v3ColorEnd.x) + "," +
		std::to_string(a_v3ColorEnd.y) + "," +
		std::to_string(a_v3ColorEnd.z) + ")";
	//sName = RTSG::ToUppercase(sName);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateLine(a_v3Start, a_v3End, a_v3ColorStart, a_v3ColorEnd);
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);
	return AddModel(pModel);
}
Model* ModelManager::GenerateSkybox(void)
{
	//There can only be one skybox, if needed we would change texture 
	//for it on add to render list
	String sName = "skybox_skybox.png";
	//sName = RTSG::ToUppercase(sName);
	Model* pModel = GetModel(sName);

	//if it exists return that model
	if (pModel)
		return pModel;

	//Else construct a new model based on this new mesh
	Mesh* pMesh = new Mesh();
	pMesh->GenerateSkybox();
	pMesh->SetName(sName);//This is just a precaution, name should match anyways
	pModel = new Model(pMesh);

	return AddModel(pModel);
}
//--- Add to render list
void ModelManager::AddSpecialToRenderList(RTSG::eBTX_SPECIALMODEL a_eSelection, matrix4 a_m4ToWorld)
{
	AddModelToRenderList(g_pShape[a_eSelection], a_m4ToWorld);
}
void ModelManager::AddSkyboxToRenderList(String a_sFileName)
{
	if (a_sFileName == "")
		return;

	String sName = "skybox_" + a_sFileName;
	//sName = RTSG::ToUppercase(sName);
	int nModelIndex = GetModelIndex(sName);

	//If I could not find it generate a new skybox and a new material to attach to it
	if (nModelIndex < 0)
	{
		//Construct a new skybox
		Mesh* pMesh = new Mesh();
		pMesh->GenerateSkybox();
		//Create a new material and attach it to the mesh
		uint matIndex = m_pMatMngr->AddMaterial(sName, a_sFileName);
		pMesh->SetMaterial(matIndex);
		//Set the new name for it
		pMesh->SetName(sName);
		//Create the model
		Model* pModel = new Model(pMesh);
		//if we couldn't make the model for whatever reason return
		if (!AddModel(pModel))
			return;
	}

	AddModelToRenderList(sName, IDENTITY_M4, eBTX_RENDER::RENDER_SOLID);
}
void ModelManager::AddPlaneToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::PLANE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniPlane(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::CUBE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniCube(a_v3Color);
	
	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddConeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::CONE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniCone(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddCylinderToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::CYLINDER, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniCylinder(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddTubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::TUBE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniTube(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddTorusToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::TORUS, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniTorus(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::SPHERE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniSphere(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddStarToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::STAR, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniStar(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddIcosahedronToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::ICOSAHEDRON, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniIcosahedron(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld, a_Render);
}
void ModelManager::AddWireCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::WIRECUBE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniWireCube(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld);
}
void ModelManager::AddWireSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color)
{
	//Try to find a model with this name
	String sName = GenerateName(ModelOrder::WIRESPHERE, a_v3Color);
	Model* pModel = GetModel(sName);

	//if the model does not exist create it
	if (!pModel)
		pModel = GenerateUniWireSphere(a_v3Color);

	AddModelToRenderList(pModel, a_m4ToWorld);
}
void ModelManager::AddLineToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Start, vector3 a_v3End, vector3 a_v3ColorStart, vector3 a_v3ColorEnd)
{
	//We calculate the orientation of the line and magnify it according to start and end
	//calculate the orientation
	vector3 vDirection = glm::normalize(a_v3End - a_v3Start);
	//Position
	vector3 v3Middle = (a_v3Start + a_v3End);
	//Size
	float fMagnitude = glm::distance(a_v3Start, a_v3End);
	//Orientation
	//quaternion qOrientation = glm::angleAxis(vDirection);// quaternion(vDirection);
	//qOrientation = glm::normalize(qOrientation);

	//http://stackoverflow.com/questions/20923232/how-to-rotate-a-vector-by-a-given-direction
	matrix3 transform;
	if (vDirection.y == 0 && vDirection.z == 0)
	{
		if (vDirection.x < 0) // rotate 180 degrees
			transform = matrix3(vector3(-1.0f, 0.0f, 0.0f),
				vector3(0.0f, -1.0f, 0.0f),
				vector3(0.0f, 0.0f, 1.0f));

		// else if direction.y >= 0, leave transform as the identity matrix.
	}
	else
	{
		vector3 new_x = glm::normalize(vDirection);
		vector3 new_z;
		if (new_x != AXIS_Y)
			new_z = glm::normalize(glm::cross(new_x, AXIS_Y));
		else
			new_z = AXIS_Z;
		vector3 new_y = glm::normalize(glm::cross(new_z, new_x));

		transform = matrix3(new_x, new_y, new_z);
	}

	//Final scale and orientation
	matrix4 m4ToWorld = glm::translate(IDENTITY_M4, a_v3Start) * matrix4(transform) * glm::scale(IDENTITY_M4, vector3(fMagnitude));

	//Use the default line
	Model* pModel = m_ModelList[ModelOrder::LINE];
	String sName = pModel->GetName();
	
	//See if we are not using a default white line
	if (a_v3ColorStart != C_WHITE ||
		a_v3ColorEnd != C_WHITE )
	{
		//If we are not then we may have to make a new line or look for one which is slower
		//instead of making all possible lines based on two points and two colors we create a 
		//unit length line based on two colors, and then we scale and orient it.
		sName = "line_(" +
			std::to_string(0.0f) + "," +
			std::to_string(0.0f) + "," +
			std::to_string(0.0f) + "," +
			std::to_string(1.0f) + "," +
			std::to_string(0.0f) + "," +
			std::to_string(0.0f) + "," +
			std::to_string(a_v3ColorStart.x) + "," +
			std::to_string(a_v3ColorStart.y) + "," +
			std::to_string(a_v3ColorStart.z) + "," +
			std::to_string(a_v3ColorEnd.x) + "," +
			std::to_string(a_v3ColorEnd.y) + "," +
			std::to_string(a_v3ColorEnd.z) + ")";
		//sName = RTSG::ToUppercase(sName);
		//Try to find a model with this name
		pModel = GetModel(sName);
		//if the model does not exist create it
		if (!pModel)
			pModel = GenerateLine(vector3(0.0f), vector3(1.0f, 0.0f, 0.0f), a_v3ColorStart, a_v3ColorEnd);

		//This is a non white to white line so we will need to look for the mesh index before printing
		AddModelToRenderList(pModel, a_m4ToWorld * m4ToWorld, RENDER_WIRE);
		return;
	}
	
	//We will send the pointer to the line model without checking to remove overhead
	//this is potentially an issue if we can't be sure of the index in the array of our line
	//but that is what the enum help us with.
	
	//this will remove the overhead of checking if its the right model
	m_ModelList[ModelOrder::LINE]->AddToRenderList(a_m4ToWorld * m4ToWorld, RENDER_WIRE);
}
void ModelManager::AddAxisToRenderList(matrix4 a_m4ToWorld)
{
	AddLineToRenderList(a_m4ToWorld, ZERO_V3, AXIS_X, C_RED, C_RED);
	AddConeToRenderList(glm::rotate(a_m4ToWorld * glm::translate(AXIS_X), -1.5708f, AXIS_Z)
						* glm::scale(vector3(0.1f)), C_RED);
	AddLineToRenderList(a_m4ToWorld, ZERO_V3, AXIS_Y, C_GREEN, C_GREEN);
	AddConeToRenderList(a_m4ToWorld * glm::translate(AXIS_Y) 
						* glm::scale(vector3(0.1f)), C_GREEN);
	AddLineToRenderList(a_m4ToWorld, ZERO_V3, AXIS_Z, C_BLUE, C_BLUE);
	AddConeToRenderList(glm::rotate(a_m4ToWorld * glm::translate(AXIS_Z), 1.5708f, AXIS_X) 
						* glm::scale(vector3(0.1f)), C_BLUE);
}
void ModelManager::AddGridToRenderList(matrix4 a_m4ToWorld)
{
	//TODO: this is really slow as we are indexing the model of a line 200 times,
	//repace with a single model created
	float fSize = 100.0f;
	float fStart = -fSize/2.0f;
	for (uint i = 0; i < 101; i++)
	{
		AddLineToRenderList(a_m4ToWorld * glm::translate(vector3(0.0f, fStart, 0.0f)), -fSize / 2.0f * AXIS_X, fSize / 2.0f * AXIS_X, C_WHITE, C_WHITE);
		AddLineToRenderList(a_m4ToWorld * glm::translate(vector3(fStart, 0.0f, 0.0f)), -fSize / 2.0f * AXIS_Y, fSize / 2.0f * AXIS_Y, C_WHITE, C_WHITE);
		fStart += 1.0f;
	}
}
void ModelManager::AddGridToRenderList()
{
	//TODO: this is really slow as we are indexing the model of a line 200 times,
	//repace with a single model created
	float fSize = 100.0f;
	float fStart = -fSize / 2.0f;
	
	BTXs::eCAMERAMODE mode = m_pCameraMngr->GetCameraMode();
	switch (mode)
	{
	default:
	case BTXs::eCAMERAMODE::CAM_PERSP:
	case BTXs::eCAMERAMODE::CAM_ORTHO_Z:
		for (uint i = 0; i < 50; i++)
		{
			AddLineToRenderList(glm::translate(vector3(0.0f, fStart, 0.0f)), -fSize / 2.0f * AXIS_X, fSize / 2.0f * AXIS_X, C_WHITE, C_WHITE);
			AddLineToRenderList(glm::translate(vector3(fStart, 0.0f, 0.0f)), -fSize / 2.0f * AXIS_Y, fSize / 2.0f * AXIS_Y, C_WHITE, C_WHITE);
			fStart += 1.0f;
		}
		AddLineToRenderList(IDENTITY_M4, -fSize / 2.0f * AXIS_X, fSize / 2.0f * AXIS_X, C_RED, C_RED);
		AddLineToRenderList(IDENTITY_M4, -fSize / 2.0f * AXIS_Y, fSize / 2.0f * AXIS_Y, C_GREEN, C_GREEN);
		AddLineToRenderList(IDENTITY_M4, -fSize / 2.0f * AXIS_Z, fSize / 2.0f * AXIS_Z, C_BLUE, C_BLUE);
		fStart += 1.0f;
		for (uint i = 51; i < 101; i++)
		{
			AddLineToRenderList(glm::translate(vector3(0.0f, fStart, 0.0f)), -fSize / 2.0f * AXIS_X, fSize / 2.0f * AXIS_X, C_WHITE, C_WHITE);
			AddLineToRenderList(glm::translate(vector3(fStart, 0.0f, 0.0f)), -fSize / 2.0f * AXIS_Y, fSize / 2.0f * AXIS_Y, C_WHITE, C_WHITE);
			fStart += 1.0f;
		}
		break;
	case BTXs::eCAMERAMODE::CAM_ORTHO_Y:
		for (uint i = 0; i < 50; i++)
		{
			AddLineToRenderList(glm::translate(vector3(0.0f, 0.0f, fStart)), -fSize / 2.0f * AXIS_X, fSize / 2.0f * AXIS_X, C_WHITE, C_WHITE);
			AddLineToRenderList(glm::translate(vector3(fStart, 0.0f, 0.0f)), -fSize / 2.0f * AXIS_Z, fSize / 2.0f * AXIS_Z, C_WHITE, C_WHITE);
			fStart += 1.0f;
		}
		AddLineToRenderList(IDENTITY_M4, -fSize / 2.0f * AXIS_X, fSize / 2.0f * AXIS_X, C_RED, C_RED);
		AddLineToRenderList(IDENTITY_M4, -fSize / 2.0f * AXIS_Z, fSize / 2.0f * AXIS_Z, C_BLUE, C_BLUE);
		fStart += 1.0f;
		for (uint i = 51; i < 101; i++)
		{
			AddLineToRenderList(glm::translate(vector3(0.0f, 0.0f, fStart)), -fSize / 2.0f * AXIS_X, fSize / 2.0f * AXIS_X, C_WHITE, C_WHITE);
			AddLineToRenderList(glm::translate(vector3(fStart, 0.0f, 0.0f)), -fSize / 2.0f * AXIS_Z, fSize / 2.0f * AXIS_Z, C_WHITE, C_WHITE);
			fStart += 1.0f;
		}
		break;
	case BTXs::eCAMERAMODE::CAM_ORTHO_X:
		for (uint i = 0; i < 50; i++)
		{
			AddLineToRenderList(glm::translate(vector3(0.0f, fStart, 0.0f)), -fSize / 2.0f * AXIS_Z, fSize / 2.0f * AXIS_Z, C_WHITE, C_WHITE);
			AddLineToRenderList(glm::translate(vector3(0.0f, 0.0f, fStart)), -fSize / 2.0f * AXIS_Y, fSize / 2.0f * AXIS_Y, C_WHITE, C_WHITE);
			fStart += 1.0f;
		}
		AddLineToRenderList(IDENTITY_M4, -fSize / 2.0f * AXIS_Y, fSize / 2.0f * AXIS_Y, C_GREEN, C_GREEN);
		AddLineToRenderList(IDENTITY_M4, -fSize / 2.0f * AXIS_Z, fSize / 2.0f * AXIS_Z, C_BLUE, C_BLUE);
		fStart += 1.0f;
		for (uint i = 51; i < 101; i++)
		{
			AddLineToRenderList(glm::translate(vector3(0.0f, fStart, 0.0f)), -fSize / 2.0f * AXIS_Z, fSize / 2.0f * AXIS_Z, C_WHITE, C_WHITE);
			AddLineToRenderList(glm::translate(vector3(0.0f, 0.0f, fStart)), -fSize / 2.0f * AXIS_Y, fSize / 2.0f * AXIS_Y, C_WHITE, C_WHITE);
			fStart += 1.0f;
		}
		break;
	}
}
void ModelManager::AddCameraToRenderList(int a_nIndex)
{
	//TODO: this is really slow as we are indexing the model of a line 200 times,
	//repace with a single model created
	//if (a_nIndex < 0)
	//{
	//	for (uint i = 0; i < m_pCameraMngr->GetCameraCount(); ++i)
	//	{
	//		if (i != m_pCameraMngr->GetActiveCamera())
	//		{
	//			matrix4 m4Camera = m_pCameraMngr->GetCameraSpace(i);

	//			vector3  v3Pos = vector3(0.0f, 0.0f, 0.45f);
	//			AddTubeToRenderList(m4Camera *
	//				glm::translate(IDENTITY_M4, v3Pos) *
	//				glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z) *
	//				glm::scale(vector3(0.4f)) *
	//				glm::translate(vector3(0.75f, 0.0f, -0.5f)),
	//				C_GREEN, RENDER_WIRE);
	//			AddTubeToRenderList(m4Camera *
	//				glm::translate(IDENTITY_M4, v3Pos) *
	//				glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z) *
	//				glm::scale(vector3(0.4f)) *
	//				glm::translate(vector3(0.75f, 0.0f, 0.5f)),
	//				C_GREEN, RENDER_WIRE);
	//			AddCubeToRenderList(m4Camera *
	//				glm::translate(IDENTITY_M4, v3Pos) *
	//				glm::scale(vector3(0.30f, 0.30f, 0.75f)) *
	//				glm::translate(vector3(0.0f, 0.0f, 0.0f)),
	//				C_GREEN, RENDER_WIRE);
	//			AddConeToRenderList(m4Camera *
	//				glm::translate(IDENTITY_M4, v3Pos) *
	//				glm::rotate(IDENTITY_M4, 1.5708f, AXIS_X) *
	//				glm::translate(IDENTITY_M4, vector3(0.0f, -0.45f, 0.0f)) *
	//				glm::scale(IDENTITY_M4, vector3(0.5f)),
	//				C_GREEN, RENDER_WIRE);
	//		}
	//	}
	//}
	//else
	//{
	//	if (a_nIndex != m_pCameraMngr->GetActiveCamera())
	//	{
	//		matrix4 m4Camera = m_pCameraMngr->GetCameraSpace(a_nIndex);

	//		vector3  v3Pos = vector3(0.0f, 0.0f, 0.45f);
	//		AddTubeToRenderList(m4Camera *
	//			glm::translate(IDENTITY_M4, v3Pos) *
	//			glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z) *
	//			glm::scale(vector3(0.4f)) *
	//			glm::translate(vector3(0.75f, 0.0f, -0.5f)),
	//			C_GREEN, RENDER_WIRE);
	//		AddTubeToRenderList(m4Camera *
	//			glm::translate(IDENTITY_M4, v3Pos) *
	//			glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z) *
	//			glm::scale(vector3(0.4f)) *
	//			glm::translate(vector3(0.75f, 0.0f, 0.5f)),
	//			C_GREEN, RENDER_WIRE);
	//		AddCubeToRenderList(m4Camera *
	//			glm::translate(IDENTITY_M4, v3Pos) *
	//			glm::scale(vector3(0.30f, 0.30f, 0.75f)) *
	//			glm::translate(vector3(0.0f, 0.0f, 0.0f)),
	//			C_GREEN, RENDER_WIRE);
	//		AddConeToRenderList(m4Camera *
	//			glm::translate(IDENTITY_M4, v3Pos) *
	//			glm::rotate(IDENTITY_M4, 1.5708f, AXIS_X) *
	//			glm::translate(IDENTITY_M4, vector3(0.0f, -0.45f, 0.0f)) *
	//			glm::scale(IDENTITY_M4, vector3(0.5f)),
	//			C_GREEN, RENDER_WIRE);
	//	}
	//}
}
bool ModelManager::IsModelInMap(String a_sName)
{
	return (GetModel(a_sName) != nullptr);
}
bool ModelManager::IsModelInMap(Model* pModel)
{
	//look for the value instead of the key
	for (auto it = m_ModelMap.begin(); it != m_ModelMap.end(); ++it)
		if (it->second == pModel)
			return true;
	return false;
}
int ModelManager::GetModelIndex(String a_sName)
{
	//Get the count of the model to iterate one by one
	uint uCount = GetModelCount();
	for (uint i = 0; i < uCount; ++i)
	{
		//If we find the model with that name return the index
		if (m_ModelList[i]->GetName() == a_sName)
			return static_cast<int>(i);
	}
	//we couldnt find it return -1
	return -1;
}
Model* ModelManager::GetModel(String a_sName)
{
	//If no name provided return
	if (a_sName == "")
		return nullptr;

	//a_sName = RTSG::ToUppercase(a_sName);

	//Look for the name in the model map
	auto it = m_ModelMap.find(a_sName);
	//If found
	if (it != m_ModelMap.end())
	{
		//return the entry
		return it->second;
	}

	//If you couldn't find the model it might be missing the full
	//address of the model so check for that
	//Get the extension of the file and send it to uppercase
	String sExtension = FileReader::GetExtension(a_sName);
	sExtension = RTSG::ToUppercase(sExtension);

	//Check if the file exists and is a known format
	FolderSingleton* pFolder = FolderSingleton::GetInstance();
	String sFileName = pFolder->GetFolderRoot();
	sFileName += pFolder->GetFolderData();
	if (sExtension == "OBJ")
	{
		sFileName += pFolder->GetFolderMOBJ();
	}
	//else if (sExtension == "BTO" || sExtension == "ATO")
	//{
	//	sFileName += pFolder->GetFolderMBTO();
	//}

	sFileName += a_sName;

	//sFileName = RTSG::ToUppercase(sFileName);
	it = m_ModelMap.find(sFileName);
	//If found
	if (it != m_ModelMap.end())
	{
		//return the entry
		return it->second;
	}

	return nullptr;
}
uint ModelManager::GetModelCount(void) { return m_ModelList.size(); }
void ModelManager::ClearRenderList(void)
{
	uint nModels = GetModelCount();
	for (uint i = 0; i < nModels; i++)
	{
		m_ModelList[i]->ClearRenderLists();
	}
	//for (auto it = m_renderOptionsList.begin(); it != m_renderOptionsList.end(); ++it)
	//{
	//	(*it)->clear();
	//}
	//Mesh::ResetRenderCallCount();
}
void ModelManager::AddModelToRenderList(String a_sModelName, matrix4 a_m4Transform, int a_nRender)
{
	/*
	* GetModel will return a nullptr if the string is empty and AddModelToRenderList 
	* by pointer checks for a nullptr so we delegate the check to it
	*/
	AddModelToRenderList(GetModel(a_sModelName), a_m4Transform, a_nRender);
}
void ModelManager::AddModelToRenderList(Model* pModel, matrix4 a_m4Transform, int a_RenderOption)
{
	//Check if a model is provided
	if (!pModel)
		return;

	//Known issues: if the model is not part of the list it will add to its render list
	//but it will never be cleared
	pModel->AddToRenderList(a_m4Transform, a_RenderOption);
	
	//Safer but slower version
	////Check if model is in the list of models
	//int index = GetModelIndex(pModel->GetName());
	////if the model is not in the list of models return
	//if (index < 0)
	//	return;
	//
	////Add the model to the list of objects to render
	//m_ModelList[index]->AddToRenderList(a_m4Transform, a_RenderOption);
}
String ModelManager::LoadModel(String a_sFileName)
{

	//Check if model exists already
	Model* pModel = GetModel(a_sFileName);
	
	//If it does just return its name
	if(pModel)
		return pModel->GetName();
	
	//If it doesn't, make a new model and load it 
	pModel = new Model(a_sFileName);
	
	//If it wasn't able to load return empty string
	if (pModel->GetName() == "")
		return "";

	//Add this model pointer to the list
	pModel = AddModel(pModel);

	//return the name of the model
	return pModel->GetName();
}
uint ModelManager::Render(void)
{
	//If no custom matrices where provided we use the camera manager's
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	vector3 v3CameraPosition = m_pCameraMngr->GetPosition();
	return Render(m4Projection, m4View, v3CameraPosition);
}
uint ModelManager::Render(matrix4 a_m4Projection, matrix4 a_m4View, vector3 a_v3CameraPosition)
{
	//TODO: sort skyboxes first otherwise semi transp models dont render using that data
	uint uRenderCalls = 0;
	uint uCount = GetModelCount();
	// Render Solids
	for (uint i = 0; i < uCount; ++i)
	{
		uRenderCalls += m_ModelList[i]->RenderLists(a_m4Projection, a_m4View, a_v3CameraPosition);
	}

	return uRenderCalls;
}
//---
std::vector<String> ModelManager::GetModelNames(void)
{
	std::vector<String> output;
	uint uModels = m_ModelList.size();
	for (uint i = 0; i < uModels; ++i)
	{
		String sName = m_ModelList[i]->GetName();
		output.push_back(sName);
	}
	return output;
}
std::vector<vector3> ModelManager::GetVertexList(String a_sName)
{
	Model* pModel = GetModel(a_sName);
	if (!pModel)
	{
		std::vector<vector3> pTemp;
		return pTemp;
	}
	return pModel->GetVertexList();
}
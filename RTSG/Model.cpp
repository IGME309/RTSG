#include "RTSG\Mesh\Model.h"
using namespace RTSG;

Model::Model(Mesh* a_pMesh)
{
	if (!a_pMesh)
		return;

	Init();
	m_sFileName = a_pMesh->GetName();
	m_MeshList.push_back(a_pMesh);
}
Model::Model(String a_sFileName, bool a_bIsModelFile)
{
	//If we didnt provide a file to load we make an empty model
	if (a_sFileName == "")
	{
		return;
	}
	if (!a_bIsModelFile)
	{
		m_sFileName = a_sFileName;
		return;
	}

	//Get the extension of the file and send it to uppercase
	String sExtension = FileReader::GetExtension(a_sFileName);
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
	else
		return;

	sFileName += a_sFileName;

	if (!FileReader::FileExists(sFileName))
		return;
	
	Init();
	//Read the file
	m_sFileName = Load(sFileName);

	//m_sFileName = RTSG::ToUppercase(sFileName);
}
//Model wont copy themselves, nothing to do on copy assignment or copy constructor
Model::Model(Model const& other) {}
Model& Model::operator=(Model const& other) { return *this; }
void RTSG::Model::Swap(Model& other) {}
RTSG::Model::~Model(void)
{
	Release();
}
void RTSG::Model::Release(void)
{
	//Deallocate all Mesh pointers in the list of mesh that make this model
	uint uMeshCount = m_MeshList.size();
	for (uint i = 0; i < uMeshCount; i++)
	{
		if (m_MeshList[i])
		{
			delete m_MeshList[i];
			m_MeshList[i] = nullptr;
		}
	}
	ClearRenderLists();
	m_MeshList.clear();
}
void Model::Init(void)
{
	m_sFileName = "";
	m_pMatMngr = MaterialManager::GetInstance();
	m_sMaterialAppend = "";
}
String Model::Load(String a_sFileName)
{
	String sExtension = FileReader::GetExtension(a_sFileName);
	sExtension = RTSG::ToUppercase(sExtension);
	
	if ("OBJ" == sExtension)
	{
		return LoadOBJ(a_sFileName);
	}
	return "_|_ExtensionUnknown";
}
void Model::LoadMTL(String a_sFileName)
{
	FileReader reader;
	eBTX_OUTPUT result = reader.ReadFile(a_sFileName);
	if (result != eBTX_OUTPUT::OUT_ERR_NONE)
		return;

	reader.Rewind();
	int nMaterial = -1;
	m_sMaterialAppend = "|" + a_sFileName;
	while (reader.ReadNextLine() != eBTX_OUTPUT::OUT_DONE)
	{
		char* sTemp = new char[reader.m_sLine.size() + 1];
		String sWord = reader.GetFirstWord();

		if (sWord == "newmtl")
		{
			sscanf_s(reader.m_sLine.c_str(), "newmtl %s", sTemp, reader.m_sLine.size());
			String sTempMaterial = sTemp;
			sTempMaterial += m_sMaterialAppend;
			//oMutex.lock();
			//There is no need to identify the material, add material will identify it as well if already added
			//nMaterial = m_pMatMngr->IdentifyMaterial(sTempMaterial);
			//if (nMaterial == -1)
			//m_uMaterialCount++;
			nMaterial = m_pMatMngr->AddMaterial(sTempMaterial);
			//oMutex.unlock();
			//create a mesh and name it as the material it will use
			Mesh* pMesh = new Mesh();
			pMesh->SetMaterial(nMaterial);
			pMesh->SetName(sTempMaterial);
			m_MeshList.push_back(pMesh);
		}
		else if (sWord == "map_Kd")
		{
			sscanf_s(reader.m_sLine.c_str(), "map_Kd %s", sTemp, reader.m_sLine.size());
			//oMutex.lock();
			m_pMatMngr->m_materialList[nMaterial]->SetDiffuseMapName(static_cast<String>(sTemp));
			//oMutex.unlock();
		}
		else if (sWord == "bump")
		{
			sscanf_s(reader.m_sLine.c_str(), "bump %s", sTemp, reader.m_sLine.size());
			//oMutex.lock();
			m_pMatMngr->m_materialList[nMaterial]->SetNormalMapName(static_cast<String>(sTemp));
			//oMutex.unlock();
		}
		else if (sWord == "map_Ks")
		{
			sscanf_s(reader.m_sLine.c_str(), "map_Ks %s", sTemp, reader.m_sLine.size());
			//oMutex.lock();
			m_pMatMngr->m_materialList[nMaterial]->SetSpecularMapName(static_cast<String>(sTemp));
			//oMutex.unlock();
		}
		else if (sWord == "Kd")
		{
			float r = 0;
			float g = 0;
			float b = 0;
			sscanf_s(reader.m_sLine.c_str(), "Kd %f %f %f", &r, &g, &b);
			vector3 color(r, g, b);
			//oMutex.lock();
			m_pMatMngr->m_materialList[nMaterial]->SetDiffuse(color);
			//oMutex.unlock();
		}
		delete[] sTemp;
	}

	reader.CloseFile();

	return;
}
Mesh* Model::IdentifyMeshByMaterialIndex(uint a_uMaterialIndex)
{
	uint uMeshCount = m_MeshList.size();
	for (uint i = 0; i < uMeshCount; i++)
	{
		if(m_MeshList[i]->GetMaterialIndex() == a_uMaterialIndex)
			return m_MeshList[i];
	}
	return nullptr;
}
String Model::LoadOBJ(String a_sFileName)
{
	FileReader reader;
	String sAbsoluteRoute = a_sFileName;
	eBTX_OUTPUT result = reader.ReadFile(a_sFileName);
	if (result != eBTX_OUTPUT::OUT_ERR_NONE)
	{
		printf("Model %s could not be found.\n", sAbsoluteRoute.c_str());
		reader.CloseFile();
		return "_|_FileNotFound";
	}
	reader.CloseFile();

	result = reader.ReadBinaryFile(sAbsoluteRoute);
	String sAbsoluteFolder = reader.GetAbsoluteRoute(sAbsoluteRoute);

	SystemSingleton* pSystem = SystemSingleton::GetInstance();

	uint nClock = pSystem->GenClock();
	pSystem->StartClock(nClock);

	reader.Rewind();
	std::vector<vector3> v4Position; //Vector of Vertices
	std::vector<vector3> vNormal; //Vector of Normals
	std::vector<vector3> vUV; //vector of UVS
	int nMaterial = 0;
	String sCurrentGroup = "";
	String sCurrentMaterial = "";
	String sCurrentMesh = "";
	int nCurrentMeshIndex = -1;
	while (reader.ReadNextLine() != OUT_DONE)
	{
		
		char* sTemp = new char[reader.m_sLine.size() + 1];
		String sWord = reader.GetFirstWord();
		
		
#pragma region Material Library
		if (sWord == "mtllib")
		{
			sscanf_s(reader.m_sLine.c_str(), "mtllib %s", sTemp, reader.m_sLine.size());
			LoadMTL(static_cast<String>(sAbsoluteFolder + sTemp));
		}
#pragma endregion
#pragma region Vertex
		else if (reader.m_sLine[0] == 'v')
		{
			float x = 0.0f, y = 0.0f, z = 0.0f;
			if (reader.m_sLine[1] == ' ')
			{
				sscanf_s(reader.m_sLine.c_str(), "v %f %f %f", &x, &y, &z);
				v4Position.push_back(vector3(x, y, z));
			}
			else if (reader.m_sLine[1] == 't')
			{
				sscanf_s(reader.m_sLine.c_str(), "vt %f %f", &x, &y);
				vUV.push_back(vector3(x, y, 0));
			}
			else if (reader.m_sLine[1] == 'n')
			{
				sscanf_s(reader.m_sLine.c_str(), "vn %f %f %f", &x, &y, &z);
				vNormal.push_back(vector3(x, y, z));
			}
		}
#pragma endregion
#pragma region Group
		else if (reader.m_sLine[0] == 'g')
		{
			/*
			* To keep things simple groups will be handled through materials,
			* in a regular obj a group will contain an array of faces and each
			* face can have a separate material, in this implementation
			* faces with the same material will be grouped together. In short
			* each material will be a new Mesh* in the list
			*/
		}

#pragma endregion
#pragma region Material
		
		else if (sWord == "usemtl")
		{
			//if we are reading a use material line
			sscanf_s(reader.m_sLine.c_str(), "usemtl %s", sTemp, reader.m_sLine.size());
			String sTempMaterial = sTemp;
			sTempMaterial += m_sMaterialAppend;
			sCurrentMaterial = sTempMaterial;
			//try to find the material to use
			nMaterial = m_pMatMngr->IdentifyMaterial(sTempMaterial);
			//if the material was not found use the DEFAULT_V3NEG material
			if (nMaterial < 0)
				nMaterial = 0;
		}
#pragma endregion
#pragma region Faces
		else if (reader.m_sLine[0] == 'f')
		{
			/*
			* Error control:
			* Some OBJ files will not define the group we are working at or the material we are using
			* we need to create a DEFAULT_V3NEG material to use. This probably happen if the mtllib
			* was not used so no meshes would have been created at that point to.
			*/
						
			//if we didnt have a material we use the DEFAULT_V3NEG one
			if (sCurrentMaterial == "")
			{
				if (m_MeshList.size() == 0)
				{
					Mesh* pMesh = new Mesh();
					pMesh->SetMaterial(0);
					m_MeshList.push_back(pMesh);
				}
			}
			//if we didn't have a mesh with this material we make a new one
			Mesh* pMesh = IdentifyMeshByMaterialIndex(nMaterial);
			if (!pMesh)
			{
				Mesh* pMesh = new Mesh();
				pMesh->SetMaterial(0);
				m_MeshList.push_back(pMesh);
			}

			int nP = 0, nT = 0, nN = 0;

			String temp = reader.m_sLine.c_str();
			int size = temp.size() + 1;
			char* str = nullptr;
			str = new char[size];
			if (str == nullptr)
			{
				Release();
				return "_|_Failed to reserve memory_"; //couldnt reserve memory
			}

			//This replaces strcpy which is failing
			for (int i = 0; i < size - 1; i++)
				str[i] = temp[i];
			str[size - 1] = '\0';

			//Inspect how many points are given to create a face
			//(usually just 3 but if more, this takes care of it)
			int nVertices = 0;
			char* pch;
			pch = strtok(str, "f ");
			while (pch != NULL)
			{
				nVertices++;
				pch = strtok(NULL, "f ");
			}

			//Now that we know how many vertices we have we know how many times we need to read the line
			for (int j = 0; j < nVertices - 2; j++)
			{
				//This replaces strcpy which is failing
				for (int i = 0; i < size - 1; i++)
					str[i] = temp[i];
				str[size - 1] = '\0';

				//We will divide the line in /%d/%d/%d so we can read the individual vertex info
				//It is obvious at this point that reading triangulated models is faster (as it only needs
				//to read each face once)
				pch = strtok(str, "f ");
				int nIndex = 0;
				while (pch != NULL)
				{
					if (nIndex == 0)
					{
						sscanf_s(pch, "%d/%d/%d", &nP, &nT, &nN);
						pMesh->AddVertexPosition(v4Position[nP - 1]);
						pMesh->AddVertexColor(m_pMatMngr->m_materialList[nMaterial]->GetDiffuse());
						pMesh->AddVertexUV(vUV[nT - 1]);
						pMesh->AddVertexNormal(vNormal[nN - 1]);
					}
					else if (nIndex + j == nVertices - 2)
					{
						sscanf_s(pch, "%d/%d/%d", &nP, &nT, &nN);
						pMesh->AddVertexPosition(v4Position[nP - 1]);
						pMesh->AddVertexColor(m_pMatMngr->m_materialList[nMaterial]->GetDiffuse());
						pMesh->AddVertexUV(vUV[nT - 1]);
						pMesh->AddVertexNormal(vNormal[nN - 1]);
					}
					else if (nIndex + j == nVertices - 1)
					{
						sscanf_s(pch, "%d/%d/%d", &nP, &nT, &nN);
						pMesh->AddVertexPosition(v4Position[nP - 1]);
						pMesh->AddVertexColor(m_pMatMngr->m_materialList[nMaterial]->GetDiffuse());
						pMesh->AddVertexUV(vUV[nT - 1]);
						pMesh->AddVertexNormal(vNormal[nN - 1]);
					}
					pch = strtok(NULL, "f ");
					nIndex++;
				}
			}

			if (str != nullptr)
			{
				delete str;
				str = nullptr;
			}

		}
#pragma endregion
	}
	reader.CloseFile();
	//Once we read all the file and added information on all the meshes we need to compile each of them
	//ComposeGroups();
	//oMutex.lock();
	m_pMatMngr->ReloadMaps();
	CompileMeshes();
	//oMutex.unlock();
	//GetModelsMap();

	m_sFileName = a_sFileName;
	printf("Model: %s \n", sAbsoluteRoute.c_str());
	printf("               loaded in %.4f seconds.\n", pSystem->GetDeltaTime(nClock));
	return m_sFileName;
}
void Model::CompileMeshes(void)
{
	uint uMeshCount = m_MeshList.size();
	for (uint i = 0; i < uMeshCount; i++)
	{
		m_MeshList[i]->CompileOpenGL3X();
	}
}
uint Model::RenderLists(matrix4 a_m4Projection, matrix4 a_m4View, vector3 a_v3CameraPosition)
{
	//Get all the matrices sent for the model and count them
	uint uRenderCalls = 0;
	//Solid
	uint uSolids = m_RenderListSolid.size();
	if (uSolids > 0)
	{
		//reserve memory to place all matrices in a contiguous array of 16 positions
		float* fSolidArray = new float[16 * uSolids];
		for (uint j = 0; j < uSolids; ++j)
		{
			const float* m4MVP = glm::value_ptr(m_RenderListSolid[j]);
			memcpy(&fSolidArray[j * 16], m4MVP, 16 * sizeof(float));
		}

		//render
		uRenderCalls += Render(a_m4Projection, a_m4View, fSolidArray, uSolids, 
			a_v3CameraPosition, eBTX_RENDER::RENDER_SOLID);

		//Once I render, deallocate the array
		if (fSolidArray)
		{
			delete[] fSolidArray;
			fSolidArray = nullptr;
		}
	}

	//Wires
	uint uWires = m_RenderListWire.size();
	if (uWires > 0)
	{
		//reserve memory to place all matrices in a contiguous array of 16 positions
		float* fWireArray = new float[16 * uWires];
		for (uint j = 0; j < uWires; ++j)
		{
			const float* m4MVP = glm::value_ptr(m_RenderListWire[j]);
			memcpy(&fWireArray[j * 16], m4MVP, 16 * sizeof(float));
		}

		//render
		uRenderCalls += Render(a_m4Projection, a_m4View, fWireArray, uWires, 
			a_v3CameraPosition, eBTX_RENDER::RENDER_WIRE);

		//Once I render, deallocate the array
		if (fWireArray)
		{
			delete[] fWireArray;
			fWireArray = nullptr;
		}
	}
	return uRenderCalls;
}
uint Model::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mWorld,
	vector3 a_v3CameraPosition, int a_RenderOption)
{
	uint uRenderCalls = 0;
	uint uMeshCount = m_MeshList.size();
	for (uint i = 0; i < uMeshCount; i++)
	{
		uRenderCalls += m_MeshList[i]->Render(a_mProjection, a_mView, a_mWorld, 
			a_v3CameraPosition, a_RenderOption);
	}
	return uRenderCalls;
}
uint Model::Render(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances,
	vector3 a_v3CameraPosition, int a_RenderOption)
{
	uint uRenderCalls = 0;
	uint uMeshCount = m_MeshList.size();
	for (uint i = 0; i < uMeshCount; i++)
	{
		uRenderCalls += m_MeshList[i]->Render(a_mProjection, a_mView, a_fMatrixArray, a_nInstances,
			a_v3CameraPosition, a_RenderOption);
	}
	return uRenderCalls;
}
String Model::GetName(void) { return m_sFileName; }
void Model::AddToRenderList(matrix4 a_m4Transform, int a_RenderOption)
{
	if (a_RenderOption & eBTX_RENDER::RENDER_SOLID)
	{
		m_RenderListSolid.push_back(a_m4Transform);
	}
	if (a_RenderOption & eBTX_RENDER::RENDER_WIRE)
	{
		m_RenderListWire.push_back(a_m4Transform);
	}
}
std::vector<matrix4> Model::GetRenderListSolids(void) {	return m_RenderListSolid; }
std::vector<matrix4> Model::GetRenderListWires(void) { return m_RenderListWire; }
void Model::ClearRenderLists(void)
{
	m_RenderListSolid.clear();
	m_RenderListWire.clear();
}
void Model::SetName(String a_sName) { m_sFileName = a_sName; }
std::vector<vector3> Model::GetVertexList()
{
	uint uMeshCount = m_MeshList.size();
	std::vector<vector3> output;
	for (uint i = 0; i < uMeshCount; i++)
	{
		std::vector<vector3> temp = m_MeshList[i]->GetVertexList();
		output.insert(output.end(), temp.begin(), temp.end());
	}
	return output;
}

void  Model::GeneratePlane(float a_fSize, vector3 a_v3Color, matrix4 a_m4Transform)
{
	Mesh* pMesh = new Mesh();
	pMesh->GeneratePlane(a_fSize, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateCube(float a_fSize, vector3 a_v3Color, matrix4 a_m4Transform)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCube( a_fSize, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCone(a_fRadius, a_fHeight, a_nSubdivisions, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCylinder( a_fRadius, a_fHeight, a_nSubdivisions, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTube(a_fOuterRadius, a_fInnerRadius, a_fHeight, a_nSubdivisions, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTorus( a_fOuterRadius, a_fInnerRadius, a_nSubdivisionHeight, a_nSubdivisionAxis, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateSphere( a_fRadius, a_nSubdivisions, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateIcosahedron(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateIcosahedron( a_fRadius, a_nSubdivisions, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateWireCube(float a_fSize, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateWireCube(a_fSize, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateWireSphere(float a_fRadius, vector3 a_v3Color, matrix4 a_m4Transform)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateWireSphere(a_fRadius, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateSkybox(void)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateSkybox();
	m_MeshList.push_back(pMesh);
}
void Model::GenerateLine(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3ColorStart, vector3 a_v3ColorEnd)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateLine( a_v3Start, a_v3End, a_v3ColorStart, a_v3ColorEnd);
	m_MeshList.push_back(pMesh);
}
void Model::GenerateStar(uint a_uSubdivisions, float fRadius1, float fRadius2, vector3 a_v3Color, matrix4 a_m4Transform)
{ 
	Mesh* pMesh = new Mesh();
	pMesh->GenerateStar( a_uSubdivisions, fRadius1, fRadius2, a_v3Color, a_m4Transform);
	m_MeshList.push_back(pMesh);
}
void Model::SetLineWidth(float a_fLineWidth)
{
	uint uCount = m_MeshList.size();
	for (uint i = 0; i < uCount; i++)
	{
		m_MeshList[i]->SetLineWidth(a_fLineWidth);
	}
}
#include "RTSG\System\FolderSingleton.h"
using namespace RTSG;
//  Folder
FolderSingleton* FolderSingleton::m_pInstance = nullptr;
FolderSingleton* FolderSingleton::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new FolderSingleton();
	}
	return m_pInstance;
}
FolderSingleton::FolderSingleton(void){Init();}
FolderSingleton::FolderSingleton(FolderSingleton const& other){}
FolderSingleton& FolderSingleton::operator=(FolderSingleton const& other) { return *this; }
FolderSingleton::~FolderSingleton(void){Release();};
void FolderSingleton::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//--- Non Standard Singleton Methods
void FolderSingleton::Release(void) { }
void FolderSingleton::Init(void)
{
	m_sRoot = GetRealProgramPath();
	if( IsDebuggerPresent() )
	{
		int nSize = m_sRoot.size();
		nSize -= 9;
		char* temporal = new char[nSize + 1];
		int i;
		for(i = 0; i < nSize; i++)
		{
			temporal[i] = m_sRoot[i];
		}
		temporal[i] = '\0';
		m_sRoot = temporal;
		delete[] temporal;
		m_sRoot += "_Binary\\";
	}
	m_sData = "Data\\";
	m_sAudio = "Audio\\";
	m_sBTO = "MBTO\\";
	m_sOBJ = "MOBJ\\";
	m_sTextures = "Textures\\";
	m_sShaders = "Shaders\\";
}
String FolderSingleton::GetRealProgramPath(void)
{
	TCHAR stCurrentDir[MAX_PATH];
	//Get the Program Path, the directory on which the program lives
	GetModuleFileName( 0, stCurrentDir, MAX_PATH);
	char* zsTemp1 = new char[MAX_PATH];
	if(!zsTemp1)
		return NULL;
	strcpy_s(zsTemp1, MAX_PATH, "");
	int nCounter = 0;
	while(stCurrentDir[nCounter] != 0)
	{
		zsTemp1[nCounter] = static_cast<char> (stCurrentDir[nCounter]);
		nCounter++;
	}
	zsTemp1[nCounter] = 0;
	
	// Count backwards until a slash is found or zero
	while(nCounter > 0)
	{
		if(zsTemp1[nCounter] == '\\')
			break;
		nCounter--;
	}
	char* zsTemp2 = new char[nCounter +2];
	if(!zsTemp2)
		return NULL;
	for(int n = 0; n < nCounter +1; n++)
	{
		zsTemp2[n] = zsTemp1[n];
	}
	zsTemp2[nCounter+1] = 0;
	delete[] zsTemp1;
	zsTemp1 = 0;
	String output = static_cast<String> (zsTemp2);
	delete[] zsTemp2;
	zsTemp2 = 0;
	
	return output;
}

//m_sRoot
void FolderSingleton::SetFolderRoot(String input) {  m_sRoot = input; }
String FolderSingleton::GetFolderRoot(void) { return m_sRoot; }

//m_sData
void FolderSingleton::SetFolderData(String input) { m_sData = input; }
String FolderSingleton::GetFolderData(void) { return m_sData; }

//m_sTextures
void FolderSingleton::SetFolderAudio(String input) { m_sAudio = input; }
String FolderSingleton::GetFolderAudio(void) { return m_sAudio; }

//m_sTextures
void FolderSingleton::SetFolderTextures(String input) { m_sTextures = input; }
String FolderSingleton::GetFolderTextures(void) { return m_sTextures; }

//m_sShaders
void FolderSingleton::SetFolderShaders(String input) { m_sShaders = input; }
String FolderSingleton::GetFolderShaders(void) { return m_sShaders; }

//m_sMBTO
void FolderSingleton::SetFolderMBTO(String input) { m_sBTO = input; }
String FolderSingleton::GetFolderMBTO(void) { return m_sBTO; }

//m_sMOBJ
void FolderSingleton::SetFolderMOBJ(String input) { m_sOBJ = input; }
String FolderSingleton::GetFolderMOBJ(void) { return m_sOBJ; }
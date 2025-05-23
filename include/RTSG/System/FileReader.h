/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __FILEREADERCLASS_H_
#define __FILEREADERCLASS_H_

#include "RTSG\System\SystemSingleton.h"

namespace RTSG
{

//FileReader class
class BTXDLL FileReader
{
	SystemSingleton* m_pSystem = nullptr; //System pointer
	FILE* m_pFile; //File pointer
	std::ifstream m_iStream;
	std::ofstream m_oStream;

public:
	String m_sLine = ""; //Line of file
	String m_sFirstWord = "";

	/*
	USAGE: constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	FileReader(void);
	/*
	USAGE: Copy constructor
	ARGUMENTS:
	OUTPUT:
	*/
	FileReader(const FileReader& other);
	/*
	USAGE: Copy assignment operator
	ARGUMENTS:
	OUTPUT:
	*/
	FileReader& operator=(const FileReader& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~FileReader(void);	
	/*
	USAGE: Deallocate object from memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Rewinds the file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Rewind(void) const;
	/*
	USAGE: Reads Files and allocates it on the string
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT ReadFile(String a_sFileName);
	/*
	USAGE: Saves a file with the specified name and location
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT SaveFile(String a_sFileName);
	/*
	USAGE: Saves a file in binary mode
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT SaveBinaryFile(String a_sFileName);
	/*
	USAGE: Reads Binary Files
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT ReadBinaryFile(String a_sFileName);
	/*
	USAGE: closes the file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CloseFile(void);
	/*
	USAGE: writes a line of the file and saves it in the string
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT WriteLine(String a_sStringInput);
	/*
	USAGE: writes a line of the file and saves it in the char array
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT WriteLine(const char * _Format, ...);	
	/*
	USAGE: writes on the same line of the file and saves it in the string
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT Write(String a_sStringInput);
	/*
	USAGE: writes on the same line of the file and saves it in the char array
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT Write(const char * _Format, ...);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteInt(int input);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteFloat(float input);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteBool(bool input);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void WriteString(String input);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int ReadInt(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float ReadFloat(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool ReadBool(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String ReadString(void);
	/*
	USAGE: Removes all tabs from the string (it makes regular spaces)
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT RemoveTabs(String* a_sInput);
	/*
	USAGE: reads a line of the file and saves it in the string
	ARGUMENTS:
	OUTPUT: will return BTO_OUTPUT::OUT_DONE when done
		OR OUT_RUNNING when running
	*/
	eBTX_OUTPUT ReadNextLine(bool a_bSkipComments = true);
	/*
	USAGE: Removes the blank spaces of the line
		Modified by AndrewWilkinson88@gmail.com
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT RemoveBlanks(char** a_szInput);
	/*
	USAGE: Removes the blank spaces of the line and returns a new copy
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT RemoveBlanks(char* a_szInput);
	/*
	USAGE: Removes the blank spaces of the line and returns a new copy
	ARGUMENTS:
	OUTPUT:
	*/
	eBTX_OUTPUT RemoveBlanks(String* a_sInput);
	/*
	USAGE: Gets the first word of the line
	ARGUMENTS:
	OUTPUT:
	*/
	String GetFirstWord(bool a_bToUpper = false);
	/*
	USAGE: Gets a file name from a explorer window
	ARGUMENTS:
	OUTPUT:
	*/
	String RetriveFileNameFromExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;
	/*
	USAGE: Tells a file name from explorer window
	ARGUMENTS:
	OUTPUT:
	*/
	String IndicateFileNameOnExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;
	/*
	USAGE: Gets the filename with extension from the name
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetFileNameAndExtension(String a_sFileName);
	/*
	USAGE: Gets the filename from the name
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetFileName(String a_sFileName);
	/*
	USAGE: Gets the extension from the filename
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetExtension(String a_sFileName);
	/*
	USAGE: Gets the absolute route from a file name
	ARGUMENTS:
	OUTPUT:
	*/
	static String GetAbsoluteRoute(String a_sFileName);
	/*
	USAGE:  Returns the string in uppercase 
	ARGUMENTS:
	OUTPUT:
	*/
	static String ToUpper(String a_sInput);
	/*
	USAGE: Checks for the existence of the file specified in the input string
	ARGUMENTS:
		String a_sFileName -> File to open
	OUTPUT:
		bool -> File exists?
	*/
	static bool FileExists(String a_sFileName);
private:
	/*
	USAGE: Initializes the variables of the object
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class BTXDLL std::vector<FileReader>;
EXPIMP_TEMPLATE template class BTXDLL std::vector<FileReader*>;

} //namespace STR

#endif //__FILEREADERCLASS_H_

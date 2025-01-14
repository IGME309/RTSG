#include "RTSG\System\Definitions.h"
using namespace RTSG;

BTXDLL matrix4 RTSG::ToMatrix4(quaternion a_qInput)
{
	return glm::mat4_cast(a_qInput);
}

BTXDLL String RTSG::ToUppercase(String a_sInput)
{
	std::locale loc;
	std::string out;
	for (std::string::size_type i = 0; i < a_sInput.length(); ++i)
		out += std::toupper(a_sInput[i], loc);
	return out;
}

BTXDLL String RTSG::CopyAfterToken(String a_sInput, char a_sToken)
{
	uint counter = 0;
	uint charCount = a_sInput.size();
	while (a_sInput[counter] != a_sToken && counter < charCount)
	{
		++counter;
	}
	if (counter == charCount)
		return a_sInput;

	char* szOutput = new char[a_sInput.size() + 1];
	int nSecond = 0;
	++counter;
	while (counter < charCount)
	{
		szOutput[nSecond] = a_sInput[counter];
		++counter;
		++nSecond;
	}
	szOutput[nSecond] = '\0';
	String output = szOutput;
	if (szOutput)
	{
		delete[] szOutput;
		szOutput = nullptr;
	}
	return output;
}
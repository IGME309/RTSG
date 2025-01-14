// Include standard headers
#include "Main.h"

int main(void)
{
	Application* pApp = new Application();
	pApp->Init("", RTSG::eBTX_RESOLUTIONS::RES_C_1920x1080_16x9_FULLHD, false, false);
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}
// Include standard headers
#include "Main.h"

int main(void)
{
	Application* pApp = new Application();
	pApp->Init("", RTSG::eBTX_RESOLUTIONS::RES_S_800, false, false);
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}
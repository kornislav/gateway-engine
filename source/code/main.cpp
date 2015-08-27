#include <Global.h>
#include <System/Core.h>

int main()
{
	Core* core = new Core();
	core->Init(1280, 720);
	core->Destroy();
	delete core;
	return 0;
}

#ifdef WIN32
int APIENTRY WinMain(HINSTANCE /*instance*/, HINSTANCE /*prev_instance*/, LPSTR /*args*/, int /*startup_info*/)
{
	return main();
}
#endif

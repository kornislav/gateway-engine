#include <Global.h>
#include <System/Core.h>

int main(int argc, char** argv)
{
	Core* core = new Core(argc, argv);
	core->Init(1280, 720);
	core->Run();
	core->Destroy();
	delete core;
	return 0;
}

#ifdef WIN32
int APIENTRY WinMain(HINSTANCE /*instance*/, HINSTANCE /*prev_instance*/, LPSTR /*args*/, int /*startup_info*/)
{
	return main(__argc, __argv);
}
#endif

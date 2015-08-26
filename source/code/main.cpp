#include <windows.h>

int main()
{
#ifdef WIN32
	HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));
#endif

	return 0;
}

int APIENTRY WinMain(HINSTANCE /*instance*/, HINSTANCE /*prev_instance*/, LPSTR /*args*/, int /*startup_info*/)
{
	return main();
}
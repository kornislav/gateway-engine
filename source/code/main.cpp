#include <Global.h>
#include <System/Context.h>

int main()
{
	Context* context = new Context();
	context->InitContext(1280, 720);
	delete context;
	return 0;
}

#ifdef WIN32
int APIENTRY WinMain(HINSTANCE /*instance*/, HINSTANCE /*prev_instance*/, LPSTR /*args*/, int /*startup_info*/)
{
	return main();
}
#endif

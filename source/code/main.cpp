#include <Global.h>
#include <System/Context.h>

int main()
{
	Context* context = new Context();
	context->Init(1280, 720);
	context->Destroy();
	delete context;
	return 0;
}

#ifdef WIN32
int APIENTRY WinMain(HINSTANCE /*instance*/, HINSTANCE /*prev_instance*/, LPSTR /*args*/, int /*startup_info*/)
{
	return main();
}
#endif

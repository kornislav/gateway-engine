#include <Global.h>
#include <System/Core.h>
#ifdef ANDROID
#include <jni.h>
#include <android/android_native_app_glue.h>
#endif

#ifndef ANDROID
int main(int argc, char** argv)
{
	Core::Initialize();
	Core& core = Core::GetInstance();
	core.Init();
	core.Run();
	core.Destroy();
	Core::Deinitialize();
	return 0;
}
#endif

#ifdef WIN32
int APIENTRY WinMain(HINSTANCE /*instance*/, HINSTANCE /*prev_instance*/, LPSTR /*args*/, int /*startup_info*/)
{
	return main(__argc, __argv);
}
#elif defined(ANDROID)
void android_main(struct android_app* state)
{
	app_dummy();
	Core::Initialize();
	Core& core = Core::GetInstance();
	core.Init(state);
	core.Run();
	core.Destroy();
	Core::Deinitialize();
}
#endif

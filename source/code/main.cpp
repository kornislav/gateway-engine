#include <Global.h>
#include <System/Core.h>
#ifdef ANDROID
#include <jni.h>
#endif

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
#elif defined(ANDROID)
extern "C" {
	JNIEXPORT void JNICALL Java_com_example_gatewayengine_GLView_InitGateway(JNIEnv* env, jobject obj);
}

JNIEXPORT void JNICALL Java_com_example_gatewayengine_GLView_InitGateway(JNIEnv* env, jobject obj)
{
	main(0, nullptr);
}
#endif

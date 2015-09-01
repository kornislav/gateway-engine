#pragma once

#include <Global.h>

#ifdef WIN32
#include <gl/GL.h>
#elif defined(ANDROID)
#include <EGL/egl.h>
#include <GLES/gl.h>
#endif

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Init(Context* context);
	void Destroy();

	void BeginFrame();
	void EndFrame();

	void FlipBuffers();

private:
#ifdef WIN32
	void SetupPixelFormat(HDC device_context);

	HGLRC _rendering_context;
	HDC _device_context;
	PIXELFORMATDESCRIPTOR _pixel_format_descriptor;
#elif defined(ANDROID)
	EGLDisplay _display;
	EGLSurface _surface;
	EGLContext _context;
#endif
};
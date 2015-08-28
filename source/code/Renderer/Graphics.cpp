#include "Graphics.h"
#include <System/Context.h>

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
}

bool Graphics::Init(Context* context)
{
#ifdef WIN32
	_device_context = GetDC(context->GetWindow());
	if(!_device_context)
	{
		LogErrorL("Failed to get device context");
		return false;
	}

	SetupPixelFormat(_device_context);

	_rendering_context = wglCreateContext(_device_context);
	if(!_rendering_context)
	{
		LogErrorL("Failed to create rendering context");
		return false;
	}

	if(!wglMakeCurrent(_device_context, _rendering_context))
	{
		LogErrorL("Failed to set rendering context");
		return false;
	}

	LogSuccessL("Created rendering context");
#endif

	glViewport(0, 0, context->GetWidth(), context->GetHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	FlipBuffers();

	return true;
}

void Graphics::Destroy()
{
#ifdef WIN32
	wglMakeCurrent(_device_context, nullptr);
	wglDeleteContext(_rendering_context);
#endif

	LogMessageL("Destroyed graphics context");
}

void Graphics::FlipBuffers()
{
#ifdef WIN32
	SwapBuffers(_device_context);
#endif
}

#ifdef WIN32
void Graphics::SetupPixelFormat(HDC device_context)
{
	int pixel_format;

	memclr(&_pixel_format_descriptor, sizeof(_pixel_format_descriptor));
	_pixel_format_descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	_pixel_format_descriptor.nVersion = 1;
	_pixel_format_descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	_pixel_format_descriptor.iPixelType = PFD_TYPE_RGBA;
	_pixel_format_descriptor.cColorBits = 32;                            
	_pixel_format_descriptor.cDepthBits = 16;
	_pixel_format_descriptor.iLayerType = PFD_MAIN_PLANE;

    pixel_format = ChoosePixelFormat(device_context, &_pixel_format_descriptor);
    SetPixelFormat(device_context, pixel_format, &_pixel_format_descriptor);
}
#endif
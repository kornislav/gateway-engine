#include "Graphics.h"
#include <System/Context.h>
#ifdef ANDROID
#include <System/Core.h>
#include <android/android_native_app_glue.h>
#include <android/native_activity.h>
#endif
#include <Renderer/Renderer.h>
#include <Triangle.h>

Graphics::Graphics()
#ifdef ANDROID
	: _display(nullptr)
	, _surface(nullptr)
	, _context(nullptr)
#endif
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

	// Initialize GLEW
	uint error = glewInit();
	if(error != GLEW_OK)
	{
		LogErrorL("Failed to initialize GLEW: %s", glewGetErrorString(error));
	}
#elif defined(ANDROID)
	if(!_display)
		_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if(!_display)
	{
		LogErrorL("Failed to create EGL display");
		return false;
	}

	int maj = 0;
	int min = 0;
	if(!eglInitialize(_display, &maj, &min))
	{
		LogErrorL("Failed to initialize EGL");
		return false;
	}

	LogSuccessL("Initialized EGL version %i.%i", maj, min);

	const EGLint RGBX_8888_ATTRIBS[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_NONE
	};

	const EGLint RGB_565_ATTRIBS[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6,
		EGL_RED_SIZE, 5, EGL_DEPTH_SIZE, 8, EGL_NONE
	};

	const EGLint* attribList;

	int windowFormat = ANativeWindow_getFormat(Core::GetInstance().GetState()->window);

	if ((windowFormat == WINDOW_FORMAT_RGBA_8888) || (windowFormat == WINDOW_FORMAT_RGBX_8888))
	{
		attribList = RGBX_8888_ATTRIBS;
	}
	else
	{
		attribList = RGB_565_ATTRIBS;
	}

	EGLConfig config;
	EGLint numConfigs;
	if(!eglChooseConfig(_display, attribList, &config, 1, &numConfigs))
	{
		LogErrorL("Failed to choose EGL config");
		return false;
	}

	EGLint format;
	eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);

	if(ANativeWindow_setBuffersGeometry(Core::GetInstance().GetState()->window, 0, 0, format))
	{
		LogErrorL("Failed to set EGL buffers geometry");
		return false;
	}

	EGLNativeWindowType windowType;
	_surface = eglCreateWindowSurface(_display, config, Core::GetInstance().GetState()->window, nullptr);
	if(!_surface)
	{
		LogErrorL("Failed to create EGL surface");
		return false;
	}

	LogSuccessL("Created EGL surface");

	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, contextAttribs);
	if(!_context)
	{
		LogErrorL("Failed to create EGL context");
		return false;
	}

	LogSuccessL("Created EGL context");

	eglMakeCurrent(_display, _surface, _surface, _context);

	int width;
	int height;

	eglQuerySurface(_display, _surface, EGL_WIDTH, &width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &height);

	LogMessageL("Preferred size: %dx%d", width, height);
#endif

	Renderer::Register(new Triangle());

	glViewport(0, 0, context->GetWidth(), context->GetHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	FlipBuffers();

	return true;
}

void Graphics::Destroy()
{
#ifdef WIN32
	wglMakeCurrent(_device_context, nullptr);
	wglDeleteContext(_rendering_context);
#elif defined(ANDROID)
	if (_display)
	{
		eglMakeCurrent(_display, nullptr, nullptr, nullptr);
		if(_context)
		{
			eglDestroyContext(_display, _context);
		}
		if(_surface)
		{
			eglDestroySurface(_display, _surface);
		}
		eglTerminate(_display);
	}
	_display = nullptr;
	_context = nullptr;
	_surface = nullptr;
#endif

	LogMessageL("Destroyed graphics context");
}

void Graphics::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::EndFrame()
{
	FlipBuffers();
}

void Graphics::FlipBuffers()
{
#ifdef WIN32
	SwapBuffers(_device_context);
#elif defined(ANDROID)
	eglSwapBuffers(_display, _surface);
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
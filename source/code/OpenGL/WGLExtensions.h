#pragma once

#include <OpenGL/glext.h>
#include <OpenGL/wglext.h>

// GL extensions
static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLBUFFERDATAPROC glBufferData;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers;

// Initialize the extensions
static void InitGLExtensions()
{
	glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));
	glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(wglGetProcAddress("glGenBuffers"));
	glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(wglGetProcAddress("glBufferData"));
	glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(wglGetProcAddress("glDeleteBuffers"));
}

#pragma once

#include <Global.h>
#include <iostream>
#include <cstdarg>

enum LogStatus
{
	LOG_DEFAULT,
	LOG_WARNING,
	LOG_ERROR,
	LOG_SUCCESS
};

static void __Log(LogStatus status, const char* message, ...)
{
 	va_list args;
 	va_start(args, message);

	FILE* output = stdout;

#ifdef WIN32
	switch (status)
	{
	case LOG_ERROR:
		SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), 0x0C);
		output = stderr;
		break;
	case LOG_WARNING:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		break;
	case LOG_SUCCESS:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
		break;
	case LOG_DEFAULT:
	default:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	}
#endif

 	vfprintf_s(output, message, args);

 	va_end(args);
}

#define __STR(x) #x
#define STR(x) __STR(x)

#define LineAndFile(message) "Line " STR(__LINE__) " in " __FILE__ ": " message

#define LogMessage(message, ...) __Log(LOG_DEFAULT, message, __VA_ARGS__)
#define LogWarning(message, ...) __Log(LOG_WARNING, LineAndFile(message), __VA_ARGS__)
#define LogError(message, ...) __Log(LOG_ERROR, LineAndFile(message), __VA_ARGS__)
#define LogSuccess(message, ...) __Log(LOG_SUCCESS, "Success: " message, __VA_ARGS__)

// appends a newline after the message
#define LogMessageL(message, ...) LogMessage(message "\n", __VA_ARGS__)
#define LogWarningL(message, ...) LogWarning(message "\n", __VA_ARGS__)
#define LogErrorL(message, ...) LogError(message "\n", __VA_ARGS__)
#define LogSuccessL(message, ...) LogSuccess(message "\n", __VA_ARGS__)

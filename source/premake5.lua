PRODUCT_NAME = 'Engine'

solution(PRODUCT_NAME)
	platforms {
		"Win32",
		"x64",
		"Android"
	}
	configurations {
		"Debug",
		"Release",
		"Final"
	}

project(PRODUCT_NAME)
	kind "WindowedApp"
	language "C++"
	files {
		"code/**.c",
		"code/**.cpp",
		"code/**.h",
		"code/**.hpp",
		"code/**.inl",
	}

	targetdir "%{prj.location}../bin/%{cfg.platform}"
	targetname ("%{prj.name}-%{cfg.platform}-%{cfg.buildcfg}")
	debugdir "$%{prj.location}../bin/%{cfg.platform}"
	objdir ("%{prj.location}../build/%{cfg.platform}")

	includedirs {
		"code"
	}

	libdirs {
		"%{prj.location}../lib",
		"%{prj.location}../lib/%{cfg.platform}"
	}

	-- Exclude Android-file from non-android configs
	filter { "platforms:not Android" }
		excludes {
			"**/android_native_app_glue.c"
		}

	include 'customizations'

	-- Global per-configuration settings.
	filter { "configurations:Debug" }
		defines {
			"_DEBUG",
			"DEBUG",
		}
		flags {
			"Symbols",
		}

	filter { "configurations:Release" }
		defines {
			"RELEASE",
			"NDEBUG",
		}
		flags {
			"Symbols",
			"OptimizeSpeed",
		}

	filter { "configurations:Final" }
		defines {
			"FINAL",
			"NDEBUG",
		}
		flags {
			"OptimizeSpeed",
		}

	-- Win32
	filter { "platforms:Win32" }
		architecture "x86"

	-- Win64
	filter { "platforms:x64" }
		architecture "x86_64"

	-- Windows
	filter { "platforms:Win32 or x64" }
		system "windows"
		defines {
			"WIN32",
			"_WINDOWS",
		}
		links {
			"opengl32.lib",
			"glew32s.lib"
		}

	filter { "platforms:Win32 or x64", "configurations:not Debug" }
		buildoptions {
			-- Whole program optimization
			"/GL"
		}
		linkoptions {
			-- Link-time code generation
			"/LTCG"
		}

	-- Android
	filter { "platforms:Android" }
		system "linux"
		defines {
			"ANDROID"
		}
		includedirs {
			"$(NDK_ROOT)/platforms/android-21/arch-arm/usr/include"
		}
		libdirs {
			"$(NDK_ROOT)/platforms/android-21/arch-arm/usr/lib"
		}
		links {
			"-landroid",
			"-lGLESv2",
			"-lEGL"
		}
		buildoptions {
			"-std=c++11"
		}
		-- Since we're calling this hardcoded from Java we need
		-- to give it a predetermined name
		targetname "gateway-engine"
		targetextension ".so"

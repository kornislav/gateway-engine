PRODUCT_NAME = 'Engine'

solution(PRODUCT_NAME)
	platforms {
		"Win32",
		"Win64",
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

	targetdir "%{prj.location}../bin"
	targetname ("%{prj.name}_%{cfg.platform}_%{cfg.buildcfg}")
	debugdir "$%{prj.location}../bin"
	objdir ("%{prj.location}../build")

	includedirs {
		"code"
	}

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
		architecture "x32"

	-- Win64
	filter { "platforms:Win64" }
		architecture "x64"

	-- Windows
	filter { "platforms:Win*" }
		defines {
			"WIN32",
			"_WINDOWS",
		}
		links {
			"opengl32.lib"
		}

	filter { "platforms:Win*", "configurations:not Debug" }
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
			"-lGLESv2",
			"-lEGL"
		}

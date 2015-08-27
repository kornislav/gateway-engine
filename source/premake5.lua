PRODUCT_NAME = 'Engine'

solution(PRODUCT_NAME)
	platforms {
		"Win32",
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
		"code/**.cpp",
		"code/**.h",
	}

	targetdir "$(ProjectDir)../bin/"
	targetname ("$(ProjectName)_$(PlatformName)_$(Configuration)_" .. _ACTION)
	debugdir "$(ProjectDir)../bin/"
	objdir ("$(ProjectDir)../build/" .. _ACTION)

	includedirs {
		"$(SolutionDir)/code"
	}

	-- Global per-configuration settings.
	configuration { "Debug" }
		defines {
			"_DEBUG",
			"DEBUG",
		}
		flags {
			"Symbols",
		}

	configuration { "Release" }
		defines {
			"RELEASE",
			"NDEBUG",
		}
		flags {
			"Symbols",
			"OptimizeSpeed",
		}

	configuration { "Final" }
		defines {
			"FINAL",
			"NDEBUG",
		}
		flags {
			"OptimizeSpeed",
		}

	-- Win32
	configuration { "Win32" }
		defines {
			"WIN32",
			"_WINDOWS",
		}
		links {
			"opengl32.lib"
		}

	configuration { "Win32", "not Debug" }
		buildoptions {
			-- Whole program optimization
			"/GL"
		}
		linkoptions {
			-- Link-time code generation
			"/LTCG"
		}

	-- Android
	configuration { "Android" }
		defines {
			"ANDROID"
		}

		links {
			"-lGLESv2",
			"-lEGL"
		}

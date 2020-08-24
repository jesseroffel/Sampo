-- Solution setup
workspace "Sampo"
	architecture "x64"
	startproject "Demo"

	configurations { "Debug", "Release","Test" }

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"

-- General third-party include directories relative to solution directory
thirdpartyDir = {}

-- Projects
project "framework"
	location "framework"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "sampo_pch.hpp"
	pchsource "framework/include/sampo_pch.cpp"

	-- C/C++ and Librian settings
	files { "%{prj.name}/include/**.hpp", "%{prj.name}/include/**.cpp" }

	includedirs
	{
		"%{prj.name}/include"
	}

	flags { "MultiProcessorCompile", "FatalWarnings" }
	warnings "Extra"

	filter "system:windows"
		systemversion "latest"

		defines { "SAMPO_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "SAMPO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SAMPO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Test"
		defines "SAMPO_TESTING_MODE"
		runtime "Release"
		optimize "on"

project "demo"
	location "demo"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }

	includedirs { "framework/include" }

	links { "framework" }

	flags { "MultiProcessorCompile" }

	filter "system:windows"
		systemversion "latest"
		defines { "SAMPO_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

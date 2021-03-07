include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Cactus"
	architecture "x64"
	startproject "Cactus-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	solution_items
	{
		".editorconfig"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
--[[
IncludeDir["GLFW"] = "Cactus/vendor/GLFW/include"
IncludeDir["Glad"] = "Cactus/vendor/Glad/include"
IncludeDir["imgui"] = "Cactus/vendor/imgui"
IncludeDir["glm"] = "Cactus/vendor/glm"
IncludeDir["stb_image"] = "Cactus/vendor/stb_image"
--]]
IncludeDir["GLFW"] = "%{wks.location}/Cactus/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Cactus/vendor/Glad/include"
IncludeDir["imgui"] = "%{wks.location}/Cactus/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Cactus/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Cactus/vendor/stb_image"


group "Dependencies"
	include "Cactus/vendor/GLFW"
	include "Cactus/vendor/Glad"
	include "Cactus/vendor/imgui"
group ""

include "Cactus"
include "Sandbox"
include "Cactus-Editor"

--[[
project "Cactus"
	location "Cactus"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cactus_pch.h"
	pchsource "Cactus/src/cactus_pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"CACTUS_PLATFORM_WINDOWS",
			"CACTUS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "CACTUS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CACTUS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CACTUS_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Cactus/vendor/spdlog/include",
		"Cactus/src",
		"Cactus/vendor",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"Cactus"
	}

	

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"CACTUS_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "CACTUS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CACTUS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CACTUS_DIST"
		runtime "Release"
		optimize "on"
		--]]

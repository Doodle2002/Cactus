project "Cactus"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	--targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	--objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cactus_pch.h"
	pchsource "src/cactus_pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
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

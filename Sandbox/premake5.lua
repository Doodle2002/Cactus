project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Cactus/vendor/spdlog/include",
		"%{wks.location}/Cactus/src",
		"%{wks.location}/Cactus/vendor",
		"%{IncludeDir.glm}",
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

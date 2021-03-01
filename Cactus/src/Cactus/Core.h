#pragma once

#ifdef CACTUS_PLATFORM_WINDOWS
	#ifdef CACTUS_BUILD_DLL
		#define CACTUS_API __declspec(dllexport)
	#else
		#define CACTUS_API __declspec(dllimport)
	#endif
#else
	#error Cactus only supports Windows!
#endif

#ifdef CACTUS_ENABLE_ASSERTS
	#define CACTUS_ASSERT(x, ...) {if(!(x)) { CACTUS_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); }}	
	#define CACTUS_CORE_ASSERT(x, ...) {if(!(x)) { CACTUS_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); }}	
#else
	#define CACTUS_ASSERT(x, ...)
	#define CACTUS_CORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)

#define CACTUS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
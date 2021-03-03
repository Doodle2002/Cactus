#include "cactus_pch.h"

#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cactus
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CACTUS_CORE_ASSERT(false, "RendererAPI::None is not supported");  return  nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		CACTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CACTUS_CORE_ASSERT(false, "RendererAPI::None is not supported");  return  nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name,vertexSrc, fragmentSrc);
		}

		CACTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		CACTUS_CORE_ASSERT(!Exists(name), "Shader with name '{0}' is already loaded", name);
		shaders[name] = shader;

	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
		
	}
	

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name,shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		CACTUS_CORE_ASSERT(Exists(name), "Shader with name '{0}' not found", name);
		return shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return shaders.find(name) != shaders.end();
	}
}
#include <Cactus.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Cactus::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), cameraController(1280.0f / 720.0f)
	{
		vertexArray.reset(Cactus::VertexArray::Create());

		float vertices[4 * 5] = {
			-0.25f, -0.25f,  0.0f,  0.0f,  0.0f,
			 0.25f, -0.25f,  0.0f,  1.0f,  0.0f,
			 0.25f,  0.25f,  0.0f,  1.0f,  1.0f,
			-0.25f,  0.25f,  0.0f,  0.0f,  1.0f,
		};

		Cactus::Ref<Cactus::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cactus::VertexBuffer::Create(vertices, sizeof(vertices)));

		Cactus::BufferLayout layout = {
			{ Cactus::ShaderDataType::Float3, "a_Position"},
			{ Cactus::ShaderDataType::Float2, "a_TexCoord"},
		};

		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0};
		Cactus::Ref<Cactus::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cactus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		std::string colorVertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";

		std::string colorFragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;
			
			uniform vec3 u_Color;
			in vec3 v_Position;

			void main()
			{
				
				color = vec4(u_Color,1.0);
			}
		)";


		auto colorShader = Cactus::Shader::Create("Color",colorVertexSrc, colorFragmentSrc);

		shaderLibrary.Add(colorShader);

		auto textureShader = shaderLibrary.Load("assets/shaders/Texture.glsl");

		texture = Cactus::Texture2D::Create("assets/textures/Character.png");
		std::dynamic_pointer_cast<Cactus::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Cactus::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	ExampleLayer::~ExampleLayer()
	{
	
	}

	void OnUpdate() override
	{
		cameraController.OnUpdate();

		float dt = Cactus::Time::GetDeltaTime();
		//glm::vec3 cameraPosition = camera.GetPosition();	

		

		
	}

	void OnRender() override
	{
		CACTUS_TRACE("Rendering!");
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));;


		Cactus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cactus::RenderCommand::Clear();

		Cactus::Renderer::BeginScene(cameraController.GetCamera());

		//std::dynamic_pointer_cast<Cactus::OpenGLShader>(colorShader)->Bind();
		//std::dynamic_pointer_cast<Cactus::OpenGLShader>(colorShader)->UploadUniformFloat3("u_Color",color);

		auto textureShader = shaderLibrary.Get("Texture");
		texture->Bind();
		Cactus::Renderer::Submit(textureShader, vertexArray, transform);
		Cactus::Renderer::EndScene();
	}

	void OnImGuiRender()
	{
		ImGui::Begin("Debug");
		//ImGui::Text(std::to_string(Cactus::Time::GetDeltaTime()).c_str());
		ImGui::ColorEdit3("Box Color", glm::value_ptr(color));
		ImGui::End();
	}

	void OnEvent(Cactus::Event& event) override
	{
		//CACTUS_TRACE("{0}",event);
		cameraController.OnEvent(event);
	}

private:
	Cactus::ShaderLibrary shaderLibrary;
	Cactus::Ref<Cactus::VertexArray> vertexArray;

	Cactus::Ref<Cactus::Texture2D> texture;
	Cactus::OrthographicCameraController cameraController;

	float movementSpeed = 2.5f;
	float rotationSpeed = 240.0f;

	float rotation = 0;
	glm::vec3 position = glm::vec3(0.0);

	glm::vec3 color = glm::vec3(1.0,0.0,0.1);
};


class Sandbox : public Cactus::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new Cactus::InputLayer());
	}

	~Sandbox()
	{
	}
};

Cactus::Application* Cactus::CreateApplication() {
	return new Sandbox();
}
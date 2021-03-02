#include <Cactus.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Cactus::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		vertexArray.reset(Cactus::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f,  -0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
			0.0f,  0.5f,  0.0f, 0.2f, 0.8f, 0.8f, 1.0f
		};

		std::shared_ptr<Cactus::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cactus::VertexBuffer::Create(vertices, sizeof(vertices)));

		Cactus::BufferLayout layout = {
			{ Cactus::ShaderDataType::Float3, "a_Position"},
			{ Cactus::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[6] = { 0, 1, 2 };
		std::shared_ptr<Cactus::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cactus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				//color = vec4((v_Position+0.25)*0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		shader.reset(new Cactus::Shader(vertexSrc, fragmentSrc));

	}

	void OnUpdate() override
	{
		float dt = Cactus::Time::GetDeltaTime();
		glm::vec3 cameraPosition = camera.GetPosition();
		
		if (Cactus::Input::KeyDown(CACTUS_KEY_W)) {
			cameraPosition.y += movementSpeed * dt;
		}
		if (Cactus::Input::KeyDown(CACTUS_KEY_S)) {
			cameraPosition.y -= movementSpeed * dt;
		}
		if (Cactus::Input::KeyDown(CACTUS_KEY_A)) {
			cameraPosition.x -= movementSpeed * dt;
		}
		if (Cactus::Input::KeyDown(CACTUS_KEY_D)) {
			cameraPosition.x += movementSpeed * dt;
		}

		if (Cactus::Input::KeyDown(CACTUS_KEY_UP)) {
			position.y += movementSpeed * dt;
		}
		if (Cactus::Input::KeyDown(CACTUS_KEY_DOWN)) {
			position.y -= movementSpeed * dt;
		}
		if (Cactus::Input::KeyDown(CACTUS_KEY_LEFT)) {
			position.x -= movementSpeed * dt;
		}
		if (Cactus::Input::KeyDown(CACTUS_KEY_RIGHT)) {
			position.x += movementSpeed * dt;
		}

		camera.SetPosition(cameraPosition);
		camera.SetRotation(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		Cactus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cactus::RenderCommand::Clear();
		

		Cactus::Renderer::BeginScene(camera);
		Cactus::Renderer::Submit(shader, vertexArray,transform);
		Cactus::Renderer::EndScene();

	}

	void OnImGuiRender()
	{
		ImGui::Begin("Test");
		ImGui::Text(std::to_string(Cactus::Time::GetDeltaTime()).c_str());
		ImGui::End();
	}

	void OnEvent(Cactus::Event& event) override
	{
		//CACTUS_TRACE("{0}",event);
	}

private:
	std::shared_ptr<Cactus::Shader> shader;
	std::shared_ptr<Cactus::VertexArray> vertexArray;

	Cactus::OrthographicCamera camera;

	float movementSpeed = 1.5f;


	glm::vec3 position = glm::vec3(0.0);


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
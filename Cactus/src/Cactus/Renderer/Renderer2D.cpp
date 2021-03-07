#include "cactus_pch.h"

#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>
namespace Cactus {

	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
		float texIndex;
		//texid
	};

	struct Renderer2DData
	{
		static const uint32_t maxQuads = 10000;
		static const uint32_t maxVertices = maxQuads * 4;
		static const uint32_t maxIndices = maxQuads * 6;
		static const uint32_t maxTextureSlots = 32; //Should get this from gpu max texture slots

		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
		uint32_t textureSlotIndex = 1;

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics stats;
	};

	static Renderer2DData data;


	void Renderer2D::Init()
	{
		CACTUS_PROFILE_FUNCTION();

		data.quadVertexArray = Cactus::VertexArray::Create();

		data.quadVertexBuffer = VertexBuffer::Create(data.maxVertices * sizeof(QuadVertex));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float, "a_TexIndex"}
		};

		data.quadVertexBuffer->SetLayout(layout);
		data.quadVertexArray->AddVertexBuffer(data.quadVertexBuffer);

		data.quadVertexBufferBase = new QuadVertex[data.maxVertices];

		uint32_t* quadIndices = new uint32_t[data.maxIndices];

		uint32_t offset = 0;

		//Setup ALL indices (indices = array of uint32_t, indexes of the vertexbuffer, 3 for triangle, 4 for quad)
		for (uint32_t i = 0; i < data.maxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;

		}
		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, data.maxIndices);
		data.quadVertexArray->SetIndexBuffer(quadIndexBuffer);

		delete[] quadIndices;


		data.whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;

		data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[data.maxTextureSlots];
		for (int32_t i = 0; i < data.maxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		data.textureShader = Shader::Create("assets/shaders/Texture.glsl");
		data.textureShader->Bind();
		data.textureShader->SetIntArray("u_Textures", samplers, data.maxTextureSlots);

		data.textureSlots[0] = data.whiteTexture;

		data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
	}
	void Renderer2D::Shutdown()
	{

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		data.textureShader->Bind();
		data.textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		data.quadIndexCount = 0;
		data.quadVertexBufferPtr = data.quadVertexBufferBase;

		data.textureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		uint32_t datasize = (uint32_t)((uint8_t*)data.quadVertexBufferPtr - (uint8_t*)data.quadVertexBufferBase);
		data.quadVertexBuffer->SetData(data.quadVertexBufferBase, datasize);
		Flush();
	}

	void Renderer2D::Flush()
	{
		//textureSlotIndex is the amount of total textures bind this batch (not zero based, normal counting)
		for (uint32_t i = 0; i < data.textureSlotIndex; i++)
		{
			data.textureSlots[i]->Bind(i);
		}
		RenderCommand::DrawIndexed(data.quadVertexArray, data.quadIndexCount);
		data.stats.drawCalls++;
	}

	

	void Renderer2D::FlushAndReset()
	{
		//CACTUS_CORE_WARN("New batch");
		EndScene();
		data.quadIndexCount = 0;
		data.quadVertexBufferPtr = data.quadVertexBufferBase;

		data.textureSlotIndex = 1;
	}




	//COLOR
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		DrawQuad(transform, data.whiteTexture,textureCoords, color);
	}



	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		DrawQuad(transform, data.whiteTexture, textureCoords, color);
	}


	//TEXTURE
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		DrawQuad(transform, texture, textureCoords, color);
	}



	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, rotation, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		DrawQuad(transform, texture, textureCoords, color);

	}

	//SUBTEXTURE
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& texture, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture->GetTexture() , texture->GetTexCoords(), color);
	}



	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, rotation, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture->GetTexture(), texture->GetTexCoords(), color);

	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D> texture, const glm::vec4& tint)
	{
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		DrawQuad(transform, texture->GetTexture(), texture->GetTexCoords(), tint);
	}

	//TRANSFORM
	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		DrawQuad(transform, data.whiteTexture, textureCoords, color);
	}

	//Main DrawQuad function
	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, const glm::vec4& tint)
	{
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		DrawQuad(transform, texture, textureCoords, tint);
	}


	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, const glm::vec2* textureCoords, const glm::vec4& tint)
	{
		if (data.quadIndexCount >= data.maxIndices)
		{
			FlushAndReset();
		}

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < data.textureSlotIndex; i++)
		{
			if (*data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex] = texture;
			data.textureSlotIndex++;
		}


		for (size_t i = 0; i < 4; i++)
		{
			data.quadVertexBufferPtr->position = transform * data.QuadVertexPositions[i];
			data.quadVertexBufferPtr->color = tint;
			data.quadVertexBufferPtr->texCoord = textureCoords[i];
			data.quadVertexBufferPtr->texIndex = textureIndex;
			data.quadVertexBufferPtr++;
		}

		data.quadIndexCount += 6;
		data.stats.quadCount++;
	}



	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return data.stats;
	}
	void Renderer2D::ResetStats()
	{
		memset(&data.stats, 0, sizeof(Statistics));
	}
}
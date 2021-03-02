#include "cactus_pch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>
namespace Cactus {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Cactus::ShaderDataType::Float:		return GL_FLOAT;
			case Cactus::ShaderDataType::Float2:	return GL_FLOAT;
			case Cactus::ShaderDataType::Float3:	return GL_FLOAT;
			case Cactus::ShaderDataType::Float4:	return GL_FLOAT;
			case Cactus::ShaderDataType::Int:		return GL_INT;
			case Cactus::ShaderDataType::Int2:		return GL_INT;
			case Cactus::ShaderDataType::Int3:		return GL_INT;
			case Cactus::ShaderDataType::Int4:		return GL_INT;
			case Cactus::ShaderDataType::Mat3:		return GL_FLOAT;
			case Cactus::ShaderDataType::Mat4:		return GL_FLOAT;
			case Cactus::ShaderDataType::Bool:		return GL_BOOL;
		}

		CACTUS_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	};

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(rendererID);
		vertexBuffer->Bind();

		CACTUS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has not layout");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset);
			index++;
		}

		vertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererID);
		indexBuffer->Bind();

		this->indexBuffer = indexBuffer;
	}
}
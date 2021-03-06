#pragma once

namespace Cactus {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:			return 4;
		case ShaderDataType::Float2:		return 4 * 2;
		case ShaderDataType::Float3:		return 4 * 3;
		case ShaderDataType::Float4:		return 4 * 4;
		case ShaderDataType::Mat3:			return 4 * 3 * 3;
		case ShaderDataType::Mat4:			return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;

		}

		CACTUS_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t offset;
		uint32_t size;
		bool normalized;

		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;

			}

			CACTUS_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return stride; }
		inline const std::vector<BufferElement>& GetElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : elements) 
			{
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}
	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};




	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t datasize) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		
		
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
		
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}
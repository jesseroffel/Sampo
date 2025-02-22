#pragma once

namespace Sampo
{
	enum class ShaderDataType
	{
		None = 0,
		Bool,
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4
	};

	static uint32 ShaderDataTypeSize(ShaderDataType aType)
	{
		switch (aType)
		{
		case Sampo::ShaderDataType::None: return 0;
		case Sampo::ShaderDataType::Bool: return 4;
		case Sampo::ShaderDataType::Int: return 4;
		case Sampo::ShaderDataType::Int2: return 4 * 2;
		case Sampo::ShaderDataType::Int3: return 4 * 3;
		case Sampo::ShaderDataType::Int4: return 4 * 4;
		case Sampo::ShaderDataType::Float: return 4;
		case Sampo::ShaderDataType::Float2: return 4 * 2;
		case Sampo::ShaderDataType::Float3: return 4 * 3;
		case Sampo::ShaderDataType::Float4: return 4 * 4;
		case Sampo::ShaderDataType::Mat3: return 4 * 3 * 3;
		case Sampo::ShaderDataType::Mat4: return 4 * 4 * 4;
		}

		SAMPO_ASSERT_MSG(false, "Cannot calculate Shader Data Type size as the data type is invalid!");
		return uint32_max;
	}

	struct BufferElement
	{
		std::string m_Name;
		ShaderDataType m_Type{ ShaderDataType::None };
		uint32 m_Size{ 0 };
		uint64 m_Offset{ 0 };
		bool m_Normalized{ false };

		BufferElement(ShaderDataType aDataType, const std::string& aName, bool aIsNormalized = false)
			: m_Name(aName)
			, m_Type(aDataType)
			, m_Size(ShaderDataTypeSize(aDataType))
			, m_Offset(0)
			, m_Normalized(aIsNormalized)
		{ }

		uint32 GetComponentCount() const
		{
			switch (m_Type)
			{
			case Sampo::ShaderDataType::None: return 0;
			case Sampo::ShaderDataType::Bool: return 1;
			case Sampo::ShaderDataType::Int: return 1;
			case Sampo::ShaderDataType::Int2: return 2;
			case Sampo::ShaderDataType::Int3: return 3;
			case Sampo::ShaderDataType::Int4: return 4;
			case Sampo::ShaderDataType::Float: return 1;
			case Sampo::ShaderDataType::Float2: return 2;
			case Sampo::ShaderDataType::Float3: return 3;
			case Sampo::ShaderDataType::Float4: return 4;
			case Sampo::ShaderDataType::Mat3: return 3 * 3;
			case Sampo::ShaderDataType::Mat4: return 4 * 4;
			}

			SAMPO_ASSERT_MSG(false, "Cannot calculate Shader Data Type component count as the data type is invalid!");
			return uint32_max;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& aBufferElements)
			: m_BufferElements(aBufferElements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }
		inline const uint32 GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }

	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferElement> m_BufferElements;
		uint32 m_Stride{ 0 };
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& aLayout) = 0;

		static std::shared_ptr<VertexBuffer> Create(float* aVertices, uint32 aSize);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(uint32* anIndices, uint32 aCount);
	};
}
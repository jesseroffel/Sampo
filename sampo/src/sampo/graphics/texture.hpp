#pragma once

namespace Sampo
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void SetData(void* aData, uint32 aSize) = 0;

		virtual void Bind(uint32 aTextureSlot = 0) const = 0;

		virtual bool operator==(const Texture& anOther) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;
		static std::shared_ptr<Texture2D> Create(uint32 aWidth, uint32 aHeight);
		static std::shared_ptr<Texture2D> Create(const std::string& aFilepath);
	};
}
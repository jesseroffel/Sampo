#pragma once
#include "sampo/graphics/window.hpp"

namespace Sampo
{
	class Win32Platform
	{
	public:
		Win32Platform();
		~Win32Platform() = default;

		void Init(const std::string& aWindowName);
		void Update();
		void Shutdown();

		Window* GetWindow() const;

	private:
		Window* m_Window;
	};
}
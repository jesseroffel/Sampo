#pragma once

namespace Sampo
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void PostInit() = 0;
		virtual void OnStartFrame() = 0;
		virtual void SwapBuffers() = 0;
		virtual void Draw() = 0;

		virtual void LogRendererInfo() = 0;
	};
}
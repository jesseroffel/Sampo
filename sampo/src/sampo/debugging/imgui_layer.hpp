#pragma once
#include "sampo/core/layer.hpp"

namespace Sampo
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void Begin();
		void End();
	};
}
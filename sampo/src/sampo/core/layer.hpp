#pragma once
#include "timestep.hpp"

#include "sampo/events/event.hpp"

namespace Sampo
{
	// Layer class that represents a page which update loop will be called to handle and/or render objects, respond to events or act as UI //
	class Layer
	{
	public:
		Layer(const std::string& layerName = "Unnamed Layer")
			: m_LayerName(layerName) {
		}
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep aDeltaTime) { UNUSED(aDeltaTime); };
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& anEvent) { UNUSED(anEvent); };

		inline const std::string& GetLayerName() { return m_LayerName; }

	private:
		std::string m_LayerName{};

	};

	// Collection class that propagates and goes through Layers like a book, updating and positing them in order on a stack.
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layerToAdd);
		void PushOverlay(Layer* overlayToAdd);
		void PopLayer(Layer* layerToPop);
		void PopOverlay(Layer* overlayToPop);


		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers; // TODO - make layers be aligned next to each other in memory?
		uint32_t m_LayerIndex{};
	};
}
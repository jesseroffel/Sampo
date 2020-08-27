#pragma once
#include "foundation/core/core_definitions.hpp"

namespace Sampo
{
    // Layer class that represents a page which update loop will be called to handle and/or render objects, respond to events or act as UI //
    class Layer
    {
    public:
        Layer(const std::string& layerName = "Unnamed Layer")
            : m_LayerName(layerName) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {};
        virtual void OnUpdate(float ts) { UNUSED(ts); };
        virtual void OnDetach() {};

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
    private:
        std::vector<Layer*> m_Layers;       // todo: make layers be aligned next to each other in memory?
        uint32_t m_LayerIndex{};
    };

}
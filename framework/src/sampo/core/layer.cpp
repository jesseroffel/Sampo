#include "sampo_pch.hpp"
#include "layer.hpp"

namespace Sampo
{
    LayerStack::~LayerStack()
    {
        for (auto layer : m_Layers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layerToAdd)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerIndex, layerToAdd);
        m_LayerIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlayToAdd)
    {
        m_Layers.emplace_back(overlayToAdd);
    }

    void LayerStack::PopLayer(Layer* layerToPop)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layerToPop);
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
            m_LayerIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlayToPop)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayToPop);
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
        }
    }
}
#pragma once
#include "core_definitions.hpp"

#include "layer.hpp"

// Application Class, using the main entry point to start common systems, to be defined in the client application // 
namespace Sampo {
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        virtual void Init() {}
        void Close();
        void Run();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        inline static Application& Get() { return *s_Instance; }
    private:
        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };

    // To be defined in the client application using Sampo //
    Application* CreateApplication();
}
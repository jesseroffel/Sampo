#pragma once
#include "core_definitions.hpp"

#include "layer.hpp"

// Application Class, using the main entry point to start common systems, to be defined in the client application // 
namespace Sampo 
{
    struct StartParams
    {
        std::string m_ApplicationName;
        std::string m_WindowName;
        std::string m_ExecuteDir;
        std::string m_DataDir;

        bool m_EnableNetworking = false;
        bool m_IsGame = false;
    };

    class Application
    {
    public:
        static Application* Create(StartParams& startParams);
        static Application* GetInstance() { return s_Instance; }
        inline static Application& Get() { return *s_Instance; }

        void Run();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

    protected:
        virtual ~Application() = default;

        static Application* CreateApplication();

        virtual bool Init(StartParams& startParams) { SAMPO_UNUSED(startParams); return true; }

        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };
}
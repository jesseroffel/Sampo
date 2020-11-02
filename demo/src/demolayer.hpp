#pragma once
#include <sampo/core/layer.hpp>

class DemoLayer : public Sampo::Layer
{
public:
    DemoLayer() = default;
    ~DemoLayer() = default;

    virtual void OnAttach() override;

};
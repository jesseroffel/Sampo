#pragma once
#include "sampo/core/layer.hpp"

class NetworkTest : public Sampo::Layer
{
public:
    NetworkTest() = default;
    ~NetworkTest() = default;

    virtual void OnAttach() override;
};
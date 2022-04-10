#pragma once
#include "sampo/core/layer.hpp"

class mathtests : public Sampo::Layer
{
public:
    mathtests() = default;
    ~mathtests() = default;

    virtual void OnAttach() override;

};
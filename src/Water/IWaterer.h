#pragma once

#include <cstdint>

class IWaterer
{
public:
    virtual~IWaterer() = default;

    virtual void tick(uint32_t elapsed) = 0;
};


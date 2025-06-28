#pragma once

#include "component_interface.hpp"

namespace platform::hardware
{
    struct KeymatrixScanner : public pulp::ComponentInterface
    {
        virtual void initialize();
        virtual void shutdown();

        bool perform(void);
    };
}

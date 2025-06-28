#include "keymatrix_scanner.hpp"

namespace platform::hardware
{
    void KeymatrixScanner::initialize()
    {
        pulp::ComponentInterface::initialize();
    }

    void KeymatrixScanner::shutdown()
    {
        pulp::ComponentInterface::shutdown();
    }

    bool KeymatrixScanner::perform(void)
    {
    }
}
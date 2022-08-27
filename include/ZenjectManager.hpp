#pragma once

#include "Zenjector.hpp"

namespace Lapiz::Zenject {
    class ZenjectManager {

        
    };

    class ZenjectorDatum {
        bool enabled;
        Zenjector& m_zenjector;

      public:
        ZenjectorDatum(class Zenjector& zenjector) : m_zenjector(zenjector) {
            m_zenjector = zenjector;
        }
    };
}
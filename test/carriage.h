#ifndef XXYY_CARRIAGE_H
#define XXYY_CARRIAGE_H

#include <cstdint>

namespace XXYY {

struct Carriage {
    Carriage(const int32_t a_destination, const int32_t a_index = -1)
        : destination(a_destination), index(a_index) {}

    /**
     * the destination number of carriage
     */
    uint32_t destination;

    /**
     * index in the original carriage sequence
     */
    uint32_t index;

}; // Carriage

} // namespace XXYY

#endif // XXYY_CARRIAGE_H

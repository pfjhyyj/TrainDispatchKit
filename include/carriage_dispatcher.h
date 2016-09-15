#ifndef XXYY_CARRIAGE_DIPATCHER_H
#define XXYY_CARRIAGE_DIPATCHER_H

#include "carriage_buffer.h"
#include <cstdint>
#include <vector>

namespace XXYY {

class CarriageDipatcher {
  public:
    CarriageDipatcher(std::vector<int32_t> carriage_sequence);

  private:
    CarriageBuffer buffer_;

}; // CarriageDispatcher

} // namespace XXYY

#endif // XXYY_CARRIAGE_DIPATCHER_H

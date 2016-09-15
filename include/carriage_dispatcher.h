#ifndef XXYY_CARRIAGE_DIPATCHER_H
#define XXYY_CARRIAGE_DIPATCHER_H

#include "carriage.h"
#include "carriage_buffers.h"
#include <cstdint>
#include <queue>
#include <vector>

namespace XXYY {

class CarriageDipatcher {
  public:
    using CarriageQueue = std::queue<Carriage>;
    /**
     * initial carriage sequence
     * @param carriage_sequence the original order of carriage
     */
    CarriageDipatcher(const std::vector<uint32_t> carriage_sequence);

    /**
     * continue for one more step
     */
    void NextStep();

    /**
     * continue for step_num steps, if not specified, continue to end
     * @param step_num steps need to continue, default to 0
     */
    void ContinueFor(const uint32_t step_num = 0);

    /**
     * getter for buffers
     * @return the reference to carriage buffers
     */
    const CarriageBuffers &Buffers() const;

  private:
    /**
     * carriage buffers of the dipatcher
     */
    CarriageBuffers buffers_;

    /**
     * carriages to be dispatch
     */
    CarriageQueue carriage_queue_;

}; // CarriageDispatcher

} // namespace XXYY

#endif // XXYY_CARRIAGE_DIPATCHER_H

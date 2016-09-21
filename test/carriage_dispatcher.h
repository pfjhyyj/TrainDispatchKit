#ifndef XXYY_CARRIAGE_DIPATCHER_H
#define XXYY_CARRIAGE_DIPATCHER_H

#include "carriage.h"
#include "carriage_buffers.h"
#include "step.h"
#include <cstdint>
#include <deque>
#include <limits>
#include <memory>
#include <vector>

namespace XXYY {

class CarriageDipatcher {
  public:
    /**
     * use deque for carriage queue for possible traverse
     */
    using CarriageQueue = std::deque<Carriage>;

    /**
     * initial carriage sequence
     * @param carriage_sequence the original order of carriage
     */
    CarriageDipatcher(const std::vector<uint32_t> carriage_sequence);

    /**
     * continue for one more step
     */
    std::string NextStep();

    /**
     * continue for step_num steps, if not specified, continue to end
     * @param step_num steps need to continue, default to numeric_limit::max()
     */
    std::vector<std::string>
    ContinueFor(uint32_t step_num = std::numeric_limits<uint32_t>::max());

    /**
     * getter for buffers
     * @return the reference to carriage buffers
     */
    const CarriageBuffers &Buffers() const;

    /**
     * get specific buffer from carriage buffers
     * @param  buffer_index index of the wanted buffer
     * @return              the pointer to the buffer, nullptr if out of range
     */
    CarriageBuffers::ConstBufferPtr Buffer(size_t buffer_index) const;

    /**
     * return the number of buffer currently used
     * @return the number of buffer currently allocated
     */
    size_t buffers_used() const;

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

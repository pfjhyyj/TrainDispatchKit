#ifndef XXYY_CARRIAGE_BUFFERS_H
#define XXYY_CARRIAGE_BUFFERS_H

#include "carriage.h"
#include "step.h"
#include <cstdint>
#include <list>
#include <memory>
#include <vector>

namespace XXYY {

class CarriageBuffers {
  public:
    /**
     * use vector to represent carriages in a single buffer
     */
    using CarriageBuffer = std::vector<Carriage>;

    using BufferPtr = std::shared_ptr<CarriageBuffer>;

    using ConstBufferPtr = std::shared_ptr<const CarriageBuffer>;

    /**
     * using list to contain buffers
     */
    using BuffersType = std::list<BufferPtr>;

    /**
     * construct specify the max number of destination
     * @param max_destination_num max number of destination the original
     *                            sequence have
     */
    CarriageBuffers(const uint32_t max_destination_num);

    /**
     * pop as many carriage as it can
     * @return the steps taken by pops
     */
    std::vector<Step> PopAll();

    /**
     * pop some carriages from buffer
     * @param  pop_num the max number of carriage it'll pop
     * @return         the steps taken by pops
     */
    std::vector<Step> PopSome(uint32_t pop_num);

    /**
     * push a carriage to buffers
     * @param the step taken by push
     */
    Step Push(const Carriage &carriage);

    /**
     * getter for a particular buffer in carriage buffers, nullptr if out of
     * range
     * @param  buffer_index the index for the buffer
     * @return              a pointer point to the specified buffer, or nullptr
     *                      if the index is out of range of buffers
     */
    ConstBufferPtr Buffer(const std::size_t buffer_index) const;

    /**
     * getter for current number of total buffer
     * @return the number of buffer in buffers
     */
    BuffersType::size_type size() const;

    /**
     * getter the number of current buffer use
     * @return the amount of buffer currently used
     */
    uint32_t buffer_used() const;

  private:
    /**
     * allocate new buffer for the buffers
     */
    void AllocateBuffer();

    /**
     * carriage buffers
     */
    BuffersType carriage_buffers_;

    /**
     * current max number need to pop
     */
    uint32_t buffer_used_;

    /**
     * carriage destination currently required for popping
     */
    uint32_t max_num_;
};

} // namespace XXYY

#endif // XXYY_CARRIAGE_BUFFERS_H

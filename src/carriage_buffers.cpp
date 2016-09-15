#include "carriage_buffers.h"

using XXYY::CarriageBuffers;

CarriageBuffers::CarriageBuffers(const uint32_t max_destination_num)
    : max_num_(max_destination_num) {}

const CarriageBuffers::BufferPtr
CarriageBuffers::Buffer(const std::size_t buffer_index) const {
    if (buffer_index < carriage_buffers_.size()) {
        return BufferPtr(&carriage_buffers_[buffer_index]);
    }
    return nullptr;
}
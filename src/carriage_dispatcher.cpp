#include "carriage_dispatcher.h"
#include <utility>

using XXYY::CarriageDipatcher;
using XXYY::CarriageBuffers;

CarriageDipatcher::CarriageDipatcher(
    const std::vector<uint32_t> carriage_sequence)
    : buffers_(carriage_sequence.size()) {
    uint32_t index(0);
    for (auto destination : carriage_sequence) {
        carriage_queue_.emplace_back(destination, index++);
    }
}

void CarriageDipatcher::NextStep() {
    ContinueFor(1);
}

const CarriageBuffers &CarriageDipatcher::Buffers() const {
    return buffers_;
}

void CarriageDipatcher::ContinueFor(uint32_t step_num) {

    do {
        step_num -= buffers_.PopSome(step_num);
        if (not step_num or carriage_queue_.empty())
            break;
        buffers_.Push(carriage_queue_.front());
        carriage_queue_.pop_front();
    } while (--step_num);
}

CarriageBuffers::ConstBufferPtr
CarriageDipatcher::Buffer(size_t buffer_index) const {
    return buffers_.Buffer(buffer_index);
}

size_t CarriageDipatcher::buffers_size() const {
    return buffers_.size();
}

size_t CarriageDipatcher::buffers_max_size() const {
    return buffers_.max_buffer_used();
}
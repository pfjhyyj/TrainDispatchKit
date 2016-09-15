#include "carriage_dispatcher.h"

using XXYY::CarriageDipatcher;
using XXYY::CarriageBuffers;

CarriageDipatcher::CarriageDipatcher(
    const std::vector<uint32_t> carriage_sequence)
    : buffers_(carriage_sequence.size()) {
    uint32_t index(0);
    for (auto destination : carriage_sequence) {
        carriage_queue_.emplace(destination, index++);
    }
}

void CarriageDipatcher::NextStep() {
    ContinueFor(1);
}

const CarriageBuffers &CarriageDipatcher::Buffers() const {
    return buffers_;
}

#include "carriage_buffers.h"
#include <algorithm>

using XXYY::CarriageBuffers;

CarriageBuffers::CarriageBuffers(const uint32_t max_destination_num)
    : max_num_(max_destination_num) {}

CarriageBuffers::BufferPtr
CarriageBuffers::Buffer(const std::size_t buffer_index) const {
    if (buffer_index < carriage_buffers_.size()) {
        return BufferPtr(&carriage_buffers_[buffer_index]);
    }
    return nullptr;
}

uint32_t CarriageBuffers::PopAll() {
    uint32_t popped_carriage(0);
    for (;;) {
        // find the buffer whose top element equal the current target
        auto find_result_iter = std::find_if(
            begin(carriage_buffers_), end(carriage_buffers_),
            [this](const CarriageBuffer &buffer) {
                return buffer.back().destination == max_num_;
            });
        if (find_result_iter != end(carriage_buffers_)) {
            ++popped_carriage;
            --max_num_;
            find_result_iter->pop_back();
        } else {
            break;
        }
    }
    return popped_carriage;
}

uint32_t CarriageBuffers::PopSome(uint32_t pop_num) {
    uint32_t popped_carriage(0);
    for (; pop_num--;) {
        // find the buffer whose top element equal the current target
        auto find_result_iter = std::find_if(
            begin(carriage_buffers_), end(carriage_buffers_),
            [this](const CarriageBuffer &buffer) {
                return buffer.back().destination == max_num_;
            });
        if (find_result_iter != end(carriage_buffers_)) {
            ++popped_carriage;
            --max_num_;
            find_result_iter->pop_back();
        } else {
            break;
        }
    }
    return popped_carriage;
}

void CarriageBuffers::Push(const Carriage &carriage) {
    // find the first buffer whose top element is smaller than current target
    auto find_result_iter = std::find_if(
        begin(carriage_buffers_), end(carriage_buffers_),
        [this, &carriage](const CarriageBuffer &buffer) {
            return buffer.back().destination < carriage.destination;
        });
    if (find_result_iter != end(carriage_buffers_)) {
        find_result_iter->push_back(carriage);
    } else {
        AllocateBuffer();
        carriage_buffers_.back().push_back(carriage);
    }
}

std::vector<CarriageBuffers::CarriageBuffer>::size_type
CarriageBuffers::size() const {
    return carriage_buffers_.size();
}

void CarriageBuffers::AllocateBuffer() {
    carriage_buffers_.push_back(CarriageBuffer());
}
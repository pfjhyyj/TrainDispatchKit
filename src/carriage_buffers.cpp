#include "carriage_buffers.h"
#include <algorithm>
#include <limits>

using XXYY::CarriageBuffers;

CarriageBuffers::CarriageBuffers(const uint32_t max_destination_num)
    : max_num_(max_destination_num), max_buffer_used_(0) {}

CarriageBuffers::BufferPtr
CarriageBuffers::Buffer(const std::size_t buffer_index) const {
    if (buffer_index < carriage_buffers_.size()) {
        auto ret_iter = carriage_buffers_.begin();
        std::advance(ret_iter, buffer_index);
        return BufferPtr(&(*ret_iter));
    }
    return nullptr;
}

uint32_t CarriageBuffers::PopAll() {
    return PopSome(std::numeric_limits<uint32_t>::max());
}

uint32_t CarriageBuffers::PopSome(uint32_t pop_num) {
    uint32_t popped_carriage(0);
    for (; pop_num--;) {
        // find the buffer whose top element equal the current target
        auto find_result_iter = std::find_if(
            begin(carriage_buffers_), end(carriage_buffers_),
            [this](const CarriageBuffer &buffer) {
                return buffer.size() and buffer.back().destination == max_num_;
            });

        // if the buffer satisfied the condition is found
        if (find_result_iter != end(carriage_buffers_)) {
            ++popped_carriage;
            --max_num_;
            find_result_iter->pop_back();

            // if empty, deallocate buffer
            if (find_result_iter->empty()) {
                carriage_buffers_.erase(find_result_iter);
            }
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

        // check if max_buffer_used can be updated
        auto current_size = carriage_buffers_.size();
        if (current_size > max_buffer_used_) {
            max_buffer_used_ = current_size;
        }
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

uint32_t CarriageBuffers::max_buffer_used() const {
    return max_buffer_used_;
}
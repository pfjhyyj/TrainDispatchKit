#include "carriage_buffers.h"
#include "step.h"
#include <algorithm>
#include <limits>
#include <utility>

template <typename T>
class TD;

using XXYY::CarriageBuffers;
using XXYY::Step;

CarriageBuffers::CarriageBuffers(const uint32_t max_destination_num)
    : max_num_(max_destination_num) {}

CarriageBuffers::ConstBufferPtr
CarriageBuffers::Buffer(const std::size_t buffer_index) const {
    if (buffer_index < carriage_buffers_.size()) {
        return carriage_buffers_.at(buffer_index);
    }
    return nullptr;
}

std::vector<Step> CarriageBuffers::PopAll() {
    return PopSome(std::numeric_limits<uint32_t>::max());
}

std::vector<Step> CarriageBuffers::PopSome(uint32_t pop_num) {
    std::vector<Step> steps;
    for (; pop_num--;) {
        bool find = false;
        // try to find a buffer which can pop something
        for (size_t i(0); i < size(); ++i) {
            auto &buffer = carriage_buffers_.at(i);
            if (buffer and buffer->back().destination == max_num_) {
                // found
                find = true;
                // update steps
                steps.push_back(Step(Step::POP, i, buffer->back().destination));
                // do the pop
                buffer->pop_back();
                // deallocate buffer
                if (buffer->empty()) {
                    buffer = nullptr;
                    buffer_order_.remove(i);
                }
                --max_num_;
                break;
            }
        }
        if (not find) {
            break;
        }
        // // find the buffer whose top element equal the current target
        // auto find_result_iter = std::find_if(
        //     begin(carriage_buffers_), end(carriage_buffers_),
        //     [this](const BufferPtr &buffer) {
        //         return buffer->back().destination == max_num_;
        //     });

        // // if the buffer satisfied the condition is found
        // if (find_result_iter != end(carriage_buffers_)) {
        //     --max_num_;
        //     (*find_result_iter)->pop_back();

        //     // if empty, deallocate buffer
        //     if ((*find_result_iter)->empty()) {
        //         carriage_buffers_.erase(find_result_iter);
        //     }
        // } else {
        //     break;
        // }
    }
    return steps;
}

Step CarriageBuffers::Push(const Carriage &carriage) {
    // find available buffer according to the buffer allocation order
    for (auto index : buffer_order_) {
        if (carriage_buffers_.at(index)->back().destination <
            carriage.destination) {
            carriage_buffers_.at(index)->push_back(carriage);
            return Step(Step::PUSH, index, carriage.destination);
        }
    }

    // use new buffer otherwise
    size_t index;
    auto new_buffer = AllocateBuffer(&index);
    new_buffer->push_back(carriage);
    return Step(Step::PUSH, index, carriage.destination);
}
// find the first buffer whose top element is smaller than current target
// auto find_result_iter = std::find_if(
//     begin(carriage_buffers_), end(carriage_buffers_),
//     [this, &carriage](const BufferPtr &buffer) {
//         return buffer->back().destination < carriage.destination;
//     });
// if (find_result_iter != end(carriage_buffers_)) {
//     (*find_result_iter)->push_back(carriage);
// } else {
//     AllocateBuffer();

//     // check if max_buffer_used can be updated
//     auto current_size = carriage_buffers_.size();
//     if (current_size > max_buffer_used_) {
//         max_buffer_used_ = current_size;
//     }
//     carriage_buffers_.back()->push_back(carriage);
// }
// }

CarriageBuffers::BuffersType::size_type CarriageBuffers::size() const {
    return carriage_buffers_.size();
}

CarriageBuffers::BufferPtr
CarriageBuffers::AllocateBuffer(size_t *const index) {
    // check if there's empty buffer in allocated buffers
    for (BuffersType::size_type i(0); i < size(); ++i) {
        if (not carriage_buffers_.at(i)) {
            buffer_order_.push_back(i);
            *index = i;
            return carriage_buffers_.at(i) = BufferPtr(new CarriageBuffer);
        }
    }

    // allocate new buffers otherwise
    buffer_order_.push_back(size());
    *index = size();
    carriage_buffers_.push_back(std::make_shared<CarriageBuffer>());
    return carriage_buffers_.back();
}

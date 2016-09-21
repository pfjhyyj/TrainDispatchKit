#include "carriage_dispatcher.h"
#include <string>
#include <utility>

using XXYY::CarriageDipatcher;
using XXYY::CarriageBuffers;
using std::string;
using std::vector;

CarriageDipatcher::CarriageDipatcher(
    const std::vector<uint32_t> carriage_sequence)
    : buffers_(carriage_sequence.size()) {
    uint32_t index(0);
    for (auto destination : carriage_sequence) {
        carriage_queue_.emplace_back(destination, index++);
    }
}

string CarriageDipatcher::NextStep() {
    auto step_strings = ContinueFor(1);
    if (step_strings.empty()) {
        return "Finish";
    }
    return step_strings.front();
}

const CarriageBuffers &CarriageDipatcher::Buffers() const {
    return buffers_;
}

vector<string> CarriageDipatcher::ContinueFor(uint32_t step_num) {
    vector<string> step_strings;
    do {
        // the steps recorded
        auto steps = buffers_.PopSome(step_num);

        // if no step is taken, and queue is empty, the procedure is over
        if (steps.empty() and carriage_queue_.empty()) {
            step_strings.push_back("Finish");
            return step_strings;
        }

        for (const auto &step : steps) {
            step_strings.push_back(step.to_string());
        }

        step_num -= steps.size();
        if (not step_num)
            return step_strings;

        if (not carriage_queue_.empty()) {
            step_strings.push_back(
                buffers_.Push(carriage_queue_.front()).to_string());
            carriage_queue_.pop_front();
            --step_num;
        }
    } while (step_num);

    return step_strings;
}

CarriageBuffers::ConstBufferPtr
CarriageDipatcher::Buffer(size_t buffer_index) const {
    return buffers_.Buffer(buffer_index);
}

size_t CarriageDipatcher::buffers_used() const {
    return buffers_.size();
}

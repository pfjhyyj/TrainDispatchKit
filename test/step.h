#ifndef XXYY_STEP_H_
#define XXYY_STEP_H_

#include <sstream>
#include <string>

namespace XXYY {

struct Step {
  public:
    enum Operation { POP, PUSH };

    Step(Operation a_operation, size_t a_buffer_index, uint32_t destination)
        : operation(a_operation), buffer_index(a_buffer_index),
          carriage_dest(destination) {}

    /**
     * turn the step into string
     * @return a human readable string representing the step
     */
    std::string to_string() const {
        std::ostringstream oss;
        if (operation == POP) {
            oss << "Pop Carriage " << carriage_dest << " from buffer "
                << buffer_index;
        } else {
            oss << "Push Carriage " << carriage_dest << " to buffer "
                << buffer_index;
        }
        return oss.str();
    }

    /**
     * the operation carried out
     */
    Operation operation;

    /**
     * which buffer did the operation
     */
    size_t buffer_index;

    /**
     * the carriage related to the operation
     * 'dest' is the abbrieviation for destination
     */
    uint32_t carriage_dest;
};

} // namespace XXYY

#endif // XXYY_STEP_H_
#include "compiler/visitor/code_gen/helper/error_helper.h"
#include <stdexcept>
#include <string>

void ErrorHelper::compilationError(const std::string& message) {
    throw std::runtime_error("Semantic error: " + message);
}

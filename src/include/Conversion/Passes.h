#pragma once

#include "Conversion/ArithToHe/ArithToHe.h"

namespace mlir_he {

/// Generate the code for registering conversion passes.
#define GEN_PASS_REGISTRATION
#include "Conversion/Passes.h.inc"

} // namespace mlir_he

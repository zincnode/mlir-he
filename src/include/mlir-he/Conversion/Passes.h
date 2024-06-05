#pragma once

#include "mlir-he/Conversion/ArithToHe/ArithToHe.h"

namespace mlir_he {

/// Generate the code for registering conversion passes.
#define GEN_PASS_REGISTRATION
#include "mlir-he/Conversion/Passes.h.inc"

} // namespace mlir_he

#pragma once

#include "mlir-he/Conversion/Passes.h"

namespace mlir_he {

inline void registerAllMLIRHePasses() {
  // Conversion passes
  registerMLIRHeConversionPasses();
}

} // namespace mlir_he

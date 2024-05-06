#pragma once

#include "Conversion/Passes.h"

namespace mlir_he {

inline void registerAllHePasses() {
  // Conversion passes
  registerHeConversionPasses();
}

} // namespace mlir_he

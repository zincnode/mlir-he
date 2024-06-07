#pragma once

#include "mlir/Pass/Pass.h"
#include <memory>

namespace mlir_he {

#define GEN_PASS_DECL_CONVERTARITHTOHE
#include "mlir-he/Conversion/Passes.h.inc"

std::unique_ptr<mlir::Pass> createConvertArithToHePass();

} // namespace mlir_he

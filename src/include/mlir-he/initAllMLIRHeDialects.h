#pragma once

#include "mlir-he/Dialect/He/IR/He.h"
#include "mlir/IR/Dialect.h"

namespace mlir_he {

/// Add all the MLIR-He dialects to the provided registry.
inline void registerAllMLIRHeDialects(mlir::DialectRegistry &registry) {
  // clang-format off
  registry.insert<he::HeDialect>();
  // clang-format on
}

/// Append all the MLIR-He dialects to the registry contained in the given context.
inline void registerAllMLIRHeDialects(mlir::MLIRContext &context) {
  mlir::DialectRegistry registry;
  registerAllMLIRHeDialects(registry);
  context.appendDialectRegistry(registry);
}

} // namespace mlir_he

#pragma once

#include "Dialect/He/IR/He.h"
#include "mlir/IR/Dialect.h"

namespace mlir_he {

/// Add all the MLIR-He dialects to the provided registry.
inline void registerAllHeDialects(mlir::DialectRegistry &registry) {
  // clang-format off
  registry.insert<HeDialect>();
  // clang-format on
}

/// Append all the MLIR-He dialects to the registry contained in the given context.
inline void registerAllHeDialects(mlir::MLIRContext &context) {
  mlir::DialectRegistry registry;
  registerAllHeDialects(registry);
  context.appendDialectRegistry(registry);
}

} // namespace mlir_he

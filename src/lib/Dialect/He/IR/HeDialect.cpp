#include "mlir-he/Dialect/He/IR/He.h"

void mlir_he::he::HeDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "mlir-he/Dialect/He/IR/HeOps.cpp.inc"
      >();
}

#include "mlir-he/Dialect/He/IR/HeOpsDialect.cpp.inc"

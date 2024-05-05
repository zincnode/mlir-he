#include "Dialect/He/IR/He.h"

void mlir_he::HeDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "Dialect/He/IR/He.cpp.inc"
      >();
}

#include "Dialect/He/IR/HeDialect.cpp.inc"

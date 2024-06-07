#pragma once

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"


#include "mlir-he/Dialect/He/IR/HeOpsDialect.h.inc"

#define GET_OP_CLASSES
#include "mlir-he/Dialect/He/IR/HeOps.h.inc"

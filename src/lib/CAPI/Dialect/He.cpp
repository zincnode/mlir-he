#include "mlir-he-c/Dialect/He.h"
#include "mlir-he/Dialect/He/IR/He.h"
#include "mlir/CAPI/IR.h"
#include "mlir/CAPI/Registration.h"
#include "mlir/CAPI/Support.h"

MLIR_DEFINE_CAPI_DIALECT_REGISTRATION(He, he, mlir_he::he::HeDialect)

#include "mlir-he/Conversion/Passes.h"
#include "mlir/CAPI/Pass.h"
#include "mlir/Pass/Pass.h"

// Must include the declarations as they carry important visibility attributes.
#include "mlir-he/Conversion/Conversion.capi.h.inc"

using namespace mlir_he;

#ifdef __cplusplus
extern "C" {
#endif

#include "mlir-he/Conversion/Conversion.capi.cpp.inc"

#ifdef __cplusplus
}
#endif

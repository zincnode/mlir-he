#include "mlir-c/Bindings/Python/Interop.h"
#include "mlir-c/IR.h"
#include "mlir-c/Transforms.h"
#include "mlir-he-c/Conversion.h"
#include "mlir-he-c/Dialect/He.h"
#include "mlir/Bindings/Python/PybindAdaptors.h"

#include "llvm-c/ErrorHandling.h"
#include "llvm/Support/Signals.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

static void registerPasses() { mlirRegisterMLIRHeConversionPasses(); }

PYBIND11_MODULE(_mlir_he, m) {
  m.doc() = "MLIR-He Python Native Extension";
  registerPasses();
  llvm::sys::PrintStackTraceOnErrorSignal(/*argv=*/"");
  LLVMEnablePrettyStackTrace();

  m.def(
      "register_dialects",
      [](py::object capsule) {
        // Get the MlirContext capsule from PyMlirContext capsule.
        auto wrappedCapsule = capsule.attr(MLIR_PYTHON_CAPI_PTR_ATTR);
        MlirContext context = mlirPythonCapsuleToContext(wrappedCapsule.ptr());

        // Collect MLIR-He dialects to register.
        MlirDialectHandle he = mlirGetDialectHandle__he__();
        mlirDialectHandleRegisterDialect(he, context);
        mlirDialectHandleLoadDialect(he, context);
      },
      "Register MLIR-He dialects on a PyMlirContext.");
}

#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/Tools/mlir-lsp-server/MlirLspServerMain.h"
#include "llvm/Support/PrettyStackTrace.h"

#include "initAllHeDialects.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;

  mlir::registerAllDialects(registry);
  mlir_he::registerAllHeDialects(registry);
  return failed(mlir::MlirLspServerMain(argc, argv, registry));
}

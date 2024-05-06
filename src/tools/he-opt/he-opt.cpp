#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

#include "initAllHeDialects.h"
#include "InitAllHePasses.h"


int main(int argc, char **argv) {
  mlir::registerAllPasses();
  mlir_he::registerAllHePasses();

  mlir::DialectRegistry registry;
  mlir::registerAllDialects(registry);
  mlir_he::registerAllHeDialects(registry);

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "MLIR-He optimizer driver\n", registry));
}

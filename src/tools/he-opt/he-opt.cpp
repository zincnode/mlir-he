#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

#include "mlir-he/InitAllMLIRHePasses.h"
#include "mlir-he/initAllMLIRHeDialects.h"

int main(int argc, char **argv) {
  mlir::registerAllPasses();
  mlir_he::registerAllMLIRHePasses();

  mlir::DialectRegistry registry;
  mlir::registerAllDialects(registry);
  mlir_he::registerAllMLIRHeDialects(registry);

  return mlir::asMainReturnCode(mlir::MlirOptMain(argc, argv, "MLIR-He optimizer driver\n", registry));
}

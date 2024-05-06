#ifndef CONVERSION_PASSES_TD
#define CONVERSION_PASSES_TD

include "mlir/Pass/PassBase.td"

//===----------------------------------------------------------------------===//
// ArithToHe
//===----------------------------------------------------------------------===//

def ConvertArithToHe: Pass<"convert-arith-to-he"> {
  let summary = "Convert Arith dialect to He dialect";
  let description = [{
    Convert Arith dialect to He dialect for demo.
  }];
  let constructor = "mlir_he::createConvertArithToHePass()";
  let dependentDialects = [
    "mlir::arith::ArithDialect",
    "mlir_he::HeDialect"
  ];
}

#endif // CONVERSION_PASSES_TD

#ifndef HEOPS_TD
#define HEOPS_TD

include "mlir/IR/OpBase.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

def HeAddOp : HeOp<"add", [SameOperandsAndResultType]> {
  let summary = "Add two values";
  let description = [{
    The `add` operation adds two values.
  }];
  let arguments = (ins
    AnyType:$lhs,
    AnyType:$rhs
  );
  let results = (outs
    AnyType:$result
  );
}

#endif // HEOPS_TD

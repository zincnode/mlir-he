#ifndef HEOPS_TD
#define HEOPS_TD

include "mlir/IR/OpBase.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir-he/Dialect/He/IR/HeBase.td"

class He_Op<string mnemonic, list<Trait> traits = []> :
        Op<He_Dialect, mnemonic, traits>;

def He_AddOp : He_Op<"add", [SameOperandsAndResultType]> {
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

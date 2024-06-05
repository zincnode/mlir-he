#ifndef HE_BASE
#define HE_BASE

include "mlir/IR/OpBase.td"

def He_Dialect : Dialect {
  let name = "he";
  let cppNamespace = "::mlir_he::he";
  let summary = "Dialect for demo";
  let description = [{
    This is a dialect for demo.
  }];
}

#endif // HE_BASE

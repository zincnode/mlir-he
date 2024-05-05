#ifndef HE_TD
#define HE_TD

include "mlir/IR/OpBase.td"

def HeDialect : Dialect {
  let name = "he";
  let summary = "Dialect for demo.";
  let cppNamespace = "::mlir_he";
}

class HeOp<string mnemonic, list<Trait> traits = []> :
        Op<HeDialect, mnemonic, traits>;

include "HeOps.td"

#endif // HE_TD

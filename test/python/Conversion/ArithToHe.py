# RUN: %PYTHON %s | FileCheck %s

import gc, sys
import mlir_he

def constructAndPrintInModule(f):
    print("\nTEST:", f.__name__)
    with mlir_he.ir.Context(), mlir_he.ir.Location.unknown():
        module = mlir_he.ir.Module.create()
        with mlir_he.ir.InsertionPoint(module.body):
            f()
        print(module)
    return f

# CHECK-LABEL: TEST: testArithToHe
@constructAndPrintInModule
def testArithToHe():
    with mlir_he.Context() as ctx:
        mlir_he.register_dialects(ctx)
        module = mlir_he.ir.Module.parse(
        """
        module {
          func.func @test_addi(%arg0 : i64, %arg1 : i64) -> i64 {
            %0 = arith.addi %arg0, %arg1 : i64
            return %0 : i64
          }
        }
        """
        )
        pm = mlir_he.passmanager.PassManager.parse("builtin.module(convert-arith-to-he, func.func(print-op-stats{json=false}))")
        pm.run(module.operation)
        # check: func.func   , 1
        # check: func.return , 1
        # check: he.add      , 1

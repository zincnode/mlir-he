// RUN: he-opt %s | he-opt | FileCheck %s
// RUN: he-opt %s --mlir-print-op-generic | he-opt | FileCheck %s

// CHECK-LABEL: test_add
func.func @test_add(%arg0 : tensor<1x2x3x4xf32>, %arg1 : tensor<1x2x3x4xf32>) -> tensor<1x2x3x4xf32> {
  %0 = "he.add"(%arg0, %arg1) : (tensor<1x2x3x4xf32>, tensor<1x2x3x4xf32>) -> tensor<1x2x3x4xf32>
  return %0 : tensor<1x2x3x4xf32>
}

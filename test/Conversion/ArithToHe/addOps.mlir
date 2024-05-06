// RUN: he-opt %s --convert-arith-to-he | FileCheck %s

// CHECK-LABEL: test_addi
func.func @test_addi(%arg0 : i64, %arg1 : i64) -> i64 {
  // CHECK: %0 = "he.add"(%arg0, %arg1) : (i64, i64) -> i64
  %0 = arith.addi %arg0, %arg1 : i64
  return %0 : i64
}

// CHECK-LABEL: test_addi_tensor
func.func @test_addi_tensor(%arg0 : tensor<8x8xi64>, %arg1 : tensor<8x8xi64>) -> tensor<8x8xi64> {
  // CHECK: %0 = "he.add"(%arg0, %arg1) : (tensor<8x8xi64>, tensor<8x8xi64>) -> tensor<8x8xi64>
  %0 = arith.addi %arg0, %arg1 : tensor<8x8xi64>
  return %0 : tensor<8x8xi64>
}


// CHECK-LABEL: test_addf
func.func @test_addf(%arg0 : f64, %arg1 : f64) -> f64 {
  // CHECK: %0 = "he.add"(%arg0, %arg1) : (f64, f64) -> f64
  %0 = arith.addf %arg0, %arg1 : f64
  return %0 : f64
}

// CHECK-LABEL: test_addf_tensor
func.func @test_addf_tensor(%arg0 : tensor<8x8xf64>, %arg1 : tensor<8x8xf64>) -> tensor<8x8xf64> {
  // CHECK: %0 = "he.add"(%arg0, %arg1) : (tensor<8x8xf64>, tensor<8x8xf64>) -> tensor<8x8xf64>
  %0 = arith.addf %arg0, %arg1 : tensor<8x8xf64>
  return %0 : tensor<8x8xf64>
}

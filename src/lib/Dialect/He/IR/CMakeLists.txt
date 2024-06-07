add_mlir_dialect_library(HeDialect
  HeDialect.cpp
  HeOps.cpp

  DEPENDS
  MLIRHeOpsIncGen

  LINK_LIBS PUBLIC
  MLIRIR
  MLIRInferTypeOpInterface
)

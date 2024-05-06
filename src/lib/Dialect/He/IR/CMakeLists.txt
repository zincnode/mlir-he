add_mlir_dialect_library(HeDialect
  He.cpp
  HeOps.cpp

  DEPENDS
  MLIRHeIncGen

  LINK_LIBS PUBLIC
  MLIRIR
  MLIRInferTypeOpInterface
)

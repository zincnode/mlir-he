add_mlir_conversion_library(HeArithToHe
  ArithToHe.cpp

  DEPENDS
  MLIRHeConversionPassIncGen

  LINK_LIBS PUBLIC
  MLIRArithDialect
  HeDialect
  MLIRIR
  MLIRPass
  MLIRSupport
)

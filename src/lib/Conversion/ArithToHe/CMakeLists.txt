add_mlir_conversion_library(MLIRHeArithToHe
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

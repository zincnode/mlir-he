add_mlir_public_c_api_library(MLIRHeCAPIConversion
  Passes.cpp

  LINK_LIBS PUBLIC
  MLIRHeArithToHe
)

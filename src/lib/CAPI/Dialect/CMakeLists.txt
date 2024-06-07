add_mlir_public_c_api_library(MLIRHeCAPIHe
  He.cpp

  PARTIAL_SOURCES_INTENDED
  LINK_LIBS PUBLIC
  MLIRCAPIIR
  HeDialect
)

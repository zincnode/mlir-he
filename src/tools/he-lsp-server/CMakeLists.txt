add_llvm_executable(he-lsp-server he-lsp-server.cpp)

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)

target_link_libraries(he-lsp-server PRIVATE
  ${dialect_libs}
  MLIRLspServerLib
  MLIRDialect
)

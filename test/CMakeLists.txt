configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
  MAIN_CONFIG
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
)

set(MLIR_HE_TEST_DEPENDS
  FileCheck count not
  he-opt
  he-lsp-server
)

add_lit_testsuite(check-mlir-he "Running MLIR-He regression tests"
  ${CMAKE_CURRENT_BINARY_DIR}
  
  DEPENDS 
  ${MLIR_HE_TEST_DEPENDS}
)

set_target_properties(check-mlir-he PROPERTIES FOLDER "Tests")

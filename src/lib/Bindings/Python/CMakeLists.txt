################################################################################
# Set up Python binding tools
################################################################################

include(AddMLIRPython)

add_compile_definitions("MLIR_PYTHON_PACKAGE_PREFIX=mlir_he.")

################################################################################
# Declare native Python extension
################################################################################

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

declare_mlir_python_extension(MLIRHeBindingsPythonExtension
  MODULE_NAME _mlir_he
  SOURCES
    MLIRHeModule.cpp
  EMBED_CAPI_LINK_LIBS
    MLIRHeCAPIHe
    MLIRHeCAPIConversion
    MLIRCAPITransforms
  PRIVATE_LINK_LIBS
    ${dialect_libs}
    ${conversion_libs}
    LLVMSupport
)

################################################################################
# Declare Python sources
################################################################################

declare_mlir_python_sources(MLIRHeBindingsPythonSources
  ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES
    __init__.py
)

################################################################################
# Declare dialect-specific bindings.
################################################################################

declare_mlir_python_sources(MLIRHeBindingsPythonSources.Dialects
  ADD_TO_PARENT MLIRHeBindingsPythonSources)

declare_mlir_dialect_python_bindings(
    ADD_TO_PARENT MLIRHeBindingsPythonSources.Dialects
    ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    TD_FILE dialects/HeOps.td
    SOURCES
      dialects/he.py
    DIALECT_NAME he)

################################################################################
# Build composite binaries
################################################################################

# Bundle our own, self-contained CAPI library with all of our deps.
add_mlir_python_common_capi_library(MLIRHeBindingsPythonCAPI
INSTALL_COMPONENT MLIRHePythonModules
INSTALL_DESTINATION python_packages/mlir_he_core/mlir_he/_mlir_libs
OUTPUT_DIRECTORY "${MLIR_HE_PYTHON_PACKAGES_DIR}/mlir_he_core/mlir_he/_mlir_libs"
RELATIVE_INSTALL_ROOT "../../../.."
DECLARED_SOURCES
  MLIRPythonSources
  MLIRPythonExtension.RegisterEverything
  MLIRHeBindingsPythonExtension
)

# Bundle the MLIR-He python sources into our package.
add_mlir_python_modules(MLIRHePythonModules
  ROOT_PREFIX "${MLIR_HE_PYTHON_PACKAGES_DIR}/mlir_he_core/mlir_he"
  INSTALL_PREFIX "python_packages/mlir_he_core/mlir_he"
  DECLARED_SOURCES
    MLIRPythonSources
    MLIRPythonExtension.RegisterEverything
    MLIRHeBindingsPythonExtension
    MLIRHeBindingsPythonSources
  COMMON_CAPI_LINK_LIBS
    MLIRHeBindingsPythonCAPI
)

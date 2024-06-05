cmake_minimum_required(VERSION 3.20.0)

# CMP0116: Ninja generators transform `DEPFILE`s from `add_custom_command()`
# New in CMake 3.20. https://cmake.org/cmake/help/latest/policy/CMP0116.html
if(POLICY CMP0116)
  cmake_policy(SET CMP0116 OLD)
endif()

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to conform to")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#-------------------------------------------------------------------------------
# Project setup and globals
#-------------------------------------------------------------------------------

project(mlir-he LANGUAGES CXX C)

#-------------------------------------------------------------------------------
# MLIR/LLVM Configuration
#-------------------------------------------------------------------------------

find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_BINARY_DIR}/src/include)
link_directories(${LLVM_BUILD_LIBRARY_DIR})
add_definitions(${LLVM_DEFINITIONS})

#-------------------------------------------------------------------------------
# MLIR-He configuration
#-------------------------------------------------------------------------------

set(MLIR_HE_PYTHON_PACKAGES_DIR ${PROJECT_BINARY_DIR}/python_packages)

#-------------------------------------------------------------------------------
# Python Configuration
#-------------------------------------------------------------------------------

option(MLIR_HE_ENABLE_BINDINGS_PYTHON "Enable MLIR-He Python bindings." OFF)

if(MLIR_HE_ENABLE_BINDINGS_PYTHON)
  message(STATUS "MLIR-He Python bindings are enabled.")
  include(MLIRDetectPythonEnv)
  mlir_configure_python_dev_packages()
else()
  message(STATUS "MLIR-He Python bindings are disabled.")
endif()

#-------------------------------------------------------------------------------
# MLIR-He
#-------------------------------------------------------------------------------

add_subdirectory(src)
add_subdirectory(test)

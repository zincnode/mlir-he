#!/bin/bash

PROJECT_DIR=$(dirname $(dirname $(realpath $0)))
PROJECT_BUILD_DIR=$PROJECT_DIR/build

# Check if the LLVM build directory is set
if [[ -z $LLVM_BUILD_DIR ]]; then
    echo "LLVM_BUILD_DIR is not set. Please set it to the LLVM build directory."
    exit 1
fi

# Check if the LLVM install directory is set
if [[ -z $LLVM_INSTALL_DIR ]]; then
    echo "LLVM_INSTALL_DIR is not set. Please set it to the LLVM install directory."
    exit 1
fi

useage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  -c, --clean         Clean the project. Default: false"
    echo "  -cb, --clean-build  Clean and build the project."
    echo "  -d, --debug         Build the project in debug mode. Default: Release"
    echo "  -jN                 Build the project with N threads. Default: $(nproc)"
    echo "  -t, --test          Run the tests."
}

clean_flag=0
build_flag=1
build_type="Release"
build_threads=$(nproc)
test_flag=0

clean_project() {
    echo "Cleaning the project..."
    rm -rf $PROJECT_BUILD_DIR
}

build_project() {
    echo "Building the project..."
    if [[ ! -d $PROJECT_BUILD_DIR ]]; then
        mkdir $PROJECT_BUILD_DIR
    fi
    cd $PROJECT_BUILD_DIR
    cmake -G Ninja .. \
        -DMLIR_DIR=$LLVM_INSTALL_DIR/lib/cmake/mlir \
        -DLLVM_EXTERNAL_LIT=$LLVM_BUILD_DIR/bin/llvm-lit \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_BUILD_TYPE=$build_type
    ninja -j $build_threads
    if [[ $test_flag -eq 1 ]]; then
        ninja check-mlir-he -j $build_threads
    fi
}

for arg in "$@"; do
    case $arg in
        -c|--clean)
            clean_flag=1
            build_flag=0
            ;;
        -cb|--clean-build)
            clean_flag=1
            ;;
        -d|--debug)
            build_type="Debug"
            ;;
        -j[0-9]*)
            # parse the threads, the format is -j4
            build_threads=${arg#-j}
            ;;
        -t|--test)
            test_flag=1
            ;;
        *)
            useage
            exit 1
            ;;
    esac
done

if [[ $clean_flag -eq 1 ]]; then
    clean_project
fi

if [[ $build_flag -eq 1 ]]; then
    build_project
fi

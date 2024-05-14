# MLIR-He

[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/zincnode/mlir-he/build.yml?style=flat-square&logo=githubactions)
](https://github.com/zincnode/mlir-he/actions)[![Docker Image Version](https://img.shields.io/docker/v/zincnode/mlir-he?style=flat-square&logo=docker)](https://hub.docker.com/r/zincnode/mlir-he)

![logo](images/icon-helium.png)

This project aims to provide a naive template for out-of-tree MLIR projects. 

## Build

### llvm-project

```sh
pip install numpy pybind11
```

```sh
git clone https://github.com/llvm/llvm-project.git
mkdir llvm-project/build llvm-project/install && cd llvm-project/build

cmake -G Ninja ../llvm \
   -DLLVM_ENABLE_PROJECTS=mlir \
   -DLLVM_TARGETS_TO_BUILD="host" \
   -DCMAKE_BUILD_TYPE=Release \
   -DLLVM_ENABLE_ASSERTIONS=ON \
   -DCMAKE_C_COMPILER=clang \
   -DCMAKE_CXX_COMPILER=clang++ \
   -DLLVM_ENABLE_LLD=ON \
   -DMLIR_ENABLE_BINDINGS_PYTHON=ON \
   -DLLVM_INSTALL_UTILS=ON \
   -DLLVM_ENABLE_BINDINGS=OFF \
   -DCMAKE_INSTALL_PREFIX=../install

ninja install
# Run tests:
ninja check-mlir

export LLVM_BUILD_DIR=<llvm-project-path>/build
export LLVM_INSTALL_DIR=<llvm-project-path>/install
```

### MLIR-He

```sh
git clone https://github.com/zincnode/mlir-he.git
mkdir mlir-he/build && cd mlir-he/build

cmake -G Ninja .. \
   -DMLIR_DIR=$LLVM_INSTALL_DIR/lib/cmake/mlir \
   -DLLVM_EXTERNAL_LIT=$LLVM_BUILD_DIR/bin/llvm-lit \
   -DCMAKE_C_COMPILER=clang \
   -DCMAKE_CXX_COMPILER=clang++

ninja
# Run tests:
ninja check-mlir-he
```

or

```sh
git clone https://github.com/zincnode/mlir-he.git
cd mlir-he

./scripts/build.sh
# Run tests:
./scripts/build.sh -t
```

## References

- [jmgorius/mlir-standalone-template](https://github.com/jmgorius/mlir-standalone-template)
- [Lewuathe/mlir-hello](https://github.com/Lewuathe/mlir-hello)

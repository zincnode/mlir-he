# MLIR-He

![logo](images/icon-helium.png)

This project aims to provide a naive template for out-of-tree MLIR projects. 

## Build

### llvm-project

```sh
pip install numpy pybind11
```

```sh
git clone https://github.com/llvm/llvm-project.git
mkdir llvm-project/build && cd llvm-project/build

cmake -G Ninja ../llvm \
   -DLLVM_ENABLE_PROJECTS=mlir \
   -DLLVM_TARGETS_TO_BUILD="host" \
   -DCMAKE_BUILD_TYPE=Release \
   -DLLVM_ENABLE_ASSERTIONS=ON \
   -DCMAKE_C_COMPILER=clang \
   -DCMAKE_CXX_COMPILER=clang++ \
   -DLLVM_ENABLE_LLD=ON \
   -DMLIR_ENABLE_BINDINGS_PYTHON=ON \
   -DLLVM_INSTALL_UTILS=ON

cmake --build . --
# Run tests:
cmake --build . --target check-mlir

export LLVM_BUILD_DIR=<your-path>/build
```

### MLIR-He

```sh
git clone https://github.com/zincnode/mlir-he.git
mkdir mlir-he/build && cd mlir-he/build

cmake -G Ninja .. -DMLIR_DIR=$LLVM_BUILD_DIR/lib/cmake/mlir

cmake --build . --
# Run tests:
cmake --build . --target check-mlir-he
```

## References

- [jmgorius/mlir-standalone-template](https://github.com/jmgorius/mlir-standalone-template)
- [Lewuathe/mlir-hello](https://github.com/Lewuathe/mlir-hello)

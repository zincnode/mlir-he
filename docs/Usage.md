# Usage

## Prepare the environment

### 🌟 Use the docker image

- Option 0: Get pre-built images from Docker Hub: [zincnode/mlir-he](https://hub.docker.com/r/zincnode/mlir-he). Execute the following to pull the image:
```sh
docker pull zincnode/mlir-he
```

- Option 1: Build the docker image manually. Please refer to [docker/README](../docker/README.md).

### ⭐ Build environment manually

- Install dependencies
```sh
pip install numpy pybind11
```

- Clone llvm-project
```sh
git clone https://github.com/llvm/llvm-project.git
```

- Build and install llvm-project
```sh
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
```

- Run tests

```sh
ninja check-mlir
```

- Configure environment variables
```sh
export LLVM_BUILD_DIR=<llvm-project-path>/build
export LLVM_INSTALL_DIR=<llvm-project-path>/install
```

## Build mlir-he

- Clone mlir-he
```sh
git clone https://github.com/zincnode/mlir-he.git
```

- Build
```sh
./scripts/build.sh
```

- Build with Python bindings
```sh
./scripts/build.sh -pb
```
> 📝: The compiled Python package is named `mlir_he` and the path is `<build_dir>/python_packages/mlir_he_core/`.

- Build in debug mode
```sh
./scripts/build.sh -d
```

- Run tests
```sh
./scripts/build.sh -t # or ./scripts/build.sh -pb -t
```

or

- Build
```sh
mkdir mlir-he/build && cd mlir-he/build
```

```sh
cmake -G Ninja .. \
   -DMLIR_DIR=$LLVM_INSTALL_DIR/lib/cmake/mlir \
   -DLLVM_EXTERNAL_LIT=$LLVM_BUILD_DIR/bin/llvm-lit \
   -DCMAKE_C_COMPILER=clang \
   -DCMAKE_CXX_COMPILER=clang++ \
   -DCMAKE_BUILD_TYPE="Release" \ # or "Debug"
   -DMLIR_HE_ENABLE_BINDINGS_PYTHON=OFF # or ON
```

```sh
ninja
```

- Run tests
```sh
ninja check-mlir-he
```

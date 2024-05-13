# Docker

## Build image

```sh
git clone https://github.com/zincnode/mlir-he.git && cd mlir-he

docker build -t <image-name>:<tag> ./docker

# `apt_mirror` and `pypi_mirror` can be specified at build time to replace the default mirror source to speed up the build process. e.g.:
docker build -t mlir-he ./docker --build-arg apt_mirror="mirrors.bfsu.edu.cn" --build-arg pypi_mirror="https://pypi.tuna.tsinghua.edu.cn/simple" --build-arg python_mirror="https://registry.npmmirror.com/-/binary/python"
```

## Usage

```sh
# Start the container
docker run -itd --name <container-name> -v <mlir-he-path>:/workdir/mlir-he <image-name>:<tag>

# Execute an interactive bash shell on the container
docker exec -it <container-name> bash

# Build
cd /workdir/mlir-he
./scripts/build.sh

# Run tests
./scripts/build.sh -t
```

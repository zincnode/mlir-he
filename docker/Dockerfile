FROM ubuntu:24.04
# FROM ubuntu:22.04

ARG WORKDIR=/workdir
WORKDIR ${WORKDIR}
SHELL ["/bin/bash", "-c"]

# `apt_mirror` and `pypi_mirror` can be specified at build time to replace the default mirror source to speed up the build process.
# --build-arg apt_mirror=<mirror>, e.g. --build-arg apt_mirror=mirrors.tuna.tsinghua.edu.cn
# --build-arg pypi_mirror=<mirror>, e.g. --build-arg pypi_mirror=https://pypi.tuna.tsinghua.edu.cn/simple
ARG apt_mirror=archive.ubuntu.com
ARG pypi_mirror=https://pypi.org/simple
ARG python_mirror=https://www.python.org/ftp/python
ARG python_version=3.12.3
ARG PYENV_ROOT=/root/.pyenv

# For Ubuntu 24.04, the sources.list is located at /etc/apt/sources.list.d/ubuntu.sources
RUN sed -i "s/archive.ubuntu.com/${apt_mirror}/g" /etc/apt/sources.list.d/ubuntu.sources

# For Ubuntu 22.04, the sources.list is located at /etc/apt/sources.list
# RUN sed -i "s/archive.ubuntu.com/${apt_mirror}/g" /etc/apt/sources.list

# Install dependencies
RUN yes | unminimize && \
    apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    git wget curl bash-completion apt-utils vim \
    zlib1g-dev libssl-dev libreadline-dev libbz2-dev libsqlite3-dev liblzma-dev \
    build-essential cmake ninja-build clang clangd lld ccache gdb

ENV PYTHON_BUILD_MIRROR_URL=${python_mirror} \
    PYTHON_BUILD_MIRROR_URL_SKIP_CHECKSUM=1 \
    PATH=${PYENV_ROOT}/bin:$PATH

# Install pyenv and pyenv-virtualenv
RUN git clone https://github.com/pyenv/pyenv.git ~/.pyenv && \
    git clone https://github.com/pyenv/pyenv-virtualenv.git ${PYENV_ROOT}/plugins/pyenv-virtualenv && \
    echo 'eval "$(pyenv init -)"' >> ~/.bashrc && \
    echo 'eval "$(pyenv virtualenv-init -)"' >> ~/.bashrc

RUN pyenv install ${python_version} && \
    pyenv global ${python_version} && \
    pyenv rehash

RUN eval "$(pyenv init -)" && \
    pip config set global.index-url ${pypi_mirror} && \
    pip install numpy pybind11

# Build LLVM
RUN git clone https://github.com/llvm/llvm-project.git
RUN eval "$(pyenv init -)" && \
    mkdir llvm-project/build llvm-project/install && \
    cd llvm-project/build && \
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
        -DCMAKE_INSTALL_PREFIX=../install && \
    ninja install

ENV LLVM_BUILD_DIR=${WORKDIR}/llvm-project/build \
    LLVM_INSTALL_DIR=${WORKDIR}/llvm-project/install \
    PATH=${WORKDIR}/llvm-project/build/bin:${PATH}

# Clean up
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

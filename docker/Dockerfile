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
    git wget curl bash-completion apt-utils vim unzip pigz \
    zlib1g-dev libssl-dev libreadline-dev libbz2-dev libsqlite3-dev liblzma-dev libffi-dev \
    build-essential ccache gdb

# Get the latest version of cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.29.4/cmake-3.29.4-linux-x86_64.sh  && \
    chmod +x cmake-3.29.4-linux-x86_64.sh && \
    ./cmake-3.29.4-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-3.29.4-linux-x86_64.sh

# Get the latest version of ninja
RUN wget https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-linux.zip && \
    unzip ninja-linux.zip -d /usr/local/bin && \
    rm ninja-linux.zip

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

ARG LLVM_PROJECT_DIR=${WORKDIR}/llvm-project

ENV LLVM_BUILD_DIR=${LLVM_PROJECT_DIR}/build \
    LLVM_INSTALL_DIR=${LLVM_PROJECT_DIR}/install \
    PATH=${LLVM_PROJECT_DIR}/build/bin:${PATH}

# Get llvm-project
RUN git clone https://github.com/llvm/llvm-project.git ${LLVM_PROJECT_DIR}

# Build clang, clang-tools-extra and lld
RUN eval "$(pyenv init -)" && \
    mkdir ${LLVM_BUILD_DIR} && \
    cd ${LLVM_BUILD_DIR} && \
    cmake -G Ninja ../llvm \
        -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;lld" \
        -DLLVM_CCACHE_BUILD=ON \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_COMPILER=gcc \
        -DCMAKE_CXX_COMPILER=g++ && \
    ninja install && \
    rm -rf ${LLVM_BUILD_DIR}

# Build MLIR
RUN eval "$(pyenv init -)" && \
    mkdir ${LLVM_BUILD_DIR} ${LLVM_INSTALL_DIR} && \
    cd ${LLVM_BUILD_DIR} && \
    cmake -G Ninja ../llvm \
        -DLLVM_ENABLE_PROJECTS="mlir" \
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

# Clean up
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

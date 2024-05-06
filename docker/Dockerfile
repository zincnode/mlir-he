FROM ubuntu:24.04
# FROM ubuntu:22.04

ARG WORKDIR=/workdir
WORKDIR ${WORKDIR}

# `apt_mirror` and `pypi_mirror` can be specified at build time to replace the default mirror source to speed up the build process.
# --build-arg apt_mirror=<mirror>, e.g. --build-arg apt_mirror=mirrors.tuna.tsinghua.edu.cn
# --build-arg pypi_mirror=<mirror>, e.g. --build-arg pypi_mirror=https://pypi.tuna.tsinghua.edu.cn/simple
ARG apt_mirror=archive.ubuntu.com
ARG pypi_mirror=https://pypi.org/simple

# For Ubuntu 24.04, the sources.list is located at /etc/apt/sources.list.d/ubuntu.sources
RUN sed -i "s/archive.ubuntu.com/${apt_mirror}/g" /etc/apt/sources.list.d/ubuntu.sources

# For Ubuntu 22.04, the sources.list is located at /etc/apt/sources.list
# RUN sed -i "s/archive.ubuntu.com/${apt_mirror}/g" /etc/apt/sources.list

# Install dependencies
RUN yes | unminimize && \
    apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    git wget curl bash-completion apt-utils vim \
    build-essential cmake ninja-build clang clangd lld ccache gdb

# Install miniconda
ENV PATH="/opt/conda/bin:${PATH}"
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh && \
    bash Miniconda3-latest-Linux-x86_64.sh -b -p /opt/conda && \
    rm Miniconda3-latest-Linux-x86_64.sh && \
    conda init bash && \
    . /opt/conda/etc/profile.d/conda.sh && \
    conda activate base

RUN pip config set global.index-url ${pypi_mirror} && \
    pip install numpy pybind11

# Build LLVM
RUN git clone https://github.com/llvm/llvm-project.git
RUN mkdir llvm-project/build llvm-project/install && \
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

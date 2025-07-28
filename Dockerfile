FROM csdms/bmi:0.2.1

COPY . /opt/bmi-example-cxx
WORKDIR /opt/bmi-example-cxx/_build
RUN cmake .. -DCMAKE_INSTALL_PREFIX=${CONDA_DIR} && \
    make && \
    make test && \
    make install && \
    make clean

WORKDIR /opt

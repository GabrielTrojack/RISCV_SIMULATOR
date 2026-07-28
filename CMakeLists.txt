cmake_minimum_required(VERSION 3.16)

project(RiscVSimulator)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(simulador
    src/main.cpp
    src/CPU.cpp
    src/LeitorDeArquivos.cpp
    src/DecodificadorDeInstrucao.cpp
)
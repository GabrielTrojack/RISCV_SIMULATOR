#ifndef DECODIFICADOR_INSTRUCAO_H
#define DECODIFICADOR_INSTRUCAO_H

#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>

constexpr int OPCODE_OP = 51;
constexpr int OPCODE_OP_IMM = 19;
constexpr int OPCODE_LOAD = 3;
constexpr int OPCODE_STORE = 35;
constexpr int OPCODE_BRANCH = 99;

constexpr int FUNCT7_ADD = 0;
constexpr int FUNCT7_SUB = 32;
constexpr int FUNCT7_AND = 0;
constexpr int FUNCT7_OR = 0;

constexpr int FUNCT3_ADD = 0;
constexpr int FUNCT3_SUB = 0;
constexpr int FUNCT3_AND = 7;
constexpr int FUNCT3_OR = 6;
constexpr int FUNCT3_ADDI = 0;
constexpr int FUNCT3_LOAD = 2;
constexpr int FUNCT3_STORE = 2;
constexpr int FUNCT3_BEQ = 0;
constexpr int FUNCT3_BNE = 1;

using namespace std;

class InstrucaoDecodificada {
    public:
        InstrucaoDecodificada(string instrucao, int indiceRegDst, int indiceReg1, int indiceReg2, 
        int imm);
        string instrucao;
        int indiceRegDst;
        int indiceReg1;
        int indiceReg2;
        int imm;
};

class DecodificadorDeInstrucao {
    public:
        static InstrucaoDecodificada decodificar(string instrucao);

    private:
        static int binParaDec(string instrucao, int inicio, int fim, int maskstart);
        static void immNegativo(int &imm, int j);
};

#endif
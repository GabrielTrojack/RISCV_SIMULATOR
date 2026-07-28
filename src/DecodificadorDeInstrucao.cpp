#include "DecodificadorDeInstrucao.h"

InstrucaoDecodificada::InstrucaoDecodificada(string instrucao, int indiceRegDst, int indiceReg1, int indiceReg2, 
int imm) {
    this->instrucao = instrucao;
    this->indiceRegDst = indiceRegDst;
    this->indiceReg1 = indiceReg1;
    this->indiceReg2 = indiceReg2;
    this->imm = imm;
}

void DecodificadorDeInstrucao::immNegativo(int &imm, int j) {
    if (imm & (1<<j)) {
        while(j <= 31) {
            imm |= (1<<j);
            j++;
        }
    }
}

int DecodificadorDeInstrucao::binParaDec(string instrucao, int inicio, int fim, int maskstart) {
    int mask = 0;
    int j = maskstart;
    for(int i = inicio; i <= fim; i++, j++) {
        if (instrucao[i]=='1') mask |= (1<<j);
    }

    return mask;
}

InstrucaoDecodificada DecodificadorDeInstrucao::decodificar(string instrucao) {
    if (instrucao.size()!=32) {
        throw length_error("Tamanho da instrução não é de 32 bits");
    }

    reverse(instrucao.begin(), instrucao.end());

    int opcode = binParaDec(instrucao, 0, 6, 0);

    if (opcode == OPCODE_OP) { // add, sub, and, or
        int rd = binParaDec(instrucao, 7, 11, 0);
        int rs1 = binParaDec(instrucao, 15, 19, 0);
        int rs2 = binParaDec(instrucao, 20, 24, 0);

        int f3 = binParaDec(instrucao, 12, 14, 0);
        int f7 = binParaDec(instrucao, 25, 31, 0);

        string nome;
        if (f3 == FUNCT3_ADD && f7 == FUNCT7_ADD) nome = "add";
        else if (f3 == FUNCT3_SUB && f7 == FUNCT7_SUB) nome = "sub";
        else if (f3 == FUNCT3_AND && f7 == FUNCT7_AND) nome = "and";
        else if (f3 == FUNCT3_OR && f7 == FUNCT7_OR) nome = "or";

        return InstrucaoDecodificada(nome, rd, rs1, rs2, -1);
    }
    else if (opcode == OPCODE_OP_IMM) { // addi
        int rs1 = binParaDec(instrucao, 15, 19, 0);
        int rd = binParaDec(instrucao, 7, 11, 0);
        int imm = binParaDec(instrucao, 20, 31, 0);

        immNegativo(imm, 11);

        return InstrucaoDecodificada("addi", rd, rs1, -1, imm);
    }
    else if (opcode == OPCODE_LOAD) { // load (lw)
        int rs1 = binParaDec(instrucao, 15, 19, 0);
        int rd = binParaDec(instrucao, 7, 11, 0);
        int imm = binParaDec(instrucao, 20, 31, 0);

        immNegativo(imm, 11);

        return InstrucaoDecodificada("lw", rd, rs1, -1, imm);
    }
    else if (opcode == OPCODE_STORE) { // store (sw)
        int rs1 = binParaDec(instrucao, 15, 19, 0);
        int rs2 = binParaDec(instrucao, 20, 24, 0);
        int imm04 = binParaDec(instrucao, 7, 11, 0);
        int imm511 = binParaDec(instrucao, 25, 31, 5);

        int imm = imm04 | imm511;

        immNegativo(imm, 11);

        return InstrucaoDecodificada("sw", -1, rs1, rs2, imm);
    }
    else if (opcode == OPCODE_BRANCH) { // beq, bne
        int rs1 = binParaDec(instrucao, 15, 19, 0);
        int rs2 = binParaDec(instrucao, 20, 24, 0);
        int imm12 = binParaDec(instrucao, 31, 31, 12);
        int imm510 = binParaDec(instrucao, 25, 30, 5);
        int imm14 = binParaDec(instrucao, 8, 11, 1);
        int imm11 = binParaDec(instrucao, 7, 7, 11);

        int imm = imm12 | imm11 | imm510 | imm14;

        immNegativo(imm, 12);

        int f3 = binParaDec(instrucao, 12, 14, 0);

        string nome;
        if (f3 == FUNCT3_BEQ) nome = "beq";
        else if (f3 == FUNCT3_BNE) nome = "bne";

        return InstrucaoDecodificada(nome, -1, rs1, rs2, imm);
    }

}
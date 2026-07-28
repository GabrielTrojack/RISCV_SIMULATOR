#include "CPU.h"
#include "DecodificadorDeInstrucao.h"

#include <stdexcept>


CPU::CPU(){
    pc = 0;

    registrador = vector<int>(32,0);

    memoria = vector<int>(1024, 0);
    
}

//pc
int CPU::getPC(){
    return pc;
}
void CPU::setPC(int val){
    pc = val;
}
void CPU::aumentarPC(){
    pc++;
}

//Registradores
int CPU::lerRegistrador(int index){
    //identificando se o registrador e valido
    if (index<0||index>=32){
        throw out_of_range("Registrador invalido");
    }

    return registrador[index];
}

void CPU::escreverRegistrador(int index, int valor){
    if (index<0||index>=32){
        throw out_of_range("Registrador invalido");
    }
    //o registrador x0 nao pode res alterado seu valor e sempre 0
    if(index == 0)return;

    registrador[index]=valor;
}

//Memoria
int CPU::lerMemoria(int endereco){
    if (endereco<0 || endereco>=1024){
        throw out_of_range("Endereco de memoria invalido");
    }
    return memoria[endereco];
}

void CPU::escreverMemoria(int endereco, int valor){
    if (endereco<0 || endereco>=1024){
        throw out_of_range("Endereco de memoria invalido");
    }

    memoria[endereco] = valor;
}

void CPU::executaInstrucao(const InstrucaoDecodificada& inst) {
    string op = inst.instrucao;
    int rd = inst.indiceRegDst;
    int rs1 = inst.indiceReg1;
    int rs2 = inst.indiceReg2;
    int imm = inst.imm;

    if (op == "add") {
        escreverRegistrador(rd, lerRegistrador(rs1) + lerRegistrador(rs2));
        aumentarPC();
    }
    else if (op == "sub") {
        escreverRegistrador(rd, lerRegistrador(rs1) - lerRegistrador(rs2));
        aumentarPC();
    }
    else if (op == "and") {
        escreverRegistrador(rd, lerRegistrador(rs1) & lerRegistrador(rs2));
        aumentarPC();
    }
    else if (op == "or") {
        escreverRegistrador(rd, lerRegistrador(rs1) | lerRegistrador(rs2));
        aumentarPC();
    }
    else if (op == "addi") {
        escreverRegistrador(rd, lerRegistrador(rs1) + imm);
        aumentarPC();
    }
    else if (op == "lw") {
        int endereco_byte = lerRegistrador(rs1) + imm;
        int indice_vetor = endereco_byte / 4;
        escreverRegistrador(rd, lerMemoria(indice_vetor));
        aumentarPC();
    }
    else if (op == "sw") {
        int endereco_byte = lerRegistrador(rs1) + imm;
        int indice_vetor = endereco_byte / 4;

        escreverMemoria(indice_vetor, lerRegistrador(rs2));
        aumentarPC();
    }
    else if (op == "beq") {
        if (lerRegistrador(rs1) == lerRegistrador(rs2)) {
            setPC(getPC() + (imm / 4));
        } else {
            aumentarPC();
        }
    }
    else if (op == "bne") {
        if (lerRegistrador(rs1) != lerRegistrador(rs2)) {
            setPC(getPC() + (imm / 4));
        } else {
            aumentarPC();
        }
    }
    else {
        throw invalid_argument("Instrucao nao suportada pela CPU: " + op);
    }
}
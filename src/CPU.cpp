#include "CPU.h"

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
        throw out_of_range("Regidtrador invalido");
    }

    return registrador[index];
}

void CPU::escreverRegistrador(int index, int valor){
    if (index<0||index>=32){
        throw out_of_range("Regidtrador invalido");
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
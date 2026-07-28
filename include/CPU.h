#ifndef CPU_H
#define CPU_H

#include <vector>
#include "DecodificadorDeInstrucao.h"
using namespace std;

class CPU {

private:

    int pc;

    vector<int> registrador;

    vector<int> memoria;

public:

    CPU();

    int getPC();
    void setPC(int val);
    void aumentarPC();

    int lerRegistrador(int index);
    void escreverRegistrador(int index,int val);

    int lerMemoria(int address);
    void escreverMemoria(int address,int val);
    void executaInstrucao(const InstrucaoDecodificada& inst);

};

#endif
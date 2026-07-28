#include <iostream>

#include "../include/CPU.h"
#include "../include/LeitorDeArquivos.h"
#include "../include/DecodificadorDeInstrucao.h"

using namespace std;

void imprimirSinaisDeControle(const string& op) {
    cout << "Sinais de controle para " << op << ":" << endl;

    string regWrite, aluSrc, memRead, memWrite, memToReg, branch;

    if (op == "add" || op == "sub" || op == "and" || op == "or") {
        regWrite = "1";
        aluSrc   = "0";
        memRead  = "0";
        memWrite = "0";
        memToReg = "0";
        branch   = "0";
    }
    else if (op == "addi") {
        regWrite = "1";
        aluSrc   = "1";
        memRead  = "0";
        memWrite = "0";
        memToReg = "0";
        branch   = "0";
    }
    else if (op == "lw") {
        regWrite = "1";
        aluSrc   = "1";
        memRead  = "1";
        memWrite = "0";
        memToReg = "1";
        branch   = "0";
    }
    else if (op == "sw") {
        regWrite = "0";
        aluSrc   = "1";
        memRead  = "0";
        memWrite = "1";
        memToReg = "X";
        branch   = "0";
    }
    else if (op == "beq" || op == "bne") {
        regWrite = "0";
        aluSrc   = "0";
        memRead  = "0";
        memWrite = "0";
        memToReg = "X";
        branch   = "1";
    }
    else {
        cout << "Instrucao nao reconhecida para mapeamento de controle." << endl;
        return;
    }

    cout << " - RegWrite: " << regWrite << endl;
    cout << " - ALUSrc:   " << aluSrc << endl;
    cout << " - MemRead:  " << memRead << endl;
    cout << " - MemWrite: " << memWrite << endl;
    cout << " - MemtoReg: " << memToReg << endl;
    cout << " - Branch:   " << branch << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    LeitorDeArquivos leitor;
    DecodificadorDeInstrucao decoder;
    CPU cpu;

    string nomeArquivo;
    cout << "Informe o arquivo:" << endl;
    getline(cin, nomeArquivo);
    vector<string> instrucoes = leitor.lerArquivos(nomeArquivo);

    if (instrucoes.empty()) {
        cerr << "Erro ao abrir o arquivo ou arquivo vazio." << endl;
        return 1;
    }

    cout << "Programa carregado. Total de instrucoes: " << instrucoes.size() << endl;
    cout << "----------------------------------------" << endl;

    while (cpu.getPC() >= 0 && cpu.getPC() < instrucoes.size()) {

        cout << "[Pressione ENTER para executar a proxima instrucao]" << endl;
        cin.get();

        int pcAtual = cpu.getPC();
        string linhaBinaria = instrucoes[pcAtual];

        try {
            InstrucaoDecodificada inst = decoder.decodificar(linhaBinaria);

            cout << "PC atual: " << pcAtual << endl;
            cout << "Instrucao decodificada: " << inst.instrucao << endl;

            imprimirSinaisDeControle(inst.instrucao);

            cpu.executaInstrucao(inst);

            if (inst.indiceRegDst != -1 && inst.indiceRegDst != 0) {
                cout << "Registrador x" << inst.indiceRegDst
                     << " atualizado para: " << cpu.lerRegistrador(inst.indiceRegDst) << endl;
                cout << "----------------------------------------" << endl;
            }

        } catch (const exception& e) {
            cerr << "Erro fatal durante a execucao: " << e.what() << endl;
            break;
        }
    }

    cout << "Fim da execucao do programa." << endl;

    return 0;
}
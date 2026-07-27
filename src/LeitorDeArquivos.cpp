#include "LeitorDeArquivos.h"
#include <fstream>

using namespace std;

vector<string> LeitorDeArquivos::lerArquivos(string programa) {

    vector<string> instrucoes;

    ifstream arquivo(programa);

    if (!arquivo.is_open()) {
        return instrucoes;
    }

    string linha;

    while (getline(arquivo, linha)) {
        if (!linha.empty()) {
            instrucoes.push_back(linha);
        }
    }

    arquivo.close();

    return instrucoes;
}
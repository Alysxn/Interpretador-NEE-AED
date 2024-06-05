#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;

template<typename T>
class No {
public:
    T funcao;
    T linha;
    No* prox;

    No() : funcao(T()), linha(T()), prox(nullptr) { }

    No(T _funcao, T _linha) : funcao(_funcao), linha(_linha), prox(nullptr) { }
};

template<typename T>
class PilhaFuncaoNee {
private:
    No<T>* topo;
    No<T>* fundo;

public:
    PilhaFuncaoNee() {
        fundo = new No<T>();
        fundo->prox = nullptr;
        topo = fundo;
    };

    void empilhaFuncao(T index, T linha) {
        No<T>* aux = new No<T>(index, linha);
        aux->prox = topo;
        topo = aux;
    }

    bool vazia() {
        return topo == fundo;
    }

    void retiraNo() {
        if (vazia()) {
            cout << "Pilha está vazia, não é possível retirar nenhum nó.\n";
            return;
        }
        No<T>* temp = topo;
        topo = topo->prox;
        delete temp;
    }

    T getFuncaoTopo() {
        if (vazia()) {
            cout << "Pilha está vazia, não há topo.\n";
            return T();
        }
        return topo->funcao;
    }

    T getLinhaTopo() {
        if (vazia()) {
            cout << "Pilha está vazia, não há topo.\n";
            return T();
        }
        return topo->linha;
    }
};

class CodigoNee {
public:
    string linha;

    CodigoNee() : linha("") {}

    CodigoNee(string _linha) : linha(_linha) {}

    void recebeLinha(string _linha) {
        linha = _linha;
    }

    bool verificaPrintNee(const string& p) {
        return (p.length() >= 10 && p.substr(0, 10) == "    PRINT ");
    }

    bool verificaFuncao(const string& funcao) {
        return (funcao.length() == 5 && funcao[0] == ' ' && isalpha(funcao[4]));
    }

    string converteFuncao(const string& funcao) {
        string novaFuncao = funcao.substr(4, 1) + " :";
        return novaFuncao;
    }

    void printaPrint(const string& p) {
        cout << p.substr(10) << " ";
    }
};

template<typename T>
class ListaCodigoNee {
public:
    int TAM;
    int n;
    CodigoNee* codigo;
    PilhaFuncaoNee<T>* pilhaNee;

    ListaCodigoNee(int _TAM) : TAM(_TAM), n(0) {
        codigo = new CodigoNee[TAM + 1];
        pilhaNee = new PilhaFuncaoNee<T>();
    };

    void insereLinha(CodigoNee c) {
        if (n < TAM) {
            codigo[n++] = c;
        } else {
            cout << "Quantidade de linhas excedeu a capacidade do compilador.";
        }
    };

    int buscaFuncao(const string& funcao) {
        for (int i = 0; i < n; i++) {
            if (codigo[i].linha == funcao) {
                return i;
            }
        }
        return -1;
    };

    void compilaFuncoesIterativamente(string funcao) {
        int firstIndex = buscaFuncao(funcao);
        if (firstIndex == -1) {
            cout << "Função " << funcao << " não encontrada.\n";
            return;
        }

        pilhaNee->empilhaFuncao(firstIndex, firstIndex + 1);
        while (!pilhaNee->vazia()) {
            int funcaoIndex = pilhaNee->getFuncaoTopo();
            int linhaIndex = pilhaNee->getLinhaTopo();
            pilhaNee->retiraNo();

            for (int i = linhaIndex; i < n && codigo[i].linha != ""; i++) {
                if (codigo->verificaPrintNee(codigo[i].linha)) {
                    codigo->printaPrint(codigo[i].linha);
                } else if (codigo->verificaFuncao(codigo[i].linha)) {
                    string novaFuncao = codigo->converteFuncao(codigo[i].linha);
                    int novaFuncaoIndex = buscaFuncao(novaFuncao);
                    if (novaFuncaoIndex != -1) {
                        pilhaNee->empilhaFuncao(funcaoIndex, i + 1);
                        pilhaNee->empilhaFuncao(novaFuncaoIndex, novaFuncaoIndex + 1);
                        break;
                    }
                }
            }
        }
    }

    void compila() {
        int posicaoInicioZ = buscaFuncao("Z :");
        if (posicaoInicioZ == -1) {
            cout << "Z : não encontrado\n";
            return;
        }

        for (int i = posicaoInicioZ + 1; i < n && codigo[i].linha != ""; i++) {
            if (codigo->verificaPrintNee(codigo[i].linha)) {
                codigo->printaPrint(codigo[i].linha);
            } else if (codigo->verificaFuncao(codigo[i].linha)) {
                string funcao = codigo->converteFuncao(codigo[i].linha);
                compilaFuncoesIterativamente(funcao);
            }
        }
    }
};

int main() {
    int quantLinhas;
    quantLinhas = 300;
    CodigoNee codigo("");
    ListaCodigoNee<int> l(quantLinhas);
    string linha;

    while (true) {
        getline(cin, linha);
        if (linha == "~") break;
        codigo.recebeLinha(linha);
        l.insereLinha(codigo);
    }

    l.compila();

    cout << "\n";

    return 0;
}

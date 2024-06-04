#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;

//Projeto AED1 - Implementação por:  Alyson Souza Silva e Luiza Marinho Diniz Schirmer

template<typename T>
class NoFila{
public:
    T print;
    NoFila *prox;

    NoFila() : prox(nullptr) {}

    NoFila(T _print) : print(_print), prox(nullptr) {}
};

template<typename T>
class filaPrintNee{
private:
    NoFila<T>* frente;
    NoFila<T>* tras;

public:
    filaPrintNee(){
        frente = new NoFila<T>();
        frente->prox = nullptr;
        tras = frente;
    }

    void enfilera(T numero){
        tras->prox = new NoFila<T>();
        tras = tras->prox;
        tras->print = numero;
        tras->prox = nullptr;
    }

    void imprimeFila(){
        NoFila<T>* temp = frente->prox;
        cout << "Fila de numeros que serao printados: " << "\n";
        while (temp != nullptr) {
            std::cout << temp->print << " ";
            temp = temp->prox;
        }
        std::cout << std::endl;
    }
};

template<typename T>
class No{
public:
    T funcao;
    bool vistada;
    No *prox;

    No() : prox(nullptr) {}

    No(T _funcao) : funcao(_funcao), prox(nullptr) {}
};

template<typename T>
class PilhaFuncaoNee{
private:
    No<T>* topo;
    No<T>* fundo;

public:
    PilhaFuncaoNee(){
        fundo = new No<T>();
        fundo->prox = nullptr;
        topo = fundo;
    }

    void empilhaFuncao(T funcao){
        No<T>* aux = new No<T>();
        topo->funcao = funcao;
        topo->vistada = false;
        aux->prox = topo;
        topo = aux;
    }

    void imprimePilha(){
        No<T>* Notemp = topo;
        cout << "Pilha de funcoes Nee: \n";
        while (Notemp != nullptr)
        {
            cout << Notemp->funcao << "\n";
            Notemp = Notemp->prox;
        }
    }

    bool buscaFuncao(T funcao) {
        No<T>* atual = topo;
        while (atual != nullptr) {
            if (atual->funcao == funcao) {
                atual->vistada = true;
                cout << "Funcao encontrada: " << funcao << atual->vistada << "\n";
                return true;  // Função encontrada
            }
            atual = atual->prox;
        }

        return false;  // Função não encontrada
    }

        void desalocaFuncoes() {
        while (topo != fundo) {
            No<T>* temp = topo;
            topo = topo->prox;
            delete temp;
        }
        delete fundo;  // Delete the sentinel node
        fundo = nullptr;
        topo = nullptr;
    }

};

template<typename T>
class CodigoNee{
public:
    T linha;
    PilhaFuncaoNee<T> *funcaoNee;

    CodigoNee() : linha("") {
        funcaoNee = new PilhaFuncaoNee<T>();
    }

    CodigoNee(T _linha) : linha(_linha) {
        funcaoNee = new PilhaFuncaoNee<T>();
    }

    void recebeLinha(T _linha){
        linha = _linha;
        if(linha == "Z :"){
            funcaoNee->empilhaFuncao(linha);
        }

        if (linha != "Z :" && !linha.empty() && linha.back() == ':') {
            funcaoNee->empilhaFuncao(linha);
        }
    }

    void verificaPrintNee(T p, filaPrintNee<T> &fila){
        if(p.substr(0, 9) == "    PRINT"){
            T printNumero = p.substr(10);
            if (printNumero.find_first_not_of("0123456789") == string::npos){
                fila.enfilera(printNumero);
            }
        }
    }

    bool verificaFuncao(T &funcao){
        return funcao.length() == 5;
    }

    T converteFuncao(T &funcao){
        funcao.erase(0, 4);
        return funcao + " :";
    }
};

template<typename T>
class ListaCodigoNee{
public:
    int TAM;
    int n;
    CodigoNee<T> *codigo;
    filaPrintNee<T> *printNee;
    PilhaFuncaoNee<T> *pilhaNee;

    ListaCodigoNee(int _TAM) : TAM(_TAM){
        codigo = new CodigoNee<T>[TAM + 1];
        n = 0;
        printNee = new filaPrintNee<T>();
        pilhaNee = new PilhaFuncaoNee<T>();
    }

    void insereLinha(CodigoNee<T> c){
        if(n < TAM){
            n++;
            codigo[n] = c;
        }
        else{
            cout << "Quantidade de linhas excedeu a capacidade do compilador.";
        }
    }

    int buscaFuncao(T funcao){
        for(int i = 0; i < TAM; i++){
            if (codigo[i].linha == funcao)
            {
                return i;
                break;
            }
        }
        return 0;
    }

    void compilaFuncoes(T funcao){
        bool fimFuncao = false;
        int index = buscaFuncao(funcao);
        while (fimFuncao == false)
        {
            index++;
            codigo->verificaPrintNee(codigo[index].linha, *printNee);
            if(codigo->verificaFuncao(codigo[index].linha)){
                // se for uma chamada de funcao, converte para FUNCAO + :
                T funcao = codigo->converteFuncao(codigo[index].linha);
                // passa a nova função para compilaFuncoes 
                compilaFuncoes(funcao);
            }

            if (codigo[index].linha == "")
            {
                fimFuncao = true;
            }
        }
    }

    void compila(){
        int posicaoInicioZ = -1;
        int posicaoFinalZ = -1;
        int indexZ;

        // busca Z :
        for(int i = 0; i < TAM; ++i){
            if(codigo[i].linha == "Z :"){
                posicaoInicioZ = i;
                break;
            }
        }

        // Verificação se Z foi encontrado
        if(posicaoInicioZ == -1) {
            cout << "Z : não encontrado\n";
            return;
        }

        // busca fim de Z :
        for(int i = 0; i < TAM; ++i){
            if(codigo[posicaoInicioZ + i].linha == ""){
                posicaoFinalZ = posicaoInicioZ + i;
                break;
            }
        }

        // Verificação se o fim de Z foi encontrado
        if(posicaoFinalZ == -1) {
            cout << "Fim de Z não encontrado\n";
            return;
        }

        indexZ = posicaoInicioZ + 1;

        cout << "index de Z :" <<  posicaoInicioZ << "\n";
        cout << "index fim de Z :" << posicaoFinalZ << "\n";


        while(indexZ != posicaoFinalZ)
        {
            // caso seja um print, adicionará a fila
            codigo->verificaPrintNee(codigo[indexZ].linha, *printNee);

            // verifica se é uma chamada de funcao
            if(codigo->verificaFuncao(codigo[indexZ].linha)){
                // se for uma chamada de funcao, converte para FUNCAO + :
                T funcao = codigo->converteFuncao(codigo[indexZ].linha);

                compilaFuncoes(funcao);
            }

            ++indexZ;  // Incrementar indexZ para evitar loop infinito
        }
    }
};

int main(){
    int quantLinhas;
    quantLinhas = 300;
    CodigoNee<string> codigo("");
    ListaCodigoNee<string> l(quantLinhas);
    string linha;

    while(linha != "~"){
        getline(cin, linha);
        codigo.recebeLinha(linha);
        l.insereLinha(codigo);
    }

    l.compila();

    cout << "\n";

    l.printNee->imprimeFila();

    cout << "\n";

    codigo.funcaoNee->imprimePilha();

    cout << "\n";

    cout << "Fim da compilacao, removendo pilha de funcoes." << "\n";

    codigo.funcaoNee->desalocaFuncoes();

    cout << "\n";
    
    codigo.funcaoNee->imprimePilha();

    return 0;
}

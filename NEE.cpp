#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;

class NoFila{
    public:
    string print;
    NoFila *prox;

    NoFila(): prox(nullptr) { }

    NoFila(string _print): print(_print), prox(nullptr) {}
};



class filaPrintNee{
    private:
    NoFila* frente;
    NoFila* tras;

    public:
    filaPrintNee(){
        frente = new NoFila();
        frente->prox = nullptr;
        tras = frente;
    };

    void enfilera(string numero){
        tras->prox = new NoFila;
        tras = tras->prox;
        tras->print = numero;
        tras->prox = nullptr;

    }

    void imprimeFila(){
        NoFila* temp = frente->prox;
        cout << "Fila de numeros que serao printados: " << "\n";
        while (temp != nullptr) {
            std::cout << temp->print << " ";
            temp = temp->prox;
        }
        std::cout << std::endl;
    }

};


class No{
    public:
    string funcao;
    bool vistada;
    No *prox;

    No(): prox(nullptr) { }

	No(string _funcao): funcao(_funcao), prox(nullptr) { }

};



class PilhaFuncaoNee{
    private:
    No* topo;
    No* fundo;

    public:
    PilhaFuncaoNee(){
        fundo = new No();
        fundo->prox = nullptr;
        topo = fundo;
    };

    void empilhaFuncao(string funcao){
        No* aux = new No();
        topo->funcao = funcao;
        topo->vistada = false;
        aux->prox = topo;
        topo = aux;
    };

    void imprimePilha(){
        No* Notemp = topo;
        cout << "funcoes Nee: \n";
        while (Notemp != nullptr)
        {
            cout << Notemp->funcao << Notemp->vistada << "\n";
            Notemp = Notemp->prox;
            
        }
        
    }

    bool buscaFuncao(string funcao) {
        No* atual = topo;
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

};


class CodigoNee{
    public:
    string linha;
    PilhaFuncaoNee *funcaoNee;


    CodigoNee() : linha("") {
        funcaoNee = new PilhaFuncaoNee();
    }

    CodigoNee(string _linha): linha(_linha){
          funcaoNee = new PilhaFuncaoNee();
    };
    
    void recebeLinha(string _linha){
        linha = _linha;
        if(linha == "Z :"){
            funcaoNee->empilhaFuncao(linha);
        }

        if (linha != "Z :" && !linha.empty() && linha.back() == ':') {
            funcaoNee->empilhaFuncao(linha);
        }
    }
    
    void verificaPrintNee(string p, filaPrintNee &fila){
        if(p.substr(0, 9) == "    PRINT"){
            string printNumero = p.substr(10);
            if (printNumero.find_first_not_of("0123456789") == string::npos){
                fila.enfilera(printNumero);
            }
        }
    }

    bool verificaFuncao(string &funcao){
        return funcao.length() == 5;
    }

    string converteFuncao(string &funcao){
        funcao.erase(0,4);
        return funcao + " :";
    }

};




class ListaCodigoNee{
    public:
    int TAM;
    int n;
    CodigoNee *codigo;
    filaPrintNee *printNee;
    PilhaFuncaoNee *pilhaNee;

    
    ListaCodigoNee(int _TAM): TAM(_TAM){
        codigo = new CodigoNee[TAM + 1];
        n = 0;
        printNee = new filaPrintNee();
        pilhaNee = new PilhaFuncaoNee();
    };

    void insereLinha(CodigoNee c){
        if(n < TAM){
            n++;
            codigo[n] = c;
        }
        else{
            cout << "Quantidade de linhas excedeu a capacidade do compilador.";
        }
    };

    int buscaFuncao(string funcao){
        for(int i = 0; i < TAM; i++){
            if (codigo[i].linha == funcao)
            {
                return i;
                break;
            } 
        }
        return 0;
    };

    void compilaFuncoes(string funcao){
        bool fimFuncao = false;
        int index = buscaFuncao(funcao);
        while (fimFuncao == false)
        {
            index++;
            codigo->verificaPrintNee(codigo[index].linha, *printNee);
            if(codigo->verificaFuncao(codigo[index].linha)){
                // se for uma chamada de funcao, converte para FUNCAO + :
                string funcao = codigo->converteFuncao(codigo[index].linha);
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
                string funcao = codigo->converteFuncao(codigo[indexZ].linha);
                
                compilaFuncoes(funcao);
            }

            ++indexZ;  // Incrementar indexZ para evitar loop infinito
        }
    }
};



int main(){

    int quantLinhas;
    quantLinhas = 10000;
    CodigoNee codigo("");
    ListaCodigoNee l(quantLinhas);
    string linha;

    while(linha != "~"){
        getline(cin, linha);
        codigo.recebeLinha(linha);
        l.insereLinha(codigo);
    };


    l.compila();

    cout << "\n";
    l.printNee->imprimeFila();

    l.pilhaNee->imprimePilha();


    
    return 0;

}

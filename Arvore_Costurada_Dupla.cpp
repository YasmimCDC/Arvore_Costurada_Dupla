#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Arvore_Costurada_Dupla.h"

using namespace std;

// ArCosDup == Árvore com costura dupla.
struct ArvCosDup {
    int info;
    struct ArvCosDup* esq;
    struct ArvCosDup* dir;
    bool costuraDir, costuraEsq; // Sinalizadores de costura.
};

// Função que inicializa a árvore
ArvCosDup* criarArvoreVazia(){
    return NULL;
}

// Função que retorna se a árvore está vazia
bool arvoreVazia(ArvCosDup* raiz){
    return (raiz == NULL);
}

//inserção de elementos na árvore
void inserirElemento(ArvCosDup** raiz, int novaInfo){

    // Alocação de memória para novo elemento e atribuição de informações
    ArvCosDup* novoElemento = (ArvCosDup*)malloc(sizeof(ArvCosDup));
    novoElemento->info = novaInfo;
    novoElemento->esq = NULL;
    novoElemento->dir = NULL;
    novoElemento->costuraDir = true;
    novoElemento->costuraEsq = true;

    //Inserção em árvore vazia: quando há apenas um elemento, não é necessário fazer a costura
    if(arvoreVazia(*raiz)){
        (*raiz) = novoElemento;
        novoElemento->dir = NULL;
        novoElemento->esq = NULL;
    }
    // Inserção em árvore não vazia
    else{

        // Criação de auxiliares para percorrer a árvore.
        ArvCosDup* anterior = NULL;   // Guarda o nó q já foi verificado (pai)
        ArvCosDup* atual = *raiz;     // Guarda o nó q esta sendo verificado.

        // Loop de busca para identificar o local de inserção do novo nó.
        while (atual){
            anterior = atual;

            // Caso a informação nó a ser inserido já estiver na árvore
            if(atual->info == novaInfo){
                cout << "\nElemento já existe na árvore\n";
                return;
            }
            // Se nova informação for menor, segue a esquerda
            else if (novaInfo < atual->info){
                if(atual->costuraEsq){
                    break;
                }
                atual = atual->esq;
            }
            else{

                if(atual->costuraDir){
                    atual = NULL;        // Para o Loop quando acha uma costura a direita do nó atual.
                }else{
                    atual = atual->dir;  // Segue para a direita pois o novo elemento é maior do que o verificado.
                }
            }

        }

        // Caso novo nó seja adicionado a esquerda do nó encontrado anteriormente
        if(novaInfo < anterior->info){
            novoElemento->dir = anterior;
            novoElemento->esq = anterior->esq;     // Faz a costura com o seu sucessor em ordem.
            anterior->costuraEsq = false;          // retira a costura a esquerda do no anterior
            anterior->esq = novoElemento;          // Adiciona o novo elemento a esquerda.

        }

        else {
            // Caso o novo nó seja adicionado a direita do nó encontrado anteriormente.
            novoElemento->dir = anterior->dir;     // Costura meu novo nó com o com o nó que o anterior estava costurado.
            novoElemento->esq = anterior;          // Costura o novo elemento com seu anterior
            anterior->costuraDir = false;          // Muda status do nó anterior para "sem costura"
            anterior->dir = novoElemento;          // Adiciona novo nó a direita do nó anterior
        }
    }
}

// Função auxiliar que retorna o nó mais a direita da árvore
ArvCosDup* noMaisADireita(ArvCosDup* raiz){
    //Auxiliar que percorre a árvore
    ArvCosDup* aux = raiz;
    // Caso a árvore for vazia
    if(aux == NULL){
        return NULL;
    }
        // Árvore não vazia
    else{
        // Passa auxiliar para esquerda até que não tenha mais nós a direita
        while (!aux->costuraDir){
            aux = aux->dir;
        }
    }
    return aux;

}

// Função auxiliar que retorna o nó mais a esquerda
ArvCosDup* noMaisAEsquerda(ArvCosDup* raiz){
    //Auxiliar que percorre a árvore
    ArvCosDup* aux = raiz;
    // Caso a árvore for vazia
    if(aux == NULL){
        return NULL;
    }
        // Árvore não vazia
    else{
        // Passa auxiliar para esquerda até que não tenha mais nós a esquerda
        while (!aux->costuraEsq){
            aux = aux->esq;
        }
    }
    return aux;

}

// Função de exibição da árvore na forma de leitura "em ordem".
void imprimirEmOrdem(ArvCosDup* raiz){

    ArvCosDup* aux = noMaisAEsquerda(raiz);    // começa pelo nó mais a esquerda da árvore
    while (aux){
        cout << aux->info << "\n";             // Exibe a informação do nó

        if(aux->costuraDir){                   // Prossegue pela costura para seu sucessor em ordem
            aux = aux->dir;
        }else{
            aux = noMaisAEsquerda(aux->dir);   // Caso não houver costura, verifica se há filhos a esquerda para manter a ordem.
        }
    }
    cout << endl;
}

// Função de exibição da árvore na forma de leitura "pós ordem".
void imprimirPosOrdem(ArvCosDup* raiz){
    ArvCosDup* aux = noMaisADireita(raiz);     // começa pelo nó mais a direita da árvore
    while(aux){
        cout << aux->info << "\n";             // Exibe a informação do nó
        if(aux->costuraEsq){                   // Prossegue pela costura para seu sucessor em ordem
            aux = aux->esq;
        } else{
            aux = noMaisADireita(aux->esq);   // Caso não houver costura, verifica se há filhos a esquerda para manter a ordem.
        }
    }

    cout << endl;
}

// Funçaõ auxiliar que retorna se um elemento pertence a arvore.
bool pertence(ArvCosDup* raiz, int infoChave){
    ArvCosDup* aux = raiz;
    while (aux) {
        if ( aux->info == infoChave) {                          // Retorna true quando acha o elemento
            return true;
        }

        if (infoChave < aux->info && !aux->costuraEsq) {        // Busca a esquerda se a chave for menor
            aux = aux->esq;
        }
        else if (!aux->costuraDir){
            aux = aux->dir;                                     // Busca a direita se a chave de busca foe maior seguindo Em ordem
        }else {
            return false;
        }
    }
}

// Função que busca um nó através da informação que contem nele e retorna o retorna
ArvCosDup* buscarEmOrdem(ArvCosDup** raiz, int infoChave){
    // Auxiliar para buscar o nó  a ser removido.
    ArvCosDup *aux = *raiz;

    // Loop para encontrar o nó a ser removido
    while (aux->info != infoChave) {

        // Busca na sub arvore a direita pois a chave de busca é maior que a verificada
        if (aux->info < infoChave) {
            if (aux->dir) {
                aux = aux->dir;
            }
        }

        // Busca na sub arvore a esquerda pois a chave é menor do que a verificada
        else if (aux->info > infoChave) {
            if (aux->esq) {
                aux = aux->esq;
            }
        }
        // Para o loop quando encontra o nó a ser removido
        else {
            break;
        }
    }

    return aux;
}

// Função que retorna o elemento pai de um nó.
ArvCosDup* buscarPai(ArvCosDup** raiz, int infoChave){
    ArvCosDup *aux = *raiz;           // Auxiliar para buscar o nó  a ser removido.
    ArvCosDup *pai = NULL;            // Guarda o pai do nó a ser removido.

    // Loop para encontrar o nó a ser removido
    while (aux->info != infoChave) {

        // Busca na sub arvore a direita pois a chave de busca é maior que a verificada
        if (aux->info < infoChave) {
            if (aux->dir) {
                pai = aux;
                aux = aux->dir;
            }
        }

            // Busca na sub arvore a esquerda pois a chave é menor do que a verificada
        else if (aux->info > infoChave) {
            if (aux->esq) {
                pai = aux;
                aux = aux->esq;
            }
        }
            // Para o loop quando encontra o nó a ser removido
        else {
            break;
        }
    }

    return pai;
}

// Caso de exclusão para o nó é folhas
void exclusaoCaso1(ArvCosDup* raiz, ArvCosDup* pai, ArvCosDup* noEscoolhido){
    // Caso o nó a ser removido for a raiz da árvore.
    if (pai == NULL) {
        raiz = NULL;
    }

    // Caso o nó esteja a esquerda do pai, não importa se há costura pois a costura sempre leva ao pai
    else if(pai->esq == noEscoolhido){
        pai->esq = noEscoolhido->esq;
        pai->costuraEsq = true;
    }

    // Se o nó estiver a direita do pai, precisa-se verificar se há costura para manter a ordem de travessia
    else{
        pai->dir = noEscoolhido->dir;
        pai->costuraDir = true;
    }

    free(noEscoolhido);
}

// Caso de exclusão onde o nó possui apenas um filho.
void exclusaoCaso2(ArvCosDup* raiz, ArvCosDup* pai, ArvCosDup* noEscolhido){

    ArvCosDup* filho;

    // Se o nó escolhido tiver apenas fiilho a esquerda
    if(!noEscolhido->costuraEsq){
        filho = noEscolhido->esq;
        filho->dir = noEscolhido->dir;
    }
    // Se o nó escolhido tiver apenas filho direito
    else{
        filho = noEscolhido->dir;
        filho->esq = noEscolhido->esq;
    }

    // Caso nó for raiz
    if(pai == NULL){
        raiz = filho;
    }

    // Se o no estiver a direita do pai.
    if(pai->dir == noEscolhido){
        pai->dir = filho;

    }
    // Se o no estiver a direita do pai.
    else{
        pai->esq = filho;
    }

    free(noEscolhido);
}

// Caso de exclusão onde o nó possui ambos os filhos
void exclusaoCaso3(ArvCosDup* raiz, ArvCosDup* noEscolhido){
    ArvCosDup* paiDoSucessor = noEscolhido;
    ArvCosDup* sucessor = noEscolhido->dir;

    // Loop para encontrar o nó mais esquerda do sucessor
    while (!sucessor->costuraEsq){
        paiDoSucessor = sucessor;
        sucessor = sucessor->esq;
    }
    // Troca de informação com o nó escolhido.
    noEscolhido->info = sucessor->info;

    // Como a informacão já foi trocada, deve-se excluir o nó mais a esquerda da sub arvore a direita do nó escolhido.
    // Se esse nó for folha
    if(sucessor->costuraEsq && sucessor->costuraDir){
        exclusaoCaso1(raiz, paiDoSucessor, sucessor);
    }
    // Se nó possui um filho.
    else{
        exclusaoCaso2(raiz, paiDoSucessor, sucessor);
    }
}


// Função para excluir elemento através de chave de busca.
void excluirElemento(ArvCosDup** raiz, int infoChave) {
    // Só realiza a exclusão se o elemento pertencer a árvore.
    if (pertence(*raiz, infoChave)) {
        ArvCosDup* pai = buscarPai(raiz, infoChave);
        ArvCosDup* noEscolhido = buscarEmOrdem(raiz, infoChave);

        // Caso o nó a ser excluido for um nó folha
        if (noEscolhido->costuraEsq && noEscolhido->costuraDir){
            exclusaoCaso1(*raiz, pai, noEscolhido);
        }

        // No a ser excluido possui apenas um filho a esquerda
        else if (noEscolhido->costuraEsq) {
            // Tratamento para exclusão do elemento
            exclusaoCaso2(*raiz, pai, noEscolhido);

        }

        // Nó a ser excluido possuir apenas um filho a direita.
        else if (noEscolhido->costuraDir) {
            //tratamento para a exclusão do elemento.
            exclusaoCaso2(*raiz, pai, noEscolhido);
        }

        // No a ser excluido possui os dois filhos
        else {
            exclusaoCaso3(*raiz, noEscolhido);
        }
    }
    // Caso o elemento n pertença a árvore.
    else {
        cout << "Elemento não pertence a arvore\n";
    }
}


// Função para destruir (liberar a memória) da árvore.
void liberarArvore(ArvCosDup* raiz){
    if(!arvoreVazia(raiz)){
        liberarArvore(raiz->esq);
        if(raiz->costuraDir){
            liberarArvore(raiz->dir);
            free(raiz);
        }
    }
    raiz = NULL;
}

// Função de exibição de menu
void menu(){

    cout<<"======================================\n";
    cout<<"<> Árvore binária com costura dupla <>\n";
    cout<<"======================================\n";
    cout<<"1. Inserir elmento\n";
    cout<<"2. Excluir elemento\n";
    cout<<"3. Imprimir em ordem\n";
    cout<<"4. Imprimir pós ordem\n";
    cout<<"5. Destruir árvore\n";
    cout<<"6. Sair\n";

}

// Função de seleção de Menu
void selecao(){
    int val, ch;
    char sim='s';
    ArvCosDup *arvore = criarArvoreVazia();
    while(sim=='s'){
        cout<<"\nO que deseja fazer?:";cin>>ch;
        switch(ch){
            case 1:
                cout<<"Valor a adicionar:";cin>>val;
                inserirElemento(&arvore, val);
                break;

            case 2:
                cout<<"Valor a excluir:";cin>>val;
                excluirElemento(&arvore,val);
                break;

            case 3:
                cout<<"Árvore em ordem:\n";
                imprimirEmOrdem(arvore);
                break;

            case 4:
                cout<<"Árvore em pós ordem:\n";
                imprimirPosOrdem(arvore);
                break;

            case 5:
                liberarArvore(arvore);
                break;

            case 6:
                exit(0);

            default: cout<<"Invalid choice";

        }
        cout<<"Continuar?\ns/n:";cin>>sim;
    }

    liberarArvore(arvore);
}

// Função de teste das funções, caso não queira utilizar menu.
void teste(){
    ArvCosDup* arvore = criarArvoreVazia();

    inserirElemento(&arvore, 5);
    inserirElemento(&arvore, 10);
    inserirElemento(&arvore, 12);
    inserirElemento(&arvore, 9);
    inserirElemento(&arvore, 3);
    inserirElemento(&arvore, 4);
    inserirElemento(&arvore, 0);
    inserirElemento(&arvore, 1);
    inserirElemento(&arvore, 6);
    inserirElemento(&arvore, 2);
    inserirElemento(&arvore, 11);

    /*inserirElemento(&arvore, 6);
    inserirElemento(&arvore, 3);
    inserirElemento(&arvore, 8);
    inserirElemento(&arvore, 1);
    inserirElemento(&arvore, 5);
    inserirElemento(&arvore, 7);
    inserirElemento(&arvore, 11);
    inserirElemento(&arvore, 9);
    inserirElemento(&arvore, 13);

    inserirElemento(&arvore, 20);
    inserirElemento(&arvore, 10);
    inserirElemento(&arvore, 30);
    inserirElemento(&arvore, 5);
    inserirElemento(&arvore, 16);
    inserirElemento(&arvore, 14);
    inserirElemento(&arvore, 17);
    inserirElemento(&arvore, 13);*/

    imprimirEmOrdem(arvore);

    cout << "Imprimir pos ordem\n" << endl;

    imprimirPosOrdem(arvore);

    cout << "\nexcluindo 20\n" << endl;

    excluirElemento(&arvore, 20);

    imprimirEmOrdem(arvore);

    cout << "Imprimir pos ordem\n" << endl;

    imprimirPosOrdem(arvore);

    liberarArvore(arvore);

}
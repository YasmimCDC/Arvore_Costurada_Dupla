#ifndef ARVORE_COSTURADA_DUPLA_ARVORE_COSTURADA_DUPLA_H
#define ARVORE_COSTURADA_DUPLA_ARVORE_COSTURADA_DUPLA_H

struct ArvCosDup;                                          // Tipo de dado utilizado na árvore.

ArvCosDup* criarArvoreVazia();                             // Função que inicializa a árvore.
bool arvoreVazia(ArvCosDup*);                              // Função que retorna se a árvore está vazia.
void inserirElemento(ArvCosDup**, int);                    // Inserção de elementos na árvore.
ArvCosDup* noMaisADireita(ArvCosDup*);                     // Função auxiliar que retorna o nó mais a direita da árvore.
ArvCosDup* noMaisAEsquerda(ArvCosDup*);                    // Função auxiliar que retorna o nó mais a esquerda.
void imprimirEmOrdem(ArvCosDup*);                          // Função de exibição da árvore na forma de leitura "em ordem".
void imprimirPosOrdem(ArvCosDup*);                         // Função de exibição da árvore na forma de leitura "pós-ordem".
bool pertence(ArvCosDup*, int);                            // Funçaõ auxiliar que retorna se um elemento pertence a arvore.
ArvCosDup* buscarEmOrdem(ArvCosDup**, int);                // Função que busca um nó através da informação que contem nele e retorna o retorna.
ArvCosDup* buscarPai(ArvCosDup**, int);                    // Função que retorna o elemento pai de um nó.
void exclusaoCaso1(ArvCosDup*, ArvCosDup*, ArvCosDup*);    // Caso de exclusão onde o nó é folhas.
void exclusaoCaso2(ArvCosDup*, ArvCosDup*, ArvCosDup*);    // Caso de exclusão onde o nó possui apenas um filho.
void exclusaoCaso3(ArvCosDup*, ArvCosDup*);                // Caso de exclusão onde o nó possui ambos os filhos.
void excluirElemento(ArvCosDup**, int);                    // Função para excluir elemento através de chave de busca.
void liberarArvore(ArvCosDup*);                            // Função para destruir (liberar a memória) da árvore.
void menu();                                               // Função de exibição de Menu
void selecao();                                            // Função de seleção de Menu;
void teste();                                              // Função para realização de testes.

#endif //ARVORE_COSTURADA_DUPLA_ARVORE_COSTURADA_DUPLA_H

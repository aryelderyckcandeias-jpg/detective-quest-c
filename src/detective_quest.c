#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct Sala: representa um cômodo da mansão.
// Cada sala tem nome, pista opcional (NULL se não houver) e ponteiros para filhos.
typedef struct Sala {
    char* nome;              // Nome da sala (ex: "Hall")
    char* pista;             // Pista opcional (NULL se não houver)
    struct Sala* esquerda;   // Ponteiro para sala à esquerda
    struct Sala* direita;    // Ponteiro para sala à direita
} Sala;

// Definição da struct PistaNode: representa um nó da BST para pistas coletadas.
// Cada nó tem a pista (string) e ponteiros para filhos esquerdo e direito.
typedef struct PistaNode {
    char* pista;                    // Conteúdo da pista
    struct PistaNode* esquerda;     // Ponteiro para filho esquerdo
    struct PistaNode* direita;      // Ponteiro para filho direito
} PistaNode;

// Função criarSala: cria uma sala de forma dinâmica usando malloc.
// Recebe nome e pista (pista pode ser NULL se não houver).
// Retorna um ponteiro para a nova sala.
Sala* criarSala(char* nome, char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));  // Aloca memória para a sala
    if (novaSala == NULL) {
        printf("Erro: falha na alocação de memória para sala.\n");
        exit(1);
    }
    novaSala->nome = (char*)malloc(strlen(nome) + 1);  // Aloca e copia nome
    strcpy(novaSala->nome, nome);
    if (pista != NULL) {
        novaSala->pista = (char*)malloc(strlen(pista) + 1);  // Aloca e copia pista se existir
        strcpy(novaSala->pista, pista);
    } else {
        novaSala->pista = NULL;  // Sem pista
    }
    novaSala->esquerda = NULL;  // Inicializa ponteiros
    novaSala->direita = NULL;
    return novaSala;
}

// Função inserirPista: insere uma nova pista na BST de pistas coletadas.
// Recebe a raiz da BST (por referência) e a pista a inserir.
// Usa comparação alfabética para manter a ordem.
void inserirPista(PistaNode** raiz, char* pista) {
    if (*raiz == NULL) {
        // Cria novo nó se a raiz for NULL
        *raiz = (PistaNode*)malloc(sizeof(PistaNode));
        if (*raiz == NULL) {
            printf("Erro: falha na alocação de memória para pista.\n");
            exit(1);
        }
        (*raiz)->pista = (char*)malloc(strlen(pista) + 1);
        strcpy((*raiz)->pista, pista);
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;
    } else {
        // Insere recursivamente: esquerda se pista < raiz, direita se >
        if (strcmp(pista, (*raiz)->pista) < 0) {
            inserirPista(&((*raiz)->esquerda), pista);
        } else {
            inserirPista(&((*raiz)->direita), pista);
        }
    }
}

// Função explorarSalasComPistas: permite a navegação interativa pela árvore da mansão.
// Recebe a sala atual e a raiz da BST de pistas (por referência).
// Exibe nome da sala, coleta pista se existir, e permite escolher 'e', 'd' ou 's'.
// Continua até o jogador escolher 's'.
void explorarSalasComPistas(Sala* atual, PistaNode** pistasColetadas) {
    while (atual != NULL) {
        // Exibe localização atual
        printf("\nVocê está na sala: %s\n", atual->nome);
        
        // Coleta pista se existir
        if (atual->pista != NULL) {
            printf("Pista encontrada: %s\n", atual->pista);
            inserirPista(pistasColetadas, atual->pista);  // Adiciona à BST
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }
        
        // Menu de opções
        char escolha;
        printf("Escolha um caminho:\n");
        printf("e - Ir para a esquerda\n");
        printf("d - Ir para a direita\n");
        printf("s - Sair da exploração\n");
        printf("Sua escolha: ");
        scanf(" %c", &escolha);  // Lê escolha
        
        if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;  // Move para esquerda
            } else {
                printf("Não há caminho à esquerda. Tente novamente.\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;  // Move para direita
            } else {
                printf("Não há caminho à direita. Tente novamente.\n");
            }
        } else if (escolha == 's') {
            printf("Exploração interrompida pelo jogador.\n");
            break;  // Sai
        } else {
            printf("Escolha inválida. Tente novamente.\n");
        }
    }
}

// Função exibirPistas: imprime as pistas coletadas em ordem alfabética.
// Usa travessia in-order recursiva da BST.
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);  // Esquerda
        printf("- %s\n", raiz->pista);  // Raiz
        exibirPistas(raiz->direita);   // Direita
    }
}

// Função main: monta o mapa da mansão (árvore binária com pistas), inicia exploração e exibe pistas ao final.
int main() {
    // Criação das salas com pistas (folhas primeiro)
    Sala* estufa = criarSala("Estufa", "Uma chave antiga foi encontrada aqui.");
    Sala* lago = criarSala("Lago", NULL);  // Sem pista
    Sala* escritorio = criarSala("Escritório", "Um diário com anotações suspeitas.");
    Sala* varanda = criarSala("Varanda", NULL);
    Sala* despensa = criarSala("Despensa", "Restos de comida envenenada.");
    Sala* lavanderia = criarSala("Lavanderia", NULL);
    
    // Salas intermediárias
    Sala* jardim = criarSala("Jardim", "Pegadas frescas no chão.");
    jardim->esquerda = estufa;
    jardim->direita = lago;
    
    Sala* biblioteca = criarSala("Biblioteca", NULL);
    biblioteca->esquerda = escritorio;
    biblioteca->direita = varanda;
    
    Sala* salaDeEstar = criarSala("Sala de Estar", "Um bilhete rasgado.");
    salaDeEstar->esquerda = biblioteca;
    salaDeEstar->direita = jardim;
    
    Sala* cozinha = criarSala("Cozinha", NULL);
    cozinha->esquerda = despensa;
    cozinha->direita = lavanderia;
    
    // Raiz (Hall)
    Sala* hall = criarSala("Hall", NULL);
    hall->esquerda = salaDeEstar;
    hall->direita = cozinha;
    
    // BST para pistas coletadas (inicia vazia)
    PistaNode* pistasColetadas = NULL;
    
    // Início da exploração
    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansão, colete pistas e saia quando quiser.\n");
    explorarSalasComPistas(hall, &pistasColetadas);
    
    // Exibe pistas coletadas em ordem alfabética
    printf("\nPistas coletadas (em ordem alfabética):\n");
    exibirPistas(pistasColetadas);
    if (pistasColetadas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    // Liberação de memória (simplificada; em produção, libere recursivamente)
    // Omitido para brevidade, mas adicione funções de limpeza se necessário.
    
    return 0;
}

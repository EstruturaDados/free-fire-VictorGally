#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Definicao da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Constante para o tamanho maximo da mochila
#define MAX_ITENS 10

// Funcoes auxiliares
void menu();
void cadastrar_item(Item mochila[], int *contador);
void listar_itens(Item mochila[], int contador);
void remover_item(Item mochila[], int *contador);
void buscar_item(Item mochila[], int contador);
int encontrar_indice_por_nome(Item mochila[], int contador, const char *nome_busca);

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A mochila sera um array de structs Item
    Item mochila[MAX_ITENS];
    int contador_itens = 0; // Quantidade atual de itens na mochila
    int opcao;

    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        // Limpar o buffer de entrada para evitar problemas com gets() ou fgets() depois de scanf()
        while (getchar() != '\n'); 

        switch (opcao) {
            case 1:
                cadastrar_item(mochila, &contador_itens);
                break;
            case 2:
                remover_item(mochila, &contador_itens);
                break;
            case 3:
                buscar_item(mochila, contador_itens);
                break;
            case 4:
                printf("Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        
        // Listagem dos itens apos cada operacao (exceto sair)
        if (opcao >= 1 && opcao <= 3) {
            listar_itens(mochila, contador_itens);
        }

    } while (opcao != 4);

    return 0;
}

// Exibe o menu de opcoes
void menu() {
    printf("\n--- Sistema de Mochila ---\n");
    printf("1. Cadastrar item\n");
    printf("2. Remover item por nome\n");
    printf("3. Buscar item por nome (Busca Sequencial)\n");
    printf("4. Sair\n");
    printf("--------------------------\n");
}

// Funcao para cadastrar um novo item
void cadastrar_item(Item mochila[], int *contador) {
    if (*contador < MAX_ITENS) {
        printf("Digite o nome do item: ");
        fgets(mochila[*contador].nome, sizeof(mochila[*contador].nome), stdin);
        strtok(mochila[*contador].nome, "\n"); // Remover a quebra de linha

        printf("Digite o tipo do item (ex: arma, municao, cura): ");
        fgets(mochila[*contador].tipo, sizeof(mochila[*contador].tipo), stdin);
        strtok(mochila[*contador].tipo, "\n"); // Remover a quebra de linha

        printf("Digite a quantidade: ");
        scanf("%d", &mochila[*contador].quantidade);
        while (getchar() != '\n'); // Limpar buffer

        (*contador)++;
        printf("Item cadastrado com sucesso!\n");
    } else {
        printf("A mochila esta cheia! Maximo de %d itens.\n", MAX_ITENS);
    }
}

// Funcao para listar todos os itens na mochila
void listar_itens(Item mochila[], int contador) {
    printf("\n--- Itens na Mochila (%d/%d) ---\n", contador, MAX_ITENS);
    if (contador == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        for (int i = 0; i < contador; i++) {
            printf("Item %d:\n", i + 1);
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            printf("----------------------------------\n");
        }
    }
}

// Funcao para encontrar o indice de um item pelo nome (Busca Sequencial)
int encontrar_indice_por_nome(Item mochila[], int contador, const char *nome_busca) {
    for (int i = 0; i < contador; i++) {
        // strcasecmp para comparacao sem diferenciar maiusculas de minusculas (se disponivel no seu compilador)
        // Caso contrario, use strcmp para comparacao exata.
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            return i; // Item encontrado, retorna o indice
        }
    }
    return -1; // Item nao encontrado
}

// Funcao para remover um item da mochila
void remover_item(Item mochila[], int *contador) {
    char nome_busca[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nome_busca, sizeof(nome_busca), stdin);
    strtok(nome_busca, "\n"); // Remover quebra de linha

    int indice = encontrar_indice_por_nome(mochila, *contador, nome_busca);

    if (indice != -1) {
        // Mover os itens seguintes para preencher o espaco vazio (remoção logica)
        for (int i = indice; i < (*contador) - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*contador)--;
        printf("Item '%s' removido com sucesso!\n", nome_busca);
    } else {
        printf("Item '%s' nao encontrado na mochila.\n", nome_busca);
    }
}

// Funcao para buscar e exibir os dados de um item
void buscar_item(Item mochila[], int contador) {
    char nome_busca[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nome_busca, sizeof(nome_busca), stdin);
    strtok(nome_busca, "\n"); // Remover quebra de linha

    int indice = encontrar_indice_por_nome(mochila, contador, nome_busca);

    if (indice != -1) {
        printf("\n--- Item Encontrado ---\n");
        printf("  Nome: %s\n", mochila[indice].nome);
        printf("  Tipo: %s\n", mochila[indice].tipo);
        printf("  Quantidade: %d\n", mochila[indice].quantidade);
        printf("------------------------\n");
    } else {
        printf("Item '%s' nao encontrado na mochila.\n", nome_busca);
    }
}

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

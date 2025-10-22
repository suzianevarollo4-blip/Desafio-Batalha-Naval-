#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NUM_NAVIOS 3

/**
 * Cria e inicializa um tabuleiro vazio (preenchido com zeros)
 * 
 * @return Ponteiro para a matriz do tabuleiro alocada dinamicamente
 */
int** criar_tabuleiro() {
    // Aloca memória para a matriz do tabuleiro
    int** tabuleiro = (int**)malloc(TAMANHO_TABULEIRO * sizeof(int*));
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        tabuleiro[i] = (int*)malloc(TAMANHO_TABULEIRO * sizeof(int));
        
        // Inicializa todas as posições com 0 (água)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    return tabuleiro;
}

/**
 * Libera a memória alocada para o tabuleiro
 * 
 * @param tabuleiro Ponteiro para a matriz do tabuleiro
 */
void liberar_tabuleiro(int** tabuleiro) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

/**
 * Exibe o tabuleiro formatado no console
 * 
 * @param tabuleiro Ponteiro para a matriz do tabuleiro
 */
void exibir_tabuleiro(int** tabuleiro) {
    // Imprime o cabeçalho com números das colunas
    printf("  ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Imprime cada linha do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Número da linha
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 1) {
                printf("X "); // Navio
            } else {
                printf(". "); // Água
            }
        }
        printf("\n");
    }
}

/**
 * Valida se uma coordenada está dentro dos limites do tabuleiro
 * 
 * @param coord Coordenada a ser validada
 * @return 1 se válida, 0 se inválida
 */
int validar_coordenada(int coord) {
    return (coord >= 0 && coord < TAMANHO_TABULEIRO);
}

/**
 * Tenta posicionar um navio no tabuleiro após validar todas as condições
 * 
 * @param tabuleiro Ponteiro para a matriz do tabuleiro
 * @param inicio_linha Linha inicial do navio
 * @param inicio_coluna Coluna inicial do navio
 * @param orientacao 'H' para horizontal, 'V' para vertical
 * @return 1 se o navio foi posicionado com sucesso, 0 caso contrário
 */
int posicionar_navio(int** tabuleiro, int inicio_linha, int inicio_coluna, char orientacao) {
    // Valida coordenadas iniciais
    if (!validar_coordenada(inicio_linha) || !validar_coordenada(inicio_coluna)) {
        printf("Erro: Coordenadas iniciais (%d, %d) fora do tabuleiro!\n", 
               inicio_linha, inicio_coluna);
        return 0;
    }
    
    // Verifica se o navio cabe na posição e orientação escolhida
    if (orientacao == 'H') {
        if (inicio_coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio horizontal nao cabe a partir da coluna %d!\n", inicio_coluna);
            return 0;
        }
    } else if (orientacao == 'V') {
        if (inicio_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio vertical nao cabe a partir da linha %d!\n", inicio_linha);
            return 0;
        }
    } else {
        printf("Erro: Orientacao invalida! Use 'H' ou 'V'.\n");
        return 0;
    }
    
    // Verifica sobreposição com outros navios
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha, coluna;
        
        if (orientacao == 'H') {
            linha = inicio_linha;
            coluna = inicio_coluna + i;
        } else {
            linha = inicio_linha + i;
            coluna = inicio_coluna;
        }
        
        if (tabuleiro[linha][coluna] == 1) {
            printf("Erro: Sobreposicao com outro navio na posicao (%d, %d)!\n", 
                   linha, coluna);
            return 0;
        }
    }
    
    // Posiciona o navio no tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha, coluna;
        
        if (orientacao == 'H') {
            linha = inicio_linha;
            coluna = inicio_coluna + i;
        } else {
            linha = inicio_linha + i;
            coluna = inicio_coluna;
        }
        
        tabuleiro[linha][coluna] = 1;
    }
    
    return 1;
}

/**
 * Função principal que orquestra a criação do tabuleiro e posicionamento dos navios
 */
int main() {
    printf("=== BATALHA NAVAL ===\n");
    printf("Tabuleiro: %dx%d | Navios: %d (tamanho %d)\n\n", 
           TAMANHO_TABULEIRO, TAMANHO_TABULEIRO, NUM_NAVIOS, TAMANHO_NAVIO);
    
    // Cria o tabuleiro
    int** tabuleiro = criar_tabuleiro();
    
    if (tabuleiro == NULL) {
        printf("Erro: Falha ao alocar memoria para o tabuleiro!\n");
        return 1;
    }
    
    // Define os navios com coordenadas fixas (linha, coluna, orientação)
    struct {
        int linha;
        int coluna;
        char orientacao;
    } navios[NUM_NAVIOS] = {
        {2, 3, 'H'},  // Navio 1: horizontal começando em (2,3)
        {5, 7, 'V'},  // Navio 2: vertical começando em (5,7)
        {0, 0, 'H'}   // Navio 3: horizontal começando em (0,0)
    };
    
    // Posiciona cada navio
    int navios_posicionados = 0;
    
    for (int i = 0; i < NUM_NAVIOS; i++) {
        printf("Posicionando navio %d...\n", i + 1);
        printf("Coordenadas: (%d, %d) | Orientacao: %c\n", 
               navios[i].linha, navios[i].coluna, navios[i].orientacao);
        
        if (posicionar_navio(tabuleiro, navios[i].linha, navios[i].coluna, navios[i].orientacao)) {
            printf("Navio posicionado com sucesso!\n");
            navios_posicionados++;
        } else {
            printf("Falha ao posicionar navio!\n");
        }
        printf("\n");
    }
    
    // Exibe o tabuleiro final
    printf("=== TABULEIRO FINAL ===\n");
    printf("Navios posicionados: %d/%d\n\n", navios_posicionados, NUM_NAVIOS);
    exibir_tabuleiro(tabuleiro);
    
    // Legenda
    printf("\nLegenda: X = Navio | . = Agua\n");
    
    // Libera a memória alocada
    liberar_tabuleiro(tabuleiro);
    
    return 0;
}

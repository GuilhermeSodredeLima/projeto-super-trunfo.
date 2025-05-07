#include <stdio.h>
#include <string.h>

// Estrutura da carta
struct Carta {
    char nomePais[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
};

// Função auxiliar para exibir atributos
void exibirAtributo(int id, struct Carta c, float densidade) {
    switch (id) {
        case 1: printf("População: %d\n", c.populacao); break;
        case 2: printf("Área: %.2f km²\n", c.area); break;
        case 3: printf("PIB: %.2f bilhões\n", c.pib); break;
        case 4: printf("Pontos Turísticos: %d\n", c.pontosTuristicos); break;
        case 5: printf("Densidade Demográfica: %.2f hab/km²\n", densidade); break;
    }
}

// Função auxiliar para obter valor numérico do atributo
float valorAtributo(int id, struct Carta c, float densidade) {
    switch (id) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.pontosTuristicos;
        case 5: return densidade;
        default: return 0;
    }
}

// Nome do atributo
const char* nomeAtributo(int id) {
    switch (id) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

int main() {
    struct Carta c1, c2;
    float densidade1, densidade2;
    int escolha1, escolha2;

    // Entrada dos dados
    printf("Digite os dados da Carta 1:\n");
    printf("Nome do país: "); scanf(" %[^\n]", c1.nomePais);
    printf("População: "); scanf("%d", &c1.populacao);
    printf("Área: "); scanf("%f", &c1.area);
    printf("PIB (em bilhões): "); scanf("%f", &c1.pib);
    printf("Pontos Turísticos: "); scanf("%d", &c1.pontosTuristicos);

    printf("\nDigite os dados da Carta 2:\n");
    printf("Nome do país: "); scanf(" %[^\n]", c2.nomePais);
    printf("População: "); scanf("%d", &c2.populacao);
    printf("Área: "); scanf("%f", &c2.area);
    printf("PIB (em bilhões): "); scanf("%f", &c2.pib);
    printf("Pontos Turísticos: "); scanf("%d", &c2.pontosTuristicos);

    // Cálculo da densidade
    densidade1 = c1.populacao / c1.area;
    densidade2 = c2.populacao / c2.area;

    // Menu do primeiro atributo
    printf("\nEscolha o primeiro atributo para comparação:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade Demográfica\n> ");
    scanf("%d", &escolha1);

    // Validação básica
    if (escolha1 < 1 || escolha1 > 5) {
        printf("Opção inválida!\n");
        return 1;
    }

    // Menu do segundo atributo, dinâmico
    printf("\nEscolha o segundo atributo para comparação (diferente do primeiro):\n");
    for (int i = 1; i <= 5; i++) {
        if (i != escolha1) {
            printf("%d - %s\n", i, nomeAtributo(i));
        }
    }
    printf("> ");
    scanf("%d", &escolha2);

    // Validação
    if (escolha2 < 1 || escolha2 > 5 || escolha2 == escolha1) {
        printf("Opção inválida!\n");
        return 1;
    }

    // Comparações
    float v1_a1 = valorAtributo(escolha1, c1, densidade1);
    float v2_a1 = valorAtributo(escolha1, c2, densidade2);
    float v1_a2 = valorAtributo(escolha2, c1, densidade1);
    float v2_a2 = valorAtributo(escolha2, c2, densidade2);

    printf("\nComparando %s e %s com os atributos:\n", c1.nomePais, c2.nomePais);
    printf("- %s\n- %s\n\n", nomeAtributo(escolha1), nomeAtributo(escolha2));

    printf("%s:\n", c1.nomePais);
    exibirAtributo(escolha1, c1, densidade1);
    exibirAtributo(escolha2, c1, densidade1);

    printf("\n%s:\n", c2.nomePais);
    exibirAtributo(escolha1, c2, densidade2);
    exibirAtributo(escolha2, c2, densidade2);

    // Regras de vitória por atributo (Densidade Demográfica: menor vence)
    float pontosC1 = 0, pontosC2 = 0;

    if (escolha1 == 5) {
        pontosC1 += v1_a1 < v2_a1 ? 1 : (v1_a1 > v2_a1 ? 0 : 0.5);
        pontosC2 += v2_a1 < v1_a1 ? 1 : (v1_a1 > v2_a1 ? 0 : 0.5);
    } else {
        pontosC1 += v1_a1 > v2_a1 ? 1 : (v1_a1 < v2_a1 ? 0 : 0.5);
        pontosC2 += v2_a1 > v1_a1 ? 1 : (v1_a1 < v2_a1 ? 0 : 0.5);
    }

    if (escolha2 == 5) {
        pontosC1 += v1_a2 < v2_a2 ? 1 : (v1_a2 > v2_a2 ? 0 : 0.5);
        pontosC2 += v2_a2 < v1_a2 ? 1 : (v1_a2 > v2_a2 ? 0 : 0.5);
    } else {
        pontosC1 += v1_a2 > v2_a2 ? 1 : (v1_a2 < v2_a2 ? 0 : 0.5);
        pontosC2 += v2_a2 > v1_a2 ? 1 : (v1_a2 < v2_a2 ? 0 : 0.5);
    }

    float soma1 = v1_a1 + v1_a2;
    float soma2 = v2_a1 + v2_a2;

    printf("\nSoma dos valores dos atributos:\n");
    printf("%s: %.2f\n", c1.nomePais, soma1);
    printf("%s: %.2f\n", c2.nomePais, soma2);

    printf("\nResultado final:\n");
    if (soma1 > soma2) {
        printf("Vencedor: %s\n", c1.nomePais);
    } else if (soma2 > soma1) {
        printf("Vencedor: %s\n", c2.nomePais);
    } else {
        printf("Empate!\n");
    }

    return 0;
}
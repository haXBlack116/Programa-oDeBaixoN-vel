#include <stdio.h>
#include <stdlib.h>

struct Pixel {
    int R, G, B;
};

void gerarTonsDeCinza(struct Pixel **pixels, int coluna, int linha) {
    for (int j = 0; j < linha; j++) {
        for (int i = 0; i < coluna; i++) {
            int r = pixels[j][i].R;
            int g = pixels[j][i].G;
            int b = pixels[j][i].B;
            
            int tomCinza = (int)((r * 0.30) + (g * 0.59) + (b * 0.11));
            pixels[j][i].R = tomCinza;
            pixels[j][i].G = tomCinza;
            pixels[j][i].B = tomCinza;
        }
    }
}

void gerarTonsDeCinzaESaturado(struct Pixel **pixels, int coluna, int linha) {
    for (int j = 0; j < linha; j++) {
        for (int i = 0; i < coluna; i++) {
            int r = pixels[j][i].R;
            int g = pixels[j][i].G;
            int b = pixels[j][i].B;
            
            int tomCinza = (int)((r * 0.30) + (g * 0.59) + (b * 0.11));
            int tomCinzaSaturado = (int)(tomCinza * 1.3);
            if (tomCinzaSaturado > 255) {
                tomCinzaSaturado = 255;
            }
            pixels[j][i].R = tomCinzaSaturado;
            pixels[j][i].G = tomCinzaSaturado;
            pixels[j][i].B = tomCinzaSaturado;
        }
    }
}

void criarImagemNegativa(struct Pixel **pixels, int coluna, int linha) {
    for (int j = 0; j < linha; j++) {
        for (int i = 0; i < coluna; i++) {
            pixels[j][i].R = 255 - pixels[j][i].R;
            pixels[j][i].G = 255 - pixels[j][i].G;
            pixels[j][i].B = 255 - pixels[j][i].B;
        }
    }
}

void aumentarBrilho(struct Pixel **pixels, int coluna, int linha, int valor) {
    for (int j = 0; j < linha; j++) {
        for (int i = 0; i < coluna; i++) {
            pixels[j][i].R = pixels[j][i].R + valor;
            pixels[j][i].G = pixels[j][i].G + valor;
            pixels[j][i].B = pixels[j][i].B + valor;
            
            pixels[j][i].R = pixels[j][i].R > 255 ? 255 : pixels[j][i].R;
            pixels[j][i].G = pixels[j][i].G > 255 ? 255 : pixels[j][i].G;
            pixels[j][i].B = pixels[j][i].B > 255 ? 255 : pixels[j][i].B;
        }
    }
}

void diminuirBrilho(struct Pixel **pixels, int coluna, int linha, int valor) {
    for (int j = 0; j < linha; j++) {
        for (int i = 0; i < coluna; i++) {
            pixels[j][i].R = pixels[j][i].R - valor;
            pixels[j][i].G = pixels[j][i].G - valor;
            pixels[j][i].B = pixels[j][i].B - valor;
           
            pixels[j][i].R = pixels[j][i].R < 0 ? 0 : pixels[j][i].R;
            pixels[j][i].G = pixels[j][i].G < 0 ? 0 : pixels[j][i].G;
            pixels[j][i].B = pixels[j][i].B < 0 ? 0 : pixels[j][i].B;
        }
    }
}

void rotacionar90Graus(struct Pixel ***pixels, int *coluna, int *linha) {
    struct Pixel **novaMatriz = (struct Pixel **)malloc((*coluna) * sizeof(struct Pixel *));
    for (int i = 0; i < *coluna; i++) {
        novaMatriz[i] = (struct Pixel *)malloc((*linha) * sizeof(struct Pixel));
    }

    for (int j = 0; j < *linha; j++) {
        for (int i = 0; i < *coluna; i++) {
            novaMatriz[i][*linha - j - 1] = (*pixels)[j][i];
        }
    }

    for (int i = 0; i < *linha; i++) {
        free((*pixels)[i]);
    }
    free(*pixels);
    int temp = *coluna;
    *coluna = *linha;
    *linha = temp;
    *pixels = novaMatriz;
}

void envelhecerImagem(struct Pixel **pixels, int coluna, int linha) {
    for (int j = 0; j < linha; j++) {
        for (int i = 0; i < coluna; i++) {
            
            pixels[j][i].R = pixels[j][i].R * 0.7;
            pixels[j][i].G = pixels[j][i].G * 0.7;
            pixels[j][i].B = pixels[j][i].B * 0.7;
        }
    }
}

int main() {
    char nomeArquivo[100];
    FILE *fp, *fp_novo;
    int linhas, colunas, valor, r, g, b;

    printf("Digite o nome do arquivo PPM: ");
    scanf("%s", nomeArquivo);

    fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char tipoImg[3];
    fscanf(fp, "%s", tipoImg); 
    fscanf(fp, "%d %d", &colunas, &linhas); 
    fscanf(fp, "%d", &valor);

    struct Pixel **matriz = (struct Pixel **)malloc(linhas * sizeof(struct Pixel *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (struct Pixel *)malloc(colunas * sizeof(struct Pixel));
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(fp, "%d %d %d", &r, &g, &b);
            matriz[i][j].R = r;
            matriz[i][j].G = g;
            matriz[i][j].B = b;
        }
    }
    fclose(fp);

    int opcao;
    printf("Escolha uma opcao:\n");
    printf("1. Converter para tons de cinza\n");
    printf("2. Converter para tons de cinza e saturado\n");
    printf("3. Criar uma imagem negativa\n");
    printf("4. Aumentar o brilho\n");
    printf("5. Diminuir o brilho\n");
    printf("6. Rotacionar a imagem em 90 graus\n");
    printf("7. Envelhecer a imagem\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            gerarTonsDeCinza(matriz, colunas, linhas);
            break;
        case 2:
            gerarTonsDeCinzaESaturado(matriz, colunas, linhas);
            break;
        case 3:
            criarImagemNegativa(matriz, colunas, linhas);
            break;
        case 4:
            aumentarBrilho(matriz, colunas, linhas, 50); 
            break;
        case 5:
            diminuirBrilho(matriz, colunas, linhas, 50); 
            break;
        case 6:
            rotacionar90Graus(&matriz, &colunas, &linhas);
            break;
        case 7:
            envelhecerImagem(matriz, colunas, linhas);
            break;
        default:
            printf("Opcao invalida.\n");
            exit(1);
    }

    fp_novo = fopen("copia.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    fprintf(fp_novo, "P3\n");
    fprintf(fp_novo, "%d %d\n", colunas, linhas);
    fprintf(fp_novo, "%d\n", valor);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(fp_novo, "%d %d %d ", matriz[i][j].R, matriz[i][j].G, matriz[i][j].B);
        }
        fprintf(fp_novo, "\n");
    }
    fclose(fp_novo);

    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    printf("Copia do arquivo criada com sucesso.\n");
    return 0;
}

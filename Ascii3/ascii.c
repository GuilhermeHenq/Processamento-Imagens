/*=============================================================
2 * UNIFAL . . . . . . Universidade Federal de Alfenas.
3 * BACHARELADO EM CIENCIA DA COMPUTACAO.
4 * Trabalho . . . . . Imagem ASCII
5 * Discplina: . . . . Processamento de Imagens
6 * Professor: . . . . Luiz Eduardo da Silva
7 * Aluno . . . . . :  Guilherme Henrique Pereira Serafini
8 * Data . . . . . . : 28/04/2023
9 *=============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagelib.h"

int main(int argc, char *argv[])
{
    // Declaração de variáveis
    image In, Out;
    int nr, nc, ml;
    char *p, nameIn[100], nameOut[100], cmd[110];
    // Armazena os argumentos passados
    int numCols = atoi(argv[2]);
    int numRows = atoi(argv[3]);
    char *symbols = argv[4];
    int numSymbols = strlen(symbols);
    img_name(argv[1], nameIn, nameOut, GRAY);

    // Verifica se o número de argumentos passados está correto
    if (argc != 5 || argc < 4)
    {
        printf("\n \n ERROR!! \n");
        printf("Uso: <nome_arquivo_imagem> <ncolunas> <nlinhas> <string> \n \n \n ");
        return -1;
    }

    // Carrega a imagem de entrada
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);

    // Aloca memória para a imagem de saída
    Out = img_alloc(nr, nc);

    // Cria um arquivo para armazenar o resultado
    FILE *fpOut;
    fpOut = fopen("result.txt", "w");

    // Verifica se foi possível criar o arquivo
    if (!fpOut)
    {
        printf("Erro ao abrir o arquivo de saída.\n");
        exit(1);
    }

    // Calcula o tamanho de cada faixa de valores para mapear para cada caractere
    double range = 255 / (numSymbols);

    int redimensionadaL = nr / numRows;
    int redimensionadaC = nc / numCols;

    for (int i = 0; i < nc * nr; i++)
    {
        // Calcula o valor do caractere equivalente para o pixel atual
        int endchar = In[i] / range;
        if (endchar >= numSymbols)
            endchar = numSymbols - 1;
        Out[i] = symbols[endchar];
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            // Calcula o índice do pixel equivalente à posição atual na imagem de saída redimensionada
            int porcentagemL = (i * redimensionadaL);
            int porcentagemC = (j * redimensionadaC);
            int indice = (porcentagemL)*nc + (porcentagemC);

            // Escreve o caractere correspondente no arquivo de saída
            fputc(Out[indice], fpOut);
        }
        fputc('\n', fpOut);
    }

    // Fecha o arquivo de saída
    fclose(fpOut);

    img_put(Out, nameOut, nr, nc, ml, GRAY);

    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);

    img_free(In);
    img_free(Out);

    return 0;
}

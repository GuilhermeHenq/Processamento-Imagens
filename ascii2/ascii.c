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
    image In, Out;
    int nr, nc, ml;
    char *p, nameIn[100], nameOut[100], cmd[110];
    int numCols = atoi(argv[2]);
    int numRows = atoi(argv[3]);
    char symbols[30];
    strcpy(symbols, argv[4]);
    int numSymbols = strlen(symbols);
    img_name(argv[1], nameIn, nameOut, GRAY);
    double teste;

    In = img_get(nameIn, &nr, &nc, &ml, GRAY);
    Out = img_alloc(nr, nc);
    FILE *fpOut;
    fpOut = fopen("result.txt", "w");

    if (!fpOut)
    {
        printf("Erro ao abrir o arquivo de saída.\n");
        exit(1);
    }


    double range = 255 / (numSymbols);
    int redimensionadaL = nr / numRows;
    int redimensionadaC = nc / numCols;

    for (int i = 0; i < nc * nr; i++)
    {
        int endchar = In[i] / range;
        if (endchar >= numSymbols)
            endchar = numSymbols - 1;
        Out[i] = symbols[endchar];
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            int porcentagemL = (i*redimensionadaL);
            int porcentagemC = (j*redimensionadaC);
            int indice = (porcentagemL) * nc + (porcentagemC);
            fputc(Out[indice], fpOut);
        }
        fputc('\n', fpOut);
    }
    fclose(fpOut);
    img_put(Out, nameOut, nr, nc, ml, GRAY);
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);

    return 0;
}

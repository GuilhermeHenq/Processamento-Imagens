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


void ascii(image In, char* nameOut, int numCols, int numRows, char* symbols, int numSymbols) {
   int i, j, k, idx;
   double teste;
   FILE* fpOut = fopen(nameOut, "w");


   if (!fpOut) {
       printf("Erro ao abrir o arquivo de saída.\n");
       exit(1);
   }


   double range = 255.0 / (numSymbols - 1);


   for (i = 0; i < numRows; i++) {
       for (j = 0; j < numCols; j++) {
           teste = In[i*numCols + j];


           idx = (int) (teste / range);
           if (idx >= numSymbols) idx = numSymbols - 1;


           for (k = 0; k < strlen(symbols); k++) {
               if (k == idx) {
                   fputc(symbols[k], fpOut);
                   break;
               }
           }
       }
       fputc('\n', fpOut);
   }
   fclose(fpOut);
}


int main(int argc, char *argv[]) {
   image In;
   int nr, nc, ml;
   char *nameIn = argv[1];
   char *nameOut = "Saida.txt";
   int numCols = atoi(argv[2]);
   int numRows = atoi(argv[3]);
   char *symbols = argv[4];
   int numSymbols = strlen(symbols);


   In = img_get(nameIn, &nr, &nc, &ml, GRAY);
// In = img_resample(In, nr, nc, numRows, numCols);
   ascii(In, nameOut, numCols, numRows, symbols, numSymbols);
   img_free(In);


   return 0;
}



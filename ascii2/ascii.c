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


/*void ascii(image In, char* nameOut, int numCols, int numRows, char* symbols, int numSymbols) {
   int i, j, k, idx;
   double teste;
   FILE* fpOut = fopen(nameOut, "w");


   if (!fpOut) {
       printf("Erro ao abrir o arquivo de saída.\n");
       exit(1);
   }


   double range = 255.0 / (numSymbols - 1);
    int linha = nr / numRows;
    int coluna = nc / numCols;

   for (i = 0; i < numRows; i++) {
       for (j = 0; j < numCols; j++) {
           teste = In[(i*numRows)*numCols + (j*numCols)];


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
*/


int main(int argc, char *argv[]) {
   image In, Out;
   int nr, nc, ml;
   char *nameIn = argv[1];
   char *nameOut = "Saida.txt";
   int numCols = atoi(argv[2]);
   int numRows = atoi(argv[3]);
   char *symbols = argv[4];
   int numSymbols = strlen(symbols);

    int i, j, k, idx;
    double teste;
    FILE* fpOut;
   fpOut = fopen("saida.txt", "w");


   if (!fpOut) {
       printf("Erro ao abrir o arquivo de saída.\n");
       exit(1);
   }


   double range = 256 / (numSymbols);
    int linha = nr / numRows;
    int coluna = nc / numCols;

    //idx = (int) (teste / range);

    for(int i = 0; i < nc * nr; i++) {
        int aux = In[i] / range;
        if(aux >= numSymbols)
            aux = numSymbols -1;
        Out[i] = symbols[aux];
    }

   for (i = 0; i < numRows; i++) {
       for (j = 0; j < numCols; j++) {
           //teste = In[(i*linha) * nc + (j*coluna)];
           fprintf(fpOut,"%c", Out[(i*linha) * nc + (j*coluna)]);
        }
       fputc('\n', fpOut);
   
   fclose(fpOut);
    }

    img_free(fpOut);


   In = img_get(nameIn, &nr, &nc, &ml, GRAY);
   //In = img_resample(In, nr, nc, numRows, numCols);
   //ascii(In, nameOut, numCols, numRows, symbols, numSymbols);
   img_free(In);


   return 0;
}



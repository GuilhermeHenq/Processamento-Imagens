/*=============================================================
2 * UNIFAL Universidade Federal de Alfenas.
3 * BACHARELADO EM CIENCIA DA COMPUTACAO.
4 * Trabalho Imagem ASCII
5 * Discplina: Processamento de Imagens
6 * Professor: Luiz Eduardo da Silva
7 * Aluno: Guilherme Henrique Pereira Serafini
8 * Data: 28/04/2023
9 *=============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagelib.h"

// Assinatura da função arteAscii
void arteAscii(char *nomeImagem, int numCols, int numRows, char *symbols);

//////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    // Armazena os argumentos passados
    char *nomeImagem = argv[1];
    int numCols = atoi(argv[2]);
    int numRows = atoi(argv[3]);
    char *symbols = argv[4];

    // Verifica se o número de argumentos passados está correto
    if (argc != 5 || argc < 4)
    {
        printf("\n \n ERROR!! \n");
        printf("Uso: <nome_arquivo_imagem> <ncolunas> <nlinhas> <string> \n \n \n ");
        return -1;
    }

    // Chama a função arteAscii passando os argumentos necessários
    arteAscii(nomeImagem, numCols, numRows, symbols);

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void arteAscii(char *imgName, int numCols, int numRows, char *symbols)
{
    // Declaração de variáveis
    image In, Out;
    int nr, nc, ml;
    char nameIn[100], nameOut[100], cmd[110];

    // Armazena o número de caracteres disponíveis
    int numSymbols = strlen(symbols);

    // Cria os nomes dos arquivos de entrada e saída
    img_name(imgName, nameIn, nameOut, GRAY);

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

    int linhaRedimensionada = nr / numRows;
    int colunaRedimensionada = nc / numCols;

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
            int porcentagemL = (i * linhaRedimensionada);
            int porcentagemC = (j * colunaRedimensionada);
            int indice = (porcentagemL)*nc + (porcentagemC); // seria igual a (i * nc + j)

            // Escreve o caractere correspondente no arquivo de saída
            fputc(Out[indice], fpOut);
        }
        // pula a linha para escrever a próxima
        fputc('\n', fpOut);
    }

    // Fecha o arquivo de saída, salva a imagem na saida, e libera as memorias alocadas
    fclose(fpOut);
    img_put(Out, nameOut, nr, nc, ml, GRAY);
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
}



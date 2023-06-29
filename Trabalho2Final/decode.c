/*---------------------------------------------------------
 * Image Processing
 * 
 * Steganography - decode
 *---------------------------------------------------------*/
 /*=============================================================
 * UNIFAL = Universidade Federal de Alfenas 
* BACHARELADO EM CIENCIA DA COMPUTACAO.
* Trabalho: Esteganografia
* Disciplina: Processamento de Imagens
* Professor: Luiz Eduardo da Silva
* Aluno: Guilherme Henrique Pereira Serafini
* Data: 27/06/2023
*=============================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#define DEBUG(x) x

//função para pegar o ultimo bit seguindo a ordem R G B, e montar um byte com isso
int transform(int x, int y){
     int regularRgb = y;
     int color = x;
     unsigned char tamanho;
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;

        switch (regularRgb)
        {
        case 0:
            tamanho = (tamanho << 1) | (r & 0x1);
            break;
        case 1:
            tamanho = (tamanho << 1) | (g & 0x1);
            break;
        case 2:
            tamanho = (tamanho << 1) | (b & 0x1);
            break;
        }
        return tamanho;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
void decode(image In)
{
    FILE *file;
    char name[100]={""};
    int fsize;
    unsigned char byte;
    int i = 0;
    int regularRgb = 0;


    // decode the name
    do
    {   
        // compara se tem 8 bits e o i é maior que 0
        if (i % 8 == 0 && i > 0){
            char aux[100];
            sprintf(aux, "%c", byte);
            strcat(name, aux);
            byte = 0;
        }

        // verifica se a variavel que é responsavel por rodar o R G B, é 3, se for ele atribui 0
        regularRgb == 3 ? regularRgb = 0: regularRgb;

        // pega o pixel daquele byte e passa para a funcao transform, guardando o seu resultado na variavel byte
        int color = In->px[i];
        int resultado = transform(color, regularRgb);
        byte = (byte << 1) | (resultado);

        // itera os valores de i e regularRgb
        i++;
        regularRgb++;

    } while (byte != 0 ||(i % 8 != 0));
    // criterio de parada do laço de repetição
    
    printf("File name: %s\n", name);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    // decode file size
    
    // cria uma variavel unsigned para guardar o tamanho, ela possui 32 bits
    unsigned int tamanho = 0;

    // roda 4 bytes, ou seja 32 bits para descobrir o tamanho
    for (int bits = 0; bits < 32; bits++) {
        
        regularRgb == 3 ? regularRgb = 0: regularRgb;
        
        int color = In->px[i];
        int resultado = transform(color, regularRgb);
        tamanho = (tamanho << 1) | (resultado);
        
        i++;
        regularRgb++;
    }
    fsize = tamanho;
    printf("File size: %d bytes\n", fsize);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    // decode file
    
    file = fopen(name, "wb");
    if (!file)
    {
        printf("Cannot create file %s\n", name);
        exit(10);
    }
    while (fsize)
    {
        // um for para rodar 8 bits, e armazenando na variavel byte
        for (int j = 0; j < 8; j++){
          
            regularRgb == 3 ? regularRgb = 0: regularRgb;

            int color = In->px[i];
            int resultado = transform(color, regularRgb);
            byte = (byte << 1) | (resultado);
            i++;
            regularRgb++;

        }
        // escreve no arquivo o conteudo encontrado
        // variavel, tamanho da variavel, quantidade a ser escrita, e arquivo a ser escrito
        fwrite(&byte, sizeof(byte), 1, file);
        byte = 0;
        fsize--;
    }
    fclose(file);
}

void msg(char *s)
{
    printf("\nSteganography - decode");
    printf("\n-------------------------------");
    printf("\nUSE.:  %s  <IMG.PPM>", s);
    printf("\nWhere:\n");
    printf("    <IMG.PPM>  Image file in PPM ASCII format\n\n");
    exit(20);
}

/*-----------------------------------------
  Main program
------------------------------------------*/
int main(int argc, char *argv[])
{
    char name[100];
    image In;
    char *p;
    if (argc < 2)
        msg(argv[0]);
    strcpy(name, argv[1]);
    p = strstr(name, ".ppm");
    if (p)
        *p = 0;
    strcat(name, ".ppm");
    In = img_get(name, COLOR);
    decode(In);
    img_free(In);
    return 0;
}

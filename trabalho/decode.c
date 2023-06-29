/*---------------------------------------------------------
 * Image Processing
 * 
 * Steganography - decode
 *---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#define DEBUG(x) x


void decode(image In)
{
    FILE *file;
    char name[100]={""};
    int fsize;
    unsigned char byte;
    int i = 0;
    int regularRgb = 0;

    do
    {
        if (regularRgb == 3){
            regularRgb = 0;
        }
        if (i % 8 == 0 && i > 0){
            char aux[100];
            sprintf(aux, "%c", byte);
            strcat(name, aux);
            byte = 0;
        }

        int color = In->px[i];
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;

        switch (regularRgb)
        {
        case 0:
            byte = (byte << 1) | (r & 0x1);
            break;
        case 1:
            byte = (byte << 1) | (g & 0x1);
            break;
        case 2:
            byte = (byte << 1) | (b & 0x1);
            break;
        }
        /*
        if(i % 3 == 0){
            byte = (byte << 1) | (r & 0x1);
        }
        else if(i % 3 == 1){
            byte = (byte << 1) | (g & 0x1);
        }
        else{
            byte = (byte << 1) | (b & 0x1);
        }*/

        i++;
        //printf("%d\n", regularRgb);
        regularRgb++;

    } while (byte != 0 ||(i % 8 != 0));
    // decode the name
    
    printf("File name: %s\n", name);
    // decode file size
    unsigned int tamanho = 0;
    //i = i + 1;

    for (int bits = 0; bits < 32; bits++) {
        
        if (regularRgb == 3){
            regularRgb = 0;
        }
        int color = In->px[i];
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
        
        i++;
        regularRgb++;
    }
    fsize = tamanho;
    printf("File size: %d bytes\n", fsize);
    
    // decode file
    
    file = fopen(name, "wb");
    if (!file)
    {
        printf("Cannot create file %s\n", name);
        exit(10);
    }
    while (fsize)
    {
        for (int j = 0; j < 8; j++){
            // if (regularRgb == 3){
            //     regularRgb = 0;
            // }

            regularRgb == 3 ? regularRgb = 0: regularRgb;

            int color = In->px[i];
            int r = (color >> 16) & 0xFF;
            int g = (color >> 8) & 0xFF;
            int b = color & 0xFF;

            switch (regularRgb)
            {
            case 0:
                byte = (byte << 1) | (r & 0x1);
                break;
            case 1:
                byte = (byte << 1) | (g & 0x1);
                break;
            case 2:
                byte = (byte << 1) | (b & 0x1);
                break;
            }
            i++;
            regularRgb++;

        }
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

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void Decifra(byte *bloco, char *chave, int itens)
{
    int i;
    byte auxByte;

    for(i=0; i<itens; i++)
    {
        if (i%2 == 0) {
            auxByte = bloco[i] - (chave[i] << 1);
            bloco[i] = auxByte << 1;
        } else {
            auxByte = bloco[i] - (chave[i] >> 1);
            bloco[i] = auxByte >> 1;
        }
    }
}



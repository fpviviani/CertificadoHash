/**********************************************
*  Para compilar gcc Remetente.c -o remetente *
*  Para executar ./remetente                  *
**********************************************/


#include <stdio.h>
#include <stdlib.h>
#include "sha256.c"

#define TAM 100
#define ENTRADA "entrada.txt"
#define SAIDA "saida.txt"
#define CHAVE "5370290329110820473548221392439453702903291108204735482213924394"

typedef unsigned char byte;

void Cifra(byte *bloco, char *chave, int itens)
{
    int i;
    for (i = 0; i < itens; i++)
    {
        if (i%2 == 0) {
            bloco[i] = (bloco[i] >> 1) + (chave[i] << 1);
        } else {
            bloco[i] = (bloco[i] << 1) + (chave[i] >> 1);
        }
    }
}

void Hash(char *chave, char *ChaveHash)
{
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, chave, strlen(chave));
    sha256_final(&ctx, ChaveHash);
}

int main()
{
    char BlocoDados[TAM], HashFinalizada[65];
    unsigned char HashKey[32];
    FILE *ArquivoEntrada, *ArquivoSaida, *ArquivoHash;
    int Itens;

    ArquivoEntrada = fopen(ENTRADA,"rb");
    do {
        Itens = fread(BlocoDados, 1, TAM, ArquivoEntrada);
        if (Itens != 0) {
            Hash(BlocoDados, HashKey);

            ArquivoHash = fopen("hash.txt","wb");
            for (int i = 0; i < 32; i++) {
                fprintf(ArquivoHash, "%02x", HashKey[i]);
            }
            fclose(ArquivoHash);

            ArquivoHash = fopen("hash.txt","rb");
            fgets(HashFinalizada, sizeof(HashFinalizada), ArquivoHash);
            fclose(ArquivoHash);
            remove("hash.txt");

            Cifra(HashFinalizada, CHAVE, strlen(HashFinalizada));
        }
    } while(!feof(ArquivoEntrada));
    fclose(ArquivoEntrada);

    ArquivoSaida = fopen(SAIDA,"wb");
    fprintf(ArquivoSaida, "%s\t%s", BlocoDados, HashFinalizada);
    fclose(ArquivoSaida);

    return 0;
}

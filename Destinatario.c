/****************************************************
*  Para compilar gcc Destinatario.c -o destinatario *
*  Para executar ./destinatario                     *
****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "sha256.c"

#define TAM 100
#define TAM_HASH 132
#define ENTRADA "saida.txt"
#define CHAVE "5370290329110820473548221392439453702903291108204735482213924394"

typedef unsigned char byte;

void Decifra(byte *bloco, char *chave, int itens)
{
    int i;
    byte auxByte;

    for (i = 0; i < itens; i++)
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

void Hash(char *chave, char *ChaveHash)
{
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, chave, strlen(chave));
    sha256_final(&ctx, ChaveHash);
}

int main()
{
    char BlocoDados[TAM], Mensagem[TAM], Cifra[TAM], HashFinalizada[65];
    unsigned char HashKey[32];
    FILE *ArquivoEntrada, *ArquivoHash;
    int Itens;

    ArquivoEntrada = fopen(ENTRADA,"rb");
    do {
        Itens = fread(BlocoDados, 1, TAM_HASH, ArquivoEntrada);
        if (Itens != 0) {
            char *token = strtok(BlocoDados, "\t");
            strcpy(Mensagem, token);
            token = strtok(NULL, "\t");
            strcpy(Cifra, token);

            Hash(Mensagem, HashKey);

            ArquivoHash = fopen("hash.txt","wb");
            for (int i = 0; i < 32; i++) {
                fprintf(ArquivoHash, "%02x", HashKey[i]);
            }
            fclose(ArquivoHash);

            ArquivoHash = fopen("hash.txt","rb");
            fgets(HashFinalizada, sizeof(HashFinalizada), ArquivoHash);
            fclose(ArquivoHash);
            remove("hash.txt");

            Decifra(Cifra, CHAVE, strlen(Cifra));
        }
    } while(!feof(ArquivoEntrada));
    fclose(ArquivoEntrada);

    if (strcmp(Cifra, HashFinalizada) == 0) {
        printf("A mensagem foi autenticada");
    } else {
        printf("Não foi possível autenticar a mensagem.");
    }

    return 0;
}

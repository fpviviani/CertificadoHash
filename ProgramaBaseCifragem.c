/********************************************************
*  Para compilar gcc ProgramaBaseCifragem.c -o cifragem *
*  Para executar ./cifragem                             *
********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "ProgramaBaseDecifragem.c"
#include "sha256.c"

#define TAM 9

typedef unsigned char byte;

void Cifra(byte *bloco, char *chave, int itens)
{
    int i;
    for(i=0; i<itens; i++)
    {
        if (i%2 == 0)
            bloco[i] = (bloco[i] >> 1) + (chave[i] << 1);
        else
            bloco[i] = (bloco[i] << 1) + (chave[i] >> 1);
    }
}

void Hash(char *chave, char *ChaveHash)
{
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, chave, strlen(chave));
    sha256_final(&ctx, ChaveHash);
    printf("%s", ChaveHash);
}

int main()
{
    char BlocoDados[TAM], ChaveCifragem[TAM], HashKey[32];
    FILE *ArquivoEntrada, *ArquivoSaida;
    char NomeArquivoEntrada[30], NomeArquivoSaida[30];
    int  Itens;

    printf("Entre com o Nome do Arquivo Original = ");
    scanf("%s", NomeArquivoEntrada);
    printf("Entre com o Nome do Arquivo para Cifragem = ");
    scanf("%s", NomeArquivoSaida);
    printf("Entre com uma senha de 8 digitos = ");
    scanf("%s", ChaveCifragem);

    ArquivoEntrada = fopen(NomeArquivoEntrada,"rb");
    ArquivoSaida = fopen(NomeArquivoSaida,"wb");
    do
    {
        Itens = fread(BlocoDados, 1, TAM, ArquivoEntrada);
        if(Itens!=0)
        {
            Cifra(BlocoDados, ChaveCifragem, Itens);
            Hash(ChaveCifragem, HashKey);
            Decifra(BlocoDados, ChaveCifragem, Itens);
            fwrite(BlocoDados, Itens, 1, ArquivoSaida);
        }
    } while(!feof(ArquivoEntrada));

    fclose(ArquivoSaida);
    fclose(ArquivoEntrada);

    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

///O USUÁRIO PRECISA ENTRAR COM AS REGRAS NA FORMA q0,a=q1,X,R UMA POR LINHA;

//Funções

int compare (const void * a, const void * b)
{
  if ( *(char*)a <  *(char*)b ) return -1;
  if ( *(char*)a == *(char*)b ) return 0;
  if ( *(char*)a >  *(char*)b ) return 1;
}

int main(){
    FILE* entrada;
    entrada = fopen("regras.txt","r");
    if(entrada==NULL){printf("Erro na abertura do arquivo\n"); exit(1);}

    //Entrada
    char cadeia[50];
    int tam;
    char estadoAtu, estadoFin;
    char vet[50];
    //Manipulação
    char regra[12]; //q0,a=q1,X,R
    char atual;
    int i;
    int linha;
    char estadoRegra, estadoRequisito, escrita, leitura;
    int movimento;
    int RECONHECIDA = 0;

    linha =0;
    while(fscanf(entrada,"%s",regra)==1){ //Lê o arquivo e salva todos os estados em um vetor
        vet[linha] = regra[1];
        linha++;
        vet[linha] = regra[6];
        linha++;
    }
    rewind(entrada); //Volta pro começo do arquivo
    qsort(vet,linha,sizeof(char),compare); //Ordena o vetor de estados
    estadoAtu = vet[0]; //Pega o estado inicial
    estadoFin = vet[linha-1]; //Pega o estado final

    i=0;

    printf("Digite a cadeia: ");
    scanf("%s",cadeia);
    tam = strlen(cadeia);
    cadeia[tam] = 'F'; //Isso representa o caractere "branco"
    tam++;
    cadeia[tam] = '\0';

    while(fscanf(entrada,"%s",regra)==1){

        //printf(regra);
        //printf("\n");

        atual = cadeia[i];
        estadoRequisito = regra[1];
        leitura = regra[3];
        estadoRegra = regra[6];
        escrita = regra[8];
        if(regra[10]=='R') movimento=1; else movimento= -1;
        //printf("Atual = %c Estado requisito = %c Leitura = %c Estado regra = %c Escrita = %c Movimento = %d\n",atual,estadoRequisito,leitura,estadoRegra,escrita,movimento);

        if(estadoAtu==estadoRequisito){
            if(atual==leitura){
                estadoAtu = estadoRegra; //Muda de estado
                cadeia[i] = escrita; //Escreve na fita
                i = i + movimento; //Anda com o braço
                rewind(entrada); //Volta pro começo do arquivo
                //printf("DEPOIS DA REGRA: Estado Atual = %c Atual alterado = %c i = %d\n",estadoAtu,cadeia[i-movimento],i);
            }
        }

        if(estadoAtu==estadoFin){ //Antes era (estadoAtu==estadoFin && cadeia[i-1]=='F')
            RECONHECIDA = 1;
            break;
        }

    }

    if(RECONHECIDA)
        printf("CADEIA ACEITA!\n");
    else
        printf("MAQUINA PAROU!\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


//Funções Basicas
int AND(int a, int b); //Função AND

int OR(int a, int b); //Função OR

int XOR(int a, int b); //Função OR_EXCLUSIVO

int NOT(int a); //Função NOT

int NOTAND(int a, int b); //Função NOT_AND

int NOTOR(int a, int b); //Função NOT_OR
//

//Operações
void somador_parcial(int a, int b, int *sum, int *carry);
int* somador_total(int *A, int *B, int n);
int* vetor_A(int a,int n);
int* vetor_B(int b,int n);
//

int main()
{
    int a ,b , n=4, i, cont=0,escolha;
    int soma=0,carry=0;
    int vetNulo[] = {0,0,0,0};
    int *A = vetNulo;
    int *B = vetNulo;
    int *result;


while (escolha != 0)
   {
    printf("SIMULADOR DE OPERACOES DA UNIDADE LOGICA E ARITMETICA\n\n");
    printf("*******************************************************************\n\n");
    printf("Selecione a operacao desejada:\n\n");
    printf("1 - Somador Parcial\n");
    printf("2 - Somador Total\n");
    printf("0 - Encerrar programa\n");
    printf("Escolha: ");
    scanf("%d",&escolha);

    if(escolha==1)
    {   printf("Digite a e b(em binario): ");
        scanf("%d %d",&a,&b);

        A = vetor_A(a,n);
        B = vetor_B(b,n);

        somador_parcial(a,b,&soma,&carry);

        printf("Primeira passo: XOR de %d e %d que produz: %d\n",a,b,soma);
        printf("Segundo passo: AND de %d com %d que produz: %d\n",a,b,carry);


        printf("\nResultado: %d%d",carry,soma);
        getch();

    }
    else if(escolha==2)
    {   printf("Digite a e b(em binario): ");
        scanf("%d %d",&a,&b);

        A = vetor_A(a,n);
        B = vetor_B(b,n);
        printf("\na = %d%d%d%d  b = %d%d%d%d\n",A[0],A[1],A[2],A[3],B[0],B[1],B[2],B[3]);

        result = somador_total(A,B,n);
        printf("\nResultado: ");
        for(i=0;i<n;i++)
        {
            printf("%d",result[i]);
        }
        getch();
    }
    system("cls");
    }


printf("\n");
system("PAUSE");

return 0;
}


void somador_parcial(int a, int b, int *sum,int *carry)
{

*sum = XOR(a, b); //SOMA
*carry = AND(a, b); //CARRY

}

int* somador_total(int *A, int *B,int n)
{
   int Cin=0,Cout=0,S,i,C=0,S1,cont=1;;
   int *result;

   result = (int*) malloc(n*sizeof(int));
   if(result==NULL){printf("Erro de alocacao");exit(1);}

   for(i=(n-1);i>=0;i--)
   {
       somador_parcial(A[i],B[i],&S1,&Cin);

       printf("\n-Primeiro passo[%d]-\n",cont);
       printf("Soma parcial do bit[%d] de a: %d com bit[%d] de b: %d\n",i+1,A[i],i+1,B[i]);
       printf("Gerando uma Sum: %d e um VaiUm: %d\n",S1,Cin);
       getch();

       somador_parcial(C,S1,&S,&Cout);
       printf("\n-Segundo passo[%d]-\n",cont);
       printf("Soma parcial do VaiUm anterior: %d com o Sum anterior: %d\n",Cin,S1);
       printf("Gerando uma nova Sum: %d e um novo VaiUm: %d\n",S,Cout);
       getch();

       result[i] = S;

       C = OR(Cout,Cin);
       printf("\n-Terceiro passo[%d]-\n",cont);
       printf("OR com VaiUm anterior: %d e VaiUm do primeiro passo: %d\n",Cout,Cin);
       printf("Gerando o VaiUm final do ciclo: %d\n",C);
       getch();

       cont++;
   }

   return result;
   free(result);

}

int AND(int a, int b)
{
    return a & b ;
}

int OR(int a, int b)
{
    return a | b;
}

int XOR(int a, int b)
{
    return a ^ b;
}

int NOT(int a)
{
    return ~a;
}

int NOTAND(int a, int b)
{
    return ~(a & b);
}

int NOTOR(int a, int b)
{
    return ~(a | b);
}

//TRANSFORMANDO EM VETOR
int* vetor_A(int a,int n)
{
   int i;

   int * vet = (int *) malloc (n*sizeof(int));
   if(vet==NULL){printf("Erro de alocacao");exit(1);}

        while(a>0)
        {   vet[n-1] = (a % 10);
            a = a/10;
            n--;
        }

    n=4;

    for(i=0;i<n;i++)
    {
        if(vet[i]!= 0 && vet[i]!= 1)
            vet[i] = 0;
    }

    return vet;
    free(vet);

}

int* vetor_B(int b,int n)
{
   int i;

   int * vet = (int *) malloc (n*sizeof(int));
   if(vet==NULL){printf("Erro de alocacao");exit(1);}

        while(b>0)
        {   vet[n-1] = (b % 10);
            b = b/10;
            n--;
        }

    n=4;

    for(i=0;i<n;i++)
    {
        if(vet[i]!= 0 && vet[i]!= 1)
            vet[i] = 0;
    }

    return vet;
    free(vet);

}



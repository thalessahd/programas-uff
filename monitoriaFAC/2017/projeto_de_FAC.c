#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

/* Anotações
   -VERIFICAÇÃO IMPLEMENTADA MAS NÃO 100%
   -MELHORAR A IMPRESSÃO DO RESULTADO FINAL DE ACORDO COM A NECESSIDADE
   -FALTAM ADD, SUB E MUL DE BINÁRIOS
*/


///PROTÓTIPO DE FUNÇÕES
int paraBin(int x); //TRANSFORMA UM NUMERO DECIMAL PARA BINARIO
int paraBinLetra(int x); //TRANSFORMA UM NUMERO DECIMAL E LETRAS HEX PARA BINARIO
int paraDecLetra(int x); //TRANSFORMA UM NUMERO DECIMAL E LETRAS HEX PARA DECIMAL
int BinParaOct(int x); //TRANSFORMA UM NUMERO BINÁRIO PARA OCTAL
int BinParaHex(int x, int* controleRef); //TRANSFORMA UM NUMERO BINÁRIO PARA HEXADECIMAL
int potencia(int x, int y); //REALIZA X^Y
void pause (float); //FUNÇÃO TEMPORALIZADORA
int StrBinParaNum(char str[4]); //TRANSFORMA STRING BINARIA PARA NUMERO INT
int Validar(char string[100],char base); //VALIDA UMA STRING DE ACORDO COM A BASE
char decimalToLetra(int x); //TRANSFORMA DECIMAL EM LETRA

///VARIAVEIS GLOBAIS
    char num[100]; //DADO DE ENTRADA
    char binario[100]; //DADO DE SAÍDA
    int vetorRestos[100]; //DADO DE SAÍDA
    int CorDestaque=14, CorNormal=15, CorResto=12; //CORES
    char auxOct[4], auxHex[5];
    char auxBinOct[4], auxBinHex[5];

///FUNÇÕES DE ENTRADA
int EntradaOct(int op){
    system("cls");
    if(op==1)
        printf("OCTAL -> BINÁRIO\n");
    if(op==2)
        printf("OCTAL -> DECIMAL\n");
    printf("Digite o número: "); //ENTRADA DO DADO (STRING)
    scanf("%s",num);

    if(Validar(num,'8')){ //VALIDAÇÃO
        system("cls");
        printf("Iniciando conversão...");
        pause(1.5);
        system("cls");
        return 1;
    }
    return 0;
}

int EntradaHex(int op){
    system("cls");
    if(op==1)
        printf("HEXADECIMAL -> BINÁRIO\n");
    if(op==2)
        printf("HEXADECIMAL -> DECIMAL\n");
    printf("Digite o número: ");
    scanf("%s",num);

    if(Validar(num,'G')){
        system("cls");
        printf("Iniciando conversão...");
        pause(1.5);
        system("cls");
        return 1;
    }
    return 0;
}

int EntradaBin(int op){
    int end;
    system("cls");
    if(op==1)
        printf("BINÁRIO -> OCTAL\n");
    if(op==2)
        printf("BINÁRIO -> HEXADECIMAL\n");
    if(op==3)
        printf("BINÁRIO -> DECIMAL\n");
    printf("Digite o número: ");
    scanf("%s",num);
    end = strlen(num); //Salva tamanho da string
    num[end+1] = '\0'; //Só para não ter lixos

    if(Validar(num,'2')){
        system("cls");
        printf("Iniciando conversão...");
        pause(1.5);
        system("cls");
        return 1;
    }
    return 0;
}

int EntradaDec(int op){
    int end;
    system("cls");
    if(op==1)
        printf("DECIMAL -> BINÁRIO\n");
    if(op==2)
        printf("DECIMAL -> OCTAL\n");
    if(op==3)
        printf("DECIMAL -> HEXADECIMAL\n");
    printf("Digite o número: ");
    scanf("%s",num);
    end = strlen(num); //Salva tamanho da string
    num[end+1] = '\0'; //Só para não ter lixos

    if(Validar(num,':')){ //Quanto fizer base = base -1 ; base = 9
        system("cls");
        printf("Iniciando conversão...");
        pause(1.5);
        system("cls");
        return 1;
    }
    return 0;
}

int Validar(char string[100], char base){
    int tam = strlen(string);
    int i;
    int resp = 1;

    base = base -1;

    for(i=0;i<tam;i++){
        if(string[i]>base || string[i]<0)
            resp = 0;
    }
    return resp;
}

///FUNÇÕES DE IFs
void IfsEscritaDestacadaOct2Bin(int numInt, int* j, int bin){
    if(numInt<2){
        *j=*j+3;
        gotoxy(*j,1);
        printf("00");
        strcat(binario,"00");
        printf("%d",bin);
        itoa(bin,auxOct,10);
        strcat(binario,auxOct);
    }
    else if(numInt>=2 && numInt<4){
        *j = *j+3;
        gotoxy(*j,1);
        printf("0");
        strcat(binario,"0");
        printf("%d",bin);
        itoa(bin,auxOct,10);
        strcat(binario,auxOct);
    }
    else if(numInt>=4){
        *j = *j+3;
        gotoxy(*j,1);
        printf("%d",bin);
        itoa(bin,auxOct,10);
        strcat(binario,auxOct);
    }
}

void IfsEscritaCorretaOct2Bin(int numInt, int* k, int bin){
    if(numInt<2){
        *k=*k+3;
        gotoxy(*k,1);
        printf("00");
        printf("%d",bin);
    }
    else if(numInt>=2 && numInt<4){
        *k = *k+3;
        gotoxy(*k,1);
        printf("0");
        printf("%d",bin);
    }
    else if(numInt>=4){
        *k = *k+3;
        gotoxy(*k,1);
        printf("%d",bin);
    }
}

void IfsEscritaDestacadaHex2Bin(int numInt, int* j, int bin){
    if(numInt<2){
        *j=*j+4;
        gotoxy(*j,1);
        printf("000");
        strcat(binario,"000");
        printf("%d",bin);
        itoa(bin,auxOct,10);
        strcat(binario,auxOct);
    }
    else if(numInt>=2 && numInt<4){
        *j = *j+4;
        gotoxy(*j,1);
        printf("00");
        strcat(binario,"00");
        printf("%d",bin);
        itoa(bin,auxOct,10);
        strcat(binario,auxOct);
    }
    else if(numInt>=4 && numInt<8){
        *j = *j+4;
        gotoxy(*j,1);
        printf("0");
        strcat(binario,"0");
        printf("%d",bin);
        itoa(bin,auxHex,10);
        strcat(binario,auxHex);
    }
    else if(numInt>=8){
        *j = *j+4;
        gotoxy(*j,1);
        printf("%d",bin);
        itoa(bin,auxHex,10);
        strcat(binario,auxHex);
    }
}

void IfsEscritaCorretaHex2Bin(int numInt,int* k,int bin){
    if(numInt<2){
        *k=*k+4;
        gotoxy(*k,1);
        printf("000");
        printf("%d",bin);
    }
    else if(numInt>=2 && numInt<4){
        *k = *k+4;
        gotoxy(*k,1);
        printf("00");
        printf("%d",bin);
    }
    else if(numInt>=4 && numInt<8){
        *k = *k+4;
        gotoxy(*k,1);
        printf("0");
        printf("%d",bin);
    }
    else if(numInt>=8){
        *k = *k+4;
        gotoxy(*k,1);
        printf("%d",bin);
    }
}
//USADA EM BIN2OCT e BIN2HEX
void Copia(int tam, int* i, char aux[5]){
    int m;
    for(m=0;m<tam;m++){
        aux[m] = num[*i+m];
    }
    aux[tam] = '\0';
}

int IfsEscritaDestacadaBin2Oct(int bin, int* i, int* j){ //ESSA TEVE Q SER INT POR CAUSA DO CONTINUE
    textcolor(CorDestaque);
    if( (strlen(num) % 3 ==0) && *i ==0){ //Algarismo 3 dígitos
        gotoxy(*i,1);
        printf("%c%c%c",num[*i],num[*i+1],num[*i+2]); //Printa Binario
        //COPIA DE num PARA auxBinOct
        Copia(3,i,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*j)++;
        gotoxy(*j,1);
        printf("%d",bin);
        itoa(bin,auxBinOct,10);
        strcat(binario,auxBinOct);
        pause(1);
        *i = *i +2; //Controle de posição
    }
    else if( (strlen(num) % 3 ==2)  && *i ==0){ //Algarismo 2 dígitos
        gotoxy(*i,1);
        printf("%c%c",num[*i],num[*i+1]);
        //COPIA DE num PARA auxBinOct
        Copia(2,i,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*j)++;
        gotoxy(*j,1);
        printf("%d",bin);
        itoa(bin,auxBinOct,10);
        strcat(binario,auxBinOct);
        pause(1);
        *i = *i +1; //Controle de posição
    }
    else if( (strlen(num) % 3 ==1)  && *i ==0){ //Algarismo 1 dígito
        gotoxy(*i,1);
        printf("%c",num[*i]);
        //COPIA DE num PARA auxBinOct
        Copia(1,i,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*j)++;
        gotoxy(*j,1);
        printf("%d",bin);
        itoa(bin,auxBinOct,10);
        strcat(binario,auxBinOct);
        pause(1);
        *i = *i+0; //Controle de posição
    }
    else{ //VAI ENTRAR AQUI SEMPRE DEPOIS DO PRIMEIRO ALGARISMO
        if( (*i+1)>=strlen(num) || (*i+2)>=strlen(num) ) //Para não escrever lixo
            return 1; //Preciso disso para isso chamar um continue

        gotoxy(*i+1,1); //Escreve em sequencia
        printf("%c%c%c",num[*i],num[*i+1],num[*i+2]); //Printa de 3 em 3
        //COPIA DE num PARA auxBinOct
        Copia(3,i,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*j)++;
        gotoxy(*j,1);
        printf("%d",bin);
        itoa(bin,auxBinOct,10);
        strcat(binario,auxBinOct);
        pause(1);
        *i = *i+2;//Arruma posição
    }
    return 0;
}

int IfsEscritaCorretaBin2Oct(int bin, int* l, int* k){
    if( (strlen(num) % 3 ==0) && *l ==0){ //Algarismo 3 dígitos
        gotoxy(*l,1);
        printf("%c%c%c",num[*l],num[*l+1],num[*l+2]);
        //COPIA DE num PARA auxBinOct
        Copia(3,l,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*k)++;
        gotoxy(*k,1);
        printf("%d",bin);
        pause(1);
        l = l +2;
    }
    else if( (strlen(num) % 3 ==2)  && *l ==0){ //Algarismo 2 dígitos
        gotoxy(*l,1);
        printf("%c%c",num[*l],num[*l+1]);
        //COPIA DE num PARA auxBinOct
        Copia(2,l,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*k)++;
        gotoxy(*k,1);
        printf("%d",bin);
        pause(1);
        *l = *l +1;
    }
    else if( (strlen(num) % 3 ==1)  && *l ==0){ //Algarismo 1 dígito
        gotoxy(*l,1);
        printf("%c",num[*l]);
        //COPIA DE num PARA auxBinOct
        Copia(1,l,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*k)++;
        gotoxy(*k,1);
        printf("%d",bin);
        pause(1);
        *l = *l+0;
    }
    else{ //PARA TUDO DEPOIS DO PRIMEIRO ALGARISMO
        if( (*l+1)>=strlen(num) || (*l+2)>=strlen(num) ) //Para não escrever lixo
            return 1; //Preciso disso para isso chamar um continue

        gotoxy(*l+1,1); //Escreve em sequencia
        printf("%c%c%c",num[*l],num[*l+1],num[*l+2]); //Printa de 3 em 3
        //COPIA DE num PARA auxBinOct
        Copia(3,l,auxBinOct);
        bin = StrBinParaNum(auxBinOct); //Bin tem a parcela binaria
        bin = BinParaOct(bin); //Bin tem a parcela conversida para octal
        //PRINTAR O OCTAL
        (*k)++;
        gotoxy(*k,1);
        printf("%d",bin);
        pause(1);
        *l = *l+2;//Arruma posição
    }
    return 0;
}
//BIN -> HEX
void IfsEscritaDestacadaCorretaBin2Hex(int bin, int* i, int* j, int controle){
    if(controle) //Essa variável controle é para determinar qual cor usar.
        textcolor(CorDestaque);
    else
        textcolor(CorNormal);

    int controleRef=1;
    char binChar;

    if( (strlen(num) % 4 ==0) && *i ==0){ //Algarismo 4 dígitos
        gotoxy(*i,1);
        printf("%c%c%c%c",num[*i],num[*i+1],num[*i+2],num[*i+3]); //Printa Binario
        //COPIA DE num PARA auxBinHex
        Copia(4,i,auxBinHex);
        bin = StrBinParaNum(auxBinHex); //Bin tem a parcela binaria
        bin = BinParaHex(bin,&controleRef); //Bin tem a parcela convertida para hexadecimal
        //PRINTAR O HEXADECIMAL
        (*j)++;
        gotoxy(*j,1);
        if(!controleRef) //Se controleRef == 0 bin é número, controleRef == 1 bin é letra
            printf("%d",bin);
        else{
            binChar = bin;
            printf("%c",binChar);
        }
        if(controle){ //Fazer essa cópia só no modo destacada, a cópia é feita 1 vez só.
            if(!controleRef){
                itoa(bin,auxBinHex,10); // itoa() = Convert integer to string
            }
            else{
                auxBinHex[0] = binChar;
                auxBinHex[1] = '\0'; //Isso é para não ter lixo
            }
            strcat(binario,auxBinHex);
            pause(1);
        }
        *i = *i +3; //Controle de posição
    }
    else if( (strlen(num) % 4 ==3)  && *i ==0){ //Algarismo 3 dígitos
        gotoxy(*i,1);
        printf("%c%c%c",num[*i],num[*i+1],num[*i+2]);
        //COPIA DE num PARA auxBinHex
        Copia(3,i,auxBinHex);
        bin = StrBinParaNum(auxBinHex); //Bin tem a parcela binaria
        bin = BinParaHex(bin,&controleRef); //Bin tem a parcela conversida para hexadecimal
        //PRINTAR O HEXADECIMAL
        (*j)++;
        gotoxy(*j,1);
        if(!controleRef)
            printf("%d",bin);
        else{
            binChar = bin;
            printf("%c",binChar);
        }
        if(controle){
            if(!controleRef){
                itoa(bin,auxBinHex,10); // itoa() = Convert integer to string
            }
            else{
                auxBinHex[0] = binChar;
                auxBinHex[1] = '\0'; //Isso é para não ter lixo
            }
            strcat(binario,auxBinHex);
            pause(1);
        }
        *i = *i +2; //Controle de posição
    }
    else if( (strlen(num) % 4 ==2)  && *i ==0){ //Algarismo 2 dígito
        gotoxy(*i,1);
        printf("%c%c",num[*i],num[*i+1]);
        //COPIA DE num PARA auxBinHex
        Copia(2,i,auxBinHex);
        bin = StrBinParaNum(auxBinHex); //Bin tem a parcela binaria
        bin = BinParaHex(bin,&controleRef); //Bin tem a parcela conversida para hexadecimal
        //PRINTAR O HEXADECIMAL
        (*j)++;
        gotoxy(*j,1);
        if(!controleRef)
            printf("%d",bin);
        else{
            binChar = bin;
            printf("%c",binChar);
        }
        if(controle){
            if(!controleRef){
                itoa(bin,auxBinHex,10); // itoa() = Convert integer to string
            }
            else{
                auxBinHex[0] = binChar;
                auxBinHex[1] = '\0'; //Isso é para não ter lixo
            }
            strcat(binario,auxBinHex);
            pause(1);
        }
        *i = *i+1; //Controle de posição
    }
    else if( (strlen(num) % 4 ==1)  && *i ==0){ //Algarismo 1 dígito
        gotoxy(*i,1);
        printf("%c",num[*i]);
        //COPIA DE num PARA auxBinHex
        Copia(1,i,auxBinHex);
        bin = StrBinParaNum(auxBinHex); //Bin tem a parcela binaria
        bin = BinParaHex(bin,&controleRef); //Bin tem a parcela conversida para hexadecimal
        //PRINTAR O HEXADECIMAL
        (*j)++;
        gotoxy(*j,1);
        if(!controleRef)
            printf("%d",bin);
        else{
            binChar = bin;
            printf("%c",binChar);
        }
        if(controle){
            if(!controleRef){
                itoa(bin,auxBinHex,10); // itoa() = Convert integer to string
            }
            else{
                auxBinHex[0] = binChar;
                auxBinHex[1] = '\0'; //Isso é para não ter lixo
            }
            strcat(binario,auxBinHex);
            pause(1);
        }
        *i = *i+0; //Controle de posição
    }
    else{ //VAI ENTRAR AQUI SEMPRE DEPOIS DO PRIMEIRO ALGARISMO
        gotoxy(*i+1,1); //Escreve em sequencia
        printf("%c%c%c%c",num[*i],num[*i+1],num[*i+2],num[*i+3]); //Printa de 4 em 4
        //COPIA DE num PARA auxBinHex
        Copia(4,i,auxBinHex);
        bin = StrBinParaNum(auxBinHex); //Bin tem a parcela binaria
        bin = BinParaHex(bin,&controleRef); //Bin tem a parcela conversida para hexadecimal
        //PRINTAR O HEXADECIMAL
        (*j)++;
        gotoxy(*j,1);
        if(!controleRef)
            printf("%d",bin);
        else{
            binChar = bin;
            printf("%c",binChar);
        }
        if(controle){
            if(!controleRef){
                itoa(bin,auxBinHex,10); // itoa() = Convert integer to string
            }
            else{
                auxBinHex[0] = binChar;
                auxBinHex[1] = '\0'; //Isso é para não ter lixo
            }
            strcat(binario,auxBinHex);
            pause(1);
        }
        *i = *i+3;//Arruma posição
    }
}
///FUNÇÕES ENVOLVENDO DECIMAL
void PrintaSomatorio(int base,int numInt,int tam,int i){
    int y = 3; //Coordenada Y
    int x = i; //Coordenada X

    if (base==8 || base==2){ //Gambiarra pra printar visualmente certo
        if(x>=7 && x<14){ //Após 7 impressões ir para a próxima linha (Y=4)
            x = x - 7;
            y=4;
        }else if(x>=14){ //Após 14 impressões ir para a próxima linha (Y=5)
            x = x - 14;
            y=5;
        }
        gotoxy(x*11-x+1,y);
    }
    if (base==16){ //Gambiarra pra printar visualmente certo
        if(x>=6 && x<12){
            x = x - 6;
            y=4;
        }else if(x>=12){
            x = x - 12;
            y=5;
        }
        gotoxy(x*13-x+1,y);
    }

    if(i != (tam-1))
        printf("%d * %d^%d +",numInt,base,tam-(i+1));
    else
        printf("%d * %d^%d",numInt,base,tam-(i+1));
    pause(1);
}

///FUNÇÕES DE PROGRAMA
void EncerrarPrograma(void){
    int i;
    system("cls");
    printf("Obrigada por usar meu programa!\n");
    printf("Desenvolvido por: Thalessa HD.\n");
    for(i=5;i>0;i--){
        gotoxy(1,3);
        printf("O programa irá fechar em %d segundos",i);
        pause(1);
    }
}

void escreveCabecalho(void){
    gotoxy(1,1);
    printf("Operação");
    gotoxy(20,1);
    printf("Quociente");
    gotoxy(40,1);
    printf("Resto");
}
///MAIN
int main(){
    setlocale(LC_ALL,"Portuguese"); //PARA PODER USAR ACENTOS
//VARIAVEIS
    char enter;
    int numInt,bin,i,op;
    int j=30,k,l; //VARIAVEIS DE CONTROLE DE POSIÇÃO
    int AtivaContinue=0;
    double decimal =0.0;
    int cont = 0;
    int verificaLetra; //1 - Letra ; 0 - Número
//LOOP MENU
    textcolor(CorNormal);
    while(op!=0){
//INICIALIZA VARIAVEIS
        strcpy(binario,"");
        strcpy(auxBinOct,"");
        decimal = 0.0; //Usado em Caso 5
        op = 1;
//MENU
        system("cls");
        printf("***** Projeto de FAC *****\n\n\n");
        printf("1 - Converter de Octal para Binário\n");
        printf("2 - Converter de Hexadecimal para Binário\n");
        printf("3 - Converter de Binário para Octal\n");
        printf("4 - Converter de Binário para Hexadecimal\n");
        printf("5 - Converter de Octal para Decimal\n");
        printf("6 - Converter de Hexadecimal para Decimal\n");
        printf("7 - Converter de Binário para Decimal\n");
        printf("8 - Converter de Decimal para Binário\n");
        printf("9 - Converter de Decimal para Octal\n");
        printf("10 - Converter de Decimal para Hexadecimal\n");
        printf("0 - Sair\n");
        printf("\nOpção:");
        scanf("%d",&op);
        fflush(stdin); //BUG DE CARACTER EM C
//SWITCH
        switch(op){
//CASO 1
        case 1:
            j = 30;
            if(!EntradaOct(1)){
                system("cls");
                printf("Valor inválido!");
                pause(1.5);
                break;
            }
            for(i=0;i<strlen(num);i++){
//ESCREVENDO DESTACADO
                k = j; //Para escrever o binario normal depois
                textcolor(CorDestaque); //Cor destacada
                gotoxy(i+1,1); //Para escrever em sequencia de acordo com o i que incrementa de 1 em 1
                printf("%c\n",num[i]); //Escreve o primeiro algarismo do número
                numInt = num[i] - 48; //converte char pra int
                bin = paraBin(numInt);
//IFS PARA ESCREVER O NUMERO BINARIO CORRETO COM 3 ALGARISMOS
                IfsEscritaDestacadaOct2Bin(numInt,&j,bin);
//ESCREVENDO NORMAL
                pause(1);
                textcolor(CorNormal); //Cor branca
                gotoxy(i+1,1);
                printf("%c\n",num[i]);
//IFS PARA ESCREVER O NUMERO BINARIO CORRETO COM 3 ALGARISMOS
                IfsEscritaCorretaOct2Bin(numInt,&k,bin);
                pause(1);
            }
        fflush(stdin);
        gotoxy(1,3);
        printf("%s OCTAL corresponde a %s em BINÁRIO\n",num,binario);
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 2
        case 2:
            j =25; //CONTROLE DE POSIÇÃO
            if(!EntradaHex(1)){
                system("cls");
                printf("Valor inválido!");
                pause(1.5);
                break;
            }
            for(i=0;i<strlen(num);i++){
//ESCREVENDO DESTACADO
                k = j;
                textcolor(CorDestaque);
                gotoxy(i+1,1); //Posição dos algarismos
                printf("%c\n",num[i]); //Escreve o primeiro algarismo do número
                if(!(num[i]>57 && num[i]<71)) //If para controlar se for Número ou Letra
                    numInt = num[i] - 48; //Numero
                else
                    numInt = num[i]; //Letra
                bin = paraBinLetra(numInt);
//IFS PARA ESCREVER O NUMERO BINARIO CORRETO COM 4 ALGARISMOS
                IfsEscritaDestacadaHex2Bin(numInt,&j,bin);
//ESCREVENDO NORMAL
                pause(1);
                textcolor(CorNormal); //Cor branca
                gotoxy(i+1,1);
                printf("%c\n",num[i]);
//IFS PARA ESCREVER O NUMERO BINARIO CORRETO COM 4 ALGARISMOS
                IfsEscritaCorretaHex2Bin(numInt,&k,bin);
                pause(1);
            }
        fflush(stdin);
        gotoxy(1,3);
        printf("%s HEXADECIMAL corresponde a %s em BINÁRIO\n",num,binario);
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 3
        case 3:
            j =40;
            if(!EntradaBin(1)){
                system("cls");
                printf("Valor inválido!");
                pause(1.5);
                break;
            }
            AtivaContinue=0; //Variavel de controle
            for(i=0;i<(strlen(num));i++){
//ESCREVENDO DESTACADO
                k = j; //Para poder escrever normal depois
                l = i; //Para poder escrever normal depois
                AtivaContinue = IfsEscritaDestacadaBin2Oct(bin,&i,&j);
                if(AtivaContinue)
                    continue;
//ESCREVENDO NORMAL
                pause(1);
                textcolor(CorNormal); //Cor branca
                gotoxy(l+1,1);
                AtivaContinue = IfsEscritaCorretaBin2Oct(bin,&l,&k);
                if(AtivaContinue)
                    continue;
            }
        fflush(stdin);
        gotoxy(1,3);
        printf("%s BINÁRIO corresponde a %s em OCTAL\n",num,binario);
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 4
        case 4:
            j = 50;
            if(!EntradaBin(2)){
                system("cls");
                printf("Valor inválido!");
                pause(1.5);
                break;
            }
            for(i=0;i<(strlen(num));i++){
                k = j; //Para poder escrever normal depois
                l = i; //Para poder escrever normal depois
//ESCREVENDO DESTACADO
                IfsEscritaDestacadaCorretaBin2Hex(bin,&i,&j,1);
//ESCREVENDO NORMAL
                pause(1);
                gotoxy(l+1,1);
                IfsEscritaDestacadaCorretaBin2Hex(bin,&l,&k,0);
            }

        fflush(stdin);
        gotoxy(1,3);
        printf("%s BINÁRIO corresponde a %s em HEXADECIMAL\n",num,binario);
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 5
        case 5:
        j = 0;
        if(!EntradaOct(2)){
                system("cls");
                printf("Valor inválido!");
                pause(1.5);
                break;
        }
        for(i=0;i<(strlen(num));i++){
            textcolor(CorDestaque);
            gotoxy(i+1,1);
            printf("%c\n\n",num[i]); //PRINTA O ALGARISMO OCTAL
            numInt = num[i] - 48; //CONVERTE STRING->INT
            decimal = decimal + numInt * pow(8.0,(strlen(num)-(i+1))); //CALCULA O VALOR DECIMAL
            PrintaSomatorio(8,numInt,strlen(num),i);
            textcolor(CorNormal);
            gotoxy(i+1,1);
            printf("%c\n\n",num[i]);
            numInt = num[i] - 48;
            PrintaSomatorio(8,numInt,strlen(num),i);
        }
        fflush(stdin);
        gotoxy(1,6);
        printf("%s OCTAL corresponde a %.0lf em DECIMAL\n",num,decimal);
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 6
        case 6:
        j = 0;
        if(!EntradaHex(2)){
            system("cls");
            printf("Valor inválido!");
            pause(1.5);
            break;
        }
        for(i=0;i<(strlen(num));i++){
            textcolor(CorDestaque);
            gotoxy(i+1,1);
            printf("%c\n\n",num[i]); //PRINTA O ALGARISMO HEXADECIMAL
            if(!(num[i]>57 && num[i]<71)) //If para controlar se for Número ou Letra
                numInt = num[i] - 48; //Numero
            else{
                numInt = paraDecLetra(num[i]); //Letra
            }
            decimal = decimal + numInt * pow(16.0,(strlen(num)-(i+1))); //CALCULA O VALOR DECIMAL
            PrintaSomatorio(16,numInt,strlen(num),i);
            textcolor(CorNormal);
            gotoxy(i+1,1);
            printf("%c\n\n",num[i]);
            PrintaSomatorio(16,numInt,strlen(num),i);
        }
        fflush(stdin);
        gotoxy(1,6);
        printf("%s HEXADECIMAL corresponde a %.0lf em DECIMAL\n",num,decimal);
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 7
        case 7:
        j = 0;
        if(!EntradaBin(3)){
            system("cls");
            printf("Valor inválido!");
            pause(1.5);
            break;
        }
        for(i=0;i<(strlen(num));i++){
            textcolor(CorDestaque);
            gotoxy(i+1,1);
            printf("%c\n\n",num[i]); //PRINTA O ALGARISMO BINARIO
            numInt = num[i] - 48; //CONVERTE STRING->INT
            decimal = decimal + numInt * pow(2.0,(strlen(num)-(i+1))); //CALCULA O VALOR DECIMAL
            PrintaSomatorio(2,numInt,strlen(num),i);
            textcolor(CorNormal);
            gotoxy(i+1,1);
            printf("%c\n\n",num[i]);
            numInt = num[i] - 48;
            PrintaSomatorio(2,numInt,strlen(num),i);
        }
        fflush(stdin);
        gotoxy(1,6);
        printf("%s BINÁRIO corresponde a %.0lf em DECIMAL\n",num,decimal);
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 8
        case 8:
        if(!EntradaDec(1)){
            system("cls");
            printf("Valor inválido!");
            pause(1.5);
            break;
        }
        //INICIALIZA
        i=0; cont = 0;
        numInt = atoi(num); //Convert de STRING->INT
        escreveCabecalho(); //Escreve os titulos das colunas
        while(numInt>=0){
//ESCREVENDO DESTACADO
                textcolor(CorDestaque);
                gotoxy(1,i+1);
                printf("\n%d/2",numInt); //Escreve o número fração pela base
                vetorRestos[cont] = numInt%2; //Pega o resto
                textcolor(CorDestaque);
                gotoxy(20,i+2);
                pause(1);
                printf("%d",numInt/2); //Escreve o quociente
                textcolor(CorResto);
                gotoxy(40,i+2);
                pause(1);
                printf("%d",vetorRestos[cont]); //Escreve o resto
//ESCREVENDO NORMAL
                pause(1);
                textcolor(CorNormal); //Cor branca
                gotoxy(1,i+1);
                printf("\n%d/2",numInt);
                textcolor(CorNormal);
                gotoxy(20,i+2);
                printf("%d",numInt/2); //Escreve o quociente

                numInt = numInt/2; //Divide o numero pela base
                i++; //Variavel do "for"
                cont++; //Indice do vetor de resto
                pause(1);
                if(numInt==0) //Tratar o num = 0
                    break;
            }
        fflush(stdin);
        gotoxy(1,i+2);
        printf("\n%s DECIMAL corresponde a ",num);
        for(i=(cont-1);i>-1;i--)
            printf("%d",vetorRestos[i]);
        printf(" em BINÁRIO\n");
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 9
        case 9:
        if(!EntradaDec(2)){
            system("cls");
            printf("Valor inválido!");
            pause(1.5);
            break;
        }
        //INICIALIZA
        i=0; cont = 0;
        numInt = atoi(num); //Convert de STRING->INT
        escreveCabecalho(); //Escreve os titulos das colunas
        while(numInt>=0){
//ESCREVENDO DESTACADO
            textcolor(CorDestaque);
            gotoxy(1,i+1);
            printf("\n%d/8",numInt); //Escreve o número fração pela base
            vetorRestos[cont] = numInt%8;      //Pega o resto
            textcolor(CorDestaque);
            gotoxy(20,i+2);
            pause(1);
            printf("%d",numInt/8); //Escreve o quociente
            textcolor(CorResto);
            gotoxy(40,i+2);
            pause(1);
            printf("%d",vetorRestos[cont]); //Escreve o resto
//ESCREVENDO NORMAL
            pause(1);
            textcolor(CorNormal); //Cor branca
            gotoxy(1,i+1);
            printf("\n%d/8",numInt);
            textcolor(CorNormal);
            gotoxy(20,i+2);
            printf("%d",numInt/8);

            numInt = numInt/8;
            i++;
            cont++;
            pause(1);
            if(numInt==0) //Tratar o num = 0
                break;
            }
        fflush(stdin);
        gotoxy(1,i+2);
        printf("\n%s DECIMAL corresponde a ",num);
        for(i=(cont-1);i>-1;i--)
            printf("%d",vetorRestos[i]);
        printf(" em OCTAL\n");
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 10
        case 10:
        if(!EntradaDec(3)){
            system("cls");
            printf("Valor inválido!");
            pause(1.5);
            break;
        }
        //INICIALIZA
        i=0; cont = 0;
        numInt = atoi(num); //Convert de STRING->INT
        escreveCabecalho(); //Escreve os titulos das colunas
        while(numInt>=0){
        //INICIALIZA
            verificaLetra = 0;
//ESCREVENDO DESTACADO
            textcolor(CorDestaque);
            gotoxy(1,i+1);
            printf("\n%d/16",numInt); //Escreve o número fração pela base

            vetorRestos[cont] = numInt%16; //Pega o resto
            if(vetorRestos[cont]>9){
                vetorRestos[cont] = decimalToLetra(vetorRestos[cont]); //Decimal->Letra
                verificaLetra = 1; //Sinal para ser Letra
            }
            textcolor(CorDestaque);
            gotoxy(20,i+2);
            pause(1);
            printf("%d",numInt/16); //Escreve o quociente
            textcolor(CorResto);
            gotoxy(40,i+2);
            pause(1);
            if(verificaLetra)
                printf("%c",vetorRestos[cont]); //Escreve o resto com char
            else
                printf("%d",vetorRestos[cont]); //Escreve o resto com int
//ESCREVENDO NORMAL
            pause(1);
            textcolor(CorNormal); //Cor branca
            gotoxy(1,i+1);
            printf("\n%d/16",numInt);
            textcolor(CorNormal);
            gotoxy(20,i+2);
            printf("%d",numInt/16); //Escreve o quociente

            numInt = numInt/16; //Divide o numero pela base
            i++; //Variavel do "for"
            cont++; //Indice do vetor de resto
            pause(1);
            if(numInt==0) //Tratar o num = 0
                break;
        }
        fflush(stdin);
        gotoxy(1,i+2);
        printf("\n%s DECIMAL corresponde a ",num);
        for(i=(cont-1);i>-1;i--){
            if(vetorRestos[i]<10)
                printf("%d",vetorRestos[i]); //Número
            else
                printf("%c",vetorRestos[i]); //Letra
        }
        printf(" em HEXADECIMAL\n");
        printf("Pressione ENTER para voltar ao menu");
        scanf("%c",&enter);
        break;
//CASO 0
        case 0:
            op = 0;
        break;
//DEFAULT
        default:
            system("cls");
            printf("Opção incorreta\n");
            pause(1.5);
        break;
        }
        //FORA DO SWITCH
    }
//FORA DO WHILE
    EncerrarPrograma();
    return 0;
}
///FUNÇÕES
int potencia(int x, int y){
    int i;
    int pot = 1;
    for(i=0;i<y;i++)
        pot = pot*x;
    return pot;
}

int paraBin(int x){
    int digito,binario=0,cont=0;
    while (x>0){
        digito = x%2 ;
        binario = binario + digito * potencia(10,cont);
        x = x/2;
        cont++;
    }
    return binario;
}

int paraBinLetra(int x){
    int binario;
    if(x=='A')
        binario = 1010;
    else if(x=='B')
        binario = 1011;
    else if(x=='C')
        binario = 1100;
    else if(x=='D')
        binario = 1101;
    else if(x=='E')
        binario = 1110;
    else if(x=='F')
        binario = 1111;
    else
        binario = paraBin(x);
    return binario;
}

int paraDecLetra(int x){
    int decimal;
    if(x=='A')
        decimal = 10;
    else if(x=='B')
        decimal = 11;
    else if(x=='C')
        decimal = 12;
    else if(x=='D')
        decimal = 13;
    else if(x=='E')
        decimal = 14;
    else if(x=='F')
        decimal = 15;
    return decimal;
}

char decimalToLetra(int x){
    if(x==10)
        return 'A';
    if(x==11)
        return 'B';
    if(x==12)
        return 'C';
    if(x==13)
        return 'D';
    if(x==14)
        return 'E';
    if(x==15)
        return 'F';
}

int BinParaOct(int x){
    int digito,resultado=0,cont=0;
    while (x>0){
        digito = x%10 ;
        resultado = resultado + digito * potencia(2,cont);
        x = x/10;
        cont++;
    }
    return resultado;
}

int BinParaHex(int x, int* controleRef){
    //ControleRef serve para controlar quando for letra e quando for numero
    int digito,resultado=0,cont=0;
    if(x==1010){ //A
        if(*controleRef) //Se controleRef == 1, entra nesse If e continua 1
            *controleRef = 1;
        resultado = 65;
    }
    else if(x==1011){ //B
        if(*controleRef)
            *controleRef = 1;
        resultado = 66;
    }
    else if(x==1100){ //C
        if(*controleRef)
            *controleRef = 1;
        resultado = 67;
    }
    else if(x==1101){ //D
        if(*controleRef)
            *controleRef = 1;
        resultado = 68;
    }
    else if(x==1110){ //E
        if(*controleRef)
            *controleRef = 1;
        resultado = 69;
    }
    else if(x==1111){ //F
        if(*controleRef)
            *controleRef = 1;
        resultado = 70;
    }
    else{ //Se entrar aqui é pq o valor é número e não letra
        resultado = BinParaOct(x);
        *controleRef = 0; //Aqui vai retornar 0 dizendo que é número
    }
    return resultado;
}

int StrBinParaNum(char str[5]){
    int i, result=0,cont;
    int tam = strlen(str);
    cont = tam-1; //Para poder funcionar
        for(i = 0 ; i<tam ; i++){
            if(str[i]=='1'){
                result = result +  potencia(10,cont);
            }
            cont--;
        }
    return result;
}

void pause (float delay1) {
   if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;
}

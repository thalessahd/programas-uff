#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 #include <windows.h>
using namespace std;

int tiraEspaco(char str[100]){
    int tam = strlen(str),j=0;
    char aux[100];
    strcpy(aux,str);
    for(int i =0; i<=tam; i++){
        if(aux[i]!=32 && aux[i]!='\n'){
            str[j] = aux[i];
            j++;
        }
    }

    return (j-1); //-1 PRA TIRAR O \0
}

int tirarLadoEsq(char str[100]){
    int tam = strlen(str),j=0;
    char aux[100];
    int ok = 0;
    strcpy(aux,str);
    for(int i =0; i<=tam; i++){
        if(ok){
            str[j] = aux[i];
            j++;
        }
        if(aux[i]=='-'){
            ok = 1;
        }
    }

    return (j-1); //-1 PRA TIRAR O \0
}

int verificaExcTipo1(char c,char str[100]){ //SE QUEBRAR A REGRA RETURN 0 SENAO RETURN 1
    int tam = strlen(str);
    for(int i = 0;i<tam;i++){
        if(str[i]==c)
            return 0;
    }
    return 1;
}
/*COMENTARIOS
    VALIDAR TIPO 1 SÓ FUNCIONA SE CASO TIVER e ESTE VIER NA PRIMEIRA LINHA SEMPRE
*/

int main(){
    FILE* pEntrada;
    char entrada[100] = "entrada.txt", read[100],auxRead[100],letraMai;
    int quantEsq=0,tam,indiceTraco,quantDir=0,tamAux,okExc=1,okE=0,ok3=1;
    //okExc COMEÇA COM 1 = REGRA SATISFEITA; okE COMEÇA COM 0 = NÃO POSSUI e

    int resposta[4] = {1,1,1,1};

    //cout << "Digite o nome do arquivo de entrada com extensao:" << endl;
    //cin >> entrada;

    pEntrada = fopen(entrada,"r");
    if(pEntrada==NULL){ printf("Erro abertura do arquivo\n"); exit(1); }

    while(fgets(read, 30, pEntrada)!=NULL){
        tam = tiraEspaco(read);
        quantEsq = 0;
        strcpy(auxRead,read);

        //cout << read << endl;

//VERIFICA TIPO 1 e 2
        for(int i=0;i<tam;i++){ //CALCULA A QUANT A ESQUERDA
            if(read[i]!='-')
                quantEsq++;
            else{
                indiceTraco = i;
                break;
            }
        }

        if(read[tam-1]!='e') //NÃO POSSUI e
            quantDir = tam - (indiceTraco+1);
        else{               //POSSUI e
            okE = 1;
            letraMai = read[0];
            quantDir = 1;
        }

        if(okExc){ //SE NÃO QUEBROU A REGRA
            tamAux = tirarLadoEsq(auxRead);
            okExc = verificaExcTipo1(letraMai,auxRead);
        }
//FIM

//VERIFICA TIPO 3
        if(quantEsq==1 && ok3==1){
            if(quantDir>2)
                ok3 = 0;

            tamAux = tirarLadoEsq(auxRead);

            if(auxRead[0]>64 && auxRead[0]<91) //SE FOR LETRA MAIUSCULA
                ok3 = 0;

            if(quantDir==2 && auxRead[0]<91 && auxRead[1]<91) //SE AS DUAS LETRAS FOREM MINUSCULAS
                ok3=0;
        }
        else{
            ok3 = 0;
        }
//RESULTADO DO TIPO 1 E 2
        if(!okExc && okE) //SE QUEBRAR A REGRA E POSSUIR e NÃO EH TIPO 1
            quantDir = 0;

        if(quantEsq>1)
            resposta[2] = 0;

        if(quantDir<quantEsq)
            resposta[1] = 0;
    }
//FIM LEITURA DO ARQUIVO
//RESULTADO DO TIPO 3
    if(!okE) //SE NÃO POSSUIR e
        ok3 = 0;
    if(!ok3)
        resposta[3] = 0;

    for(int i=3; i>-1 ;i--){
        if(resposta[i]==1){
            cout << "Gramatica tipo " << i << endl;
            cout << "O programa ira encerrar em 3 segundos.." << endl;
            Sleep(3000);
            break;
        }
    }

    fclose(pEntrada);
    return 0;
}

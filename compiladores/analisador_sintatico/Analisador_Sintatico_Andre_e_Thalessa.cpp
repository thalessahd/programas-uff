///MUDANÇAS NO ARQUIVO DE ENTRADA
/*
LINHA 7 TIREI O ;
LINHA 54 CONSERTEI A PALAVRA PROCEDURE
LINHA 63 CONSERTEI A PALAVRA PRINCIPAL
*/
///MUDANÇAS NA GRAMÁTICA
/*
<VARIAVEIS> -> <VARIAVEL> <VARIAVEIS_2>
<VARIAVEIS> -> E
<VARIAVEIS_2> -> ; <VARIAVEIS>
<VARIAVEIS_2> -> E
*/
///PROBLEMA
/*
REGRA <COMANDO> DEVERIA LEVAR TAMBÉM A REGRA <NOME_NUMERO>, MAS ISSO IRIA GERAR AMBIGUIDADE COM A REGRA
<NOME> := <EXP_MATEMATICA> E EU NÃO SOUBE RESOLVER A AMBIGUIDADE
*/
#include <bits/stdc++.h>

using namespace std;

typedef struct Token{
        int linha;
        string word;
        int codigo;
}token;
vector<token> lista_tokens;
int atual =0;

void programa(void);
void corpo(void);
void declaracoes(void);
void def_constantes(void);
void def_tipos(void);
void def_variaveis(void);
void constantes(void);
void constantes_2(void);
void constante(void);
void const_valor(void);
void numero(void);
void tipos(void);
void tipos_2(void);
void tipo(void);
void variaveis(void);
void variaveis_2(void);
void variavel(void);
void lista_id(void);
void lista_id_2(void);
void tipo_dado(void);
void def_rotinas(void);
void funcao(void);
void procedimento(void);
void nome_rotina(void);
void bloco_rotina(void);
void bloco(void);
void comandos(void);
void comando(void);
void else_1(void);
void parametro(void);
void lista_param(void);
void lista_param_2(void);
void exp_logica(void);
void exp_logica_2(void);
void exp_matematica(void);
void exp_matematica_2(void);
void nome_numero(void);
void op_logico(void);
void op_matematico(void);
void nome(void);
void nome_2(void);
void nome_3(void);
void identificador(void);
void erro(void);

void op_logico(void){
    if(lista_tokens[atual].codigo!=3){ //operador_logico
        erro();
    }else{
        cout << "op_logico" << endl;
        atual++;
    }
}

void op_matematico(void){
    if(lista_tokens[atual].codigo!=5){ //operador_matematico
        erro();
    }else{
        cout << "operador_matematico" << endl;
        atual++;
    }
}

void identificador(void){
    if(lista_tokens[atual].codigo!=2){ //identificador
        erro();
    }else{
        cout << "identificador" << endl;
        atual++;
    }
}

void numero(void){
    if(lista_tokens[atual].codigo!=1){ //numero
        erro();
    }else{
        cout << "numero" << endl;
        atual++;
    }
}

void tipo_dado(void){
    if(lista_tokens[atual].codigo==26){//integer
        cout << "integer" << endl;
        atual++;
    }
    else if(lista_tokens[atual].codigo==27){//real
        cout << "real" << endl;
        atual++;
    }
    else if(lista_tokens[atual].codigo==28){//array
        atual++; //prox token
        cout << "array" << endl;
        if(lista_tokens[atual].codigo==12){//[
            atual++; //prox token
            cout << "[" << endl;
            numero();
            if(lista_tokens[atual].codigo==13){//]
                cout << "]" << endl;
                atual++; //prox token
                if(lista_tokens[atual].codigo==29){//of
                    cout << "of" << endl;
                    atual++; //prox token
                    tipo_dado();
                }else{
                    erro();
                }
            }else{
                erro();
            }
        }else{
            erro();
        }
    }
    else if(lista_tokens[atual].codigo==30){ //record
        cout << "record" << endl;
        atual++; //prox token
        variaveis();
        if(lista_tokens[atual].codigo==22){ //end
            cout << "end" << endl;
            atual++;
        }
        else{
            erro();
        }
    }
    else{
        identificador();
    }
}
///REGRA ORIGINAL DE <VARIAVEIS>
/*void variaveis(void){
    variavel();
    variaveis_2();
}*/

void variaveis(void){
    ///<VARIAVEIS> -> <VARIAVEL> <VARIAVEIS_2>
    ///<VARIAVEIS> -> E
    ///<VARIAVEIS_2> -> ; <VARIAVEIS>
    ///<VARIAVEIS_2> -> E
    if(lista_tokens[atual].codigo==2){ //identificador
        variavel();
        variaveis_2();
    }else{
        cout << "E" << endl;
    }
}

void variaveis_2(void){
    if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
        cout << ";Variaveis_2" << endl;
        atual++; //prox token;
        variaveis();
    }else{
        cout << "E" << endl; //vazio
    }
}

void variavel(void){
    lista_id();
    if(lista_tokens[atual].codigo==7){ //dois_pontos
        cout << ":Variavel" << endl;
        atual++; //prox token
        tipo_dado();
    }else{
        erro();
    }
}

void lista_id(void){
    identificador();
    lista_id_2();
}

void lista_id_2(void){
    if(lista_tokens[atual].codigo==6){ //virgula
        cout << ",Lista_id_2" << endl;
        atual++; //prox token
        lista_id();
    }else{
        cout << "E" << endl; //vazio
    }
}

void constantes(void){
    constante();
    constantes_2();
}

void constantes_2(void){
    ///<CONSTANTES_2> -> <CONSTANTE>
    ///<CONSTANTES_2> -> E
    if(lista_tokens[atual].codigo==2){ //identificador
        constante();
    }else{
        cout << "E" << endl; //vazio
    }
}

void constante(void){
    identificador();
    if(lista_tokens[atual].word=="="){
        cout << "=Constante" << endl;
        atual++; //prox token
        const_valor();
        if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
            atual++;
            cout << ";Constante" << endl;
        }else{
            erro();
        }
    }else{
        erro();
    }
}

void const_valor(void){
    if(lista_tokens[atual].codigo==14){ //alfanumerico
        atual++;
        cout << "alfanumerico" << endl;
    }
    else{
        exp_matematica();
    }
}

void exp_matematica(void){
    if(lista_tokens[atual].codigo==10){ //abre_parentese
        cout << "( Exp_matematica" << endl;
        atual++; //prox token
        nome_numero();
        op_matematico();
        exp_matematica();
        if(lista_tokens[atual].codigo==11){ //fecha_parentese
            atual++;
            cout << ") Exp_matematica" << endl;
        }else{
            erro();
        }
    }else{
        nome_numero();
        exp_matematica_2();
    }
}

void exp_matematica_2(void){
    ///<EXP_MATEMATICA_2> -> <OP_MATEMATICO> <EXP_MATEMATICA>
    ///<EXP_MATEMATICA_2> -> E
    if(lista_tokens[atual].codigo==5){ //op_matematico
        op_matematico();
        exp_matematica();
    }else{
        cout << "E" << endl; //vazio
    }
}

void nome_numero(void){
    if(lista_tokens[atual].codigo==2){ //identificador
        identificador();
        nome_3();
    }else{
        numero();
    }
}

void nome_3(void){
    if(lista_tokens[atual].codigo==10){ //abre_parentese
        cout << "( Nome_3" << endl;
        atual++; //prox token
        parametro();
        if(lista_tokens[atual].codigo==11){ //fecha_parentese
            atual++;
            cout << ") Nome_3" << endl;
        }else{
            erro();
        }
    }else{
        nome_2();
    }
}

void nome_2(void){
    if(lista_tokens[atual].codigo==9){ //ponto
        cout << "." << endl;
        atual++; //prox token
        nome();
    }
    else if(lista_tokens[atual].codigo==12){ //abre_colchete
        cout << "[ Nome_2" << endl;
        atual++; //prox token
        nome_numero();
        if(lista_tokens[atual].codigo==13){ //fecha_colchete
            atual++;
            cout << "] Nome_2" << endl;
        }else{
            erro();
        }
    }
    else{
        cout << "E" << endl; //vazio
    }
}

void nome(void){
    identificador();
    nome_2();
}

void tipos(void){
    tipo();
    tipos_2();
}

void tipos_2(void){
    if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
        cout << ";Tipos_2" << endl;
        atual++;
        tipos();
    }else{
        cout << "E" << endl; //vazio
    }
}

void lista_param(void){
    nome_numero();
    lista_param_2();
}

void lista_param_2(void){
    if(lista_tokens[atual].codigo==6){ //virgula
        cout << ",Lista_param2" << endl;
        atual++;
        lista_param();
    }else{
        cout << "E" << endl;
    }
}

void exp_logica(void){
    exp_matematica();
    exp_logica_2();
}

void exp_logica_2(void){
    ///<EXP_LOGICA_2> -> <OP_LOGICO> <EXP_LOGICA>
    ///<EXP_LOGICA_2> -> E
    if(lista_tokens[atual].codigo==3){ //operador_logico
        op_logico();
        exp_logica();
    }else{
        cout << "E" << endl;
    }
}

void parametro(void){
    ///<PARAMETRO> -> <LISTA_PARAM>
    ///<PARAMETRO> -> E
    if(lista_tokens[atual].codigo==1 || lista_tokens[atual].codigo==2){ //numero ou identificador
        lista_param();
    }else{
        cout << "E" << endl;
    }
}

void else_1(void){
    if(lista_tokens[atual].codigo==38){ //else
        cout << "else" << endl;
        atual++;
        bloco();
    }else{
        cout << "E" << endl;
    }
}

void comando(void){
    if(lista_tokens[atual].codigo==33){ //while
        cout << "while" << endl;
        atual++;
        exp_logica();
        bloco();
    }else if(lista_tokens[atual].codigo==34){ //if
        cout << "if" << endl;
        atual++;
        exp_logica();
        if(lista_tokens[atual].codigo==35){ //then
            cout << "then" << endl;
            atual++;
            bloco();
            else_1();
        }else{
            erro();
        }
    }else if(lista_tokens[atual].codigo==36){ //write
        cout << "write" << endl;
        atual++;
        const_valor();
    }else if(lista_tokens[atual].codigo==37){ //read
        cout << "read" << endl;
        atual++;
        nome();
    }
    else{
        nome();
        if(lista_tokens[atual].codigo==8){ //atribuicao
            cout << ":=" << endl;
            atual++;
            exp_matematica();
        }else{
            erro();
        }
    }
}

void comandos(void){
    ///<COMANDOS> -> <COMANDO> ; <COMANDOS>
    ///<COMANDOS> -> E
    if(lista_tokens[atual].codigo==33 || lista_tokens[atual].codigo==34 || lista_tokens[atual].codigo==36 || lista_tokens[atual].codigo==37 || lista_tokens[atual].codigo==2){ //while ou if ou write ou read ou identificador
        comando();
        if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
            cout << ";Comandos" << endl;
            atual++;
            comandos();
        }else{
            erro();
        }
    }else{
        cout << "E" << endl;
    }
}

void bloco(void){
    if(lista_tokens[atual].codigo==21){ //begin
        cout << "beginBloco" << endl;
        atual++;
        comandos();
        if(lista_tokens[atual].codigo==22){ //end
            atual++;
            cout << "endBloco" << endl;
        }else{
            erro();
        }
    }else{
        comando();
    }
}

void bloco_rotina(void){
    ///<BLOCO_ROTINA> -> <DEF_VARIAVEIS> <BLOCO>
    ///<BLOCO_ROTINA> -> <BLOCO>
    if(lista_tokens[atual].codigo==21 || lista_tokens[atual].codigo==33 || lista_tokens[atual].codigo==34 || lista_tokens[atual].codigo==36 || lista_tokens[atual].codigo==37 || lista_tokens[atual].codigo==2){ //begin ou while ou if ou write ou read ou identificador
        bloco();
    }else{
        def_variaveis();
        bloco();
    }
}

void nome_rotina(void){
    identificador();
    if(lista_tokens[atual].codigo==10){ //abre_parentese
        cout << "( Nome_rotina" << endl;
        atual++;
        variaveis();
        if(lista_tokens[atual].codigo==11){ //fecha_parentese
            atual++;
            cout << ") Nome_rotina" << endl;
        }else{
            erro();
        }
    }else{
        erro();
    }
}

void procedimento(void){
    if(lista_tokens[atual].codigo==32){ //procedure
        cout << "procedure" << endl;
        atual++;
        nome_rotina();
        bloco_rotina();
    }else{
        erro();
    }
}

void funcao(void){
    if(lista_tokens[atual].codigo==31){ //function
        cout << "function" << endl;
        atual++;
        nome_rotina();
        if(lista_tokens[atual].codigo==7){ //dois_pontos
            cout << ":Funcao" << endl;
            atual++;
            tipo_dado();
            bloco_rotina();
        }else{
            erro();
        }
    }else{
        erro();
    }
}

void def_variaveis(void){
    if(lista_tokens[atual].codigo==25){ //var
        cout << "var" << endl;
        atual++;
        variaveis();
    }else{
        cout << "E" << endl;
    }
}

void def_tipos(void){
    if(lista_tokens[atual].codigo==24){ //type
        cout << "type" << endl;
        atual++;
        tipos();
    }else{
        cout << "E" << endl;
    }
}

void def_constantes(void){
    if(lista_tokens[atual].codigo==23){ //const
        cout << "const" << endl;
        atual++;
        constantes();
    }else{
        cout << "E" << endl;
    }
}

void tipo(void){
    identificador();
    if(lista_tokens[atual].word=="="){
        cout << "=Tipo" << endl;
        atual++;
        tipo_dado();
    }else{
        erro();
    }
}

void declaracoes(void){
    def_constantes();
    def_tipos();
    def_variaveis();
    def_rotinas();
}

void programa(void){
    if(lista_tokens[atual].codigo==20){ //program
        cout << "program" << endl;
        atual++;
        identificador();
        if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
            cout << ";Programa" << endl;
            atual++;
            corpo();
        }else{
            erro();
        }
    }else{
        erro();
    }
}

void def_rotinas(void){
    ///<DEF_ROTINAS> -> <FUNCAO> <DEF_ROTINAS>
    ///<DEF_ROTINAS> -> <PROCEDIMENTO> <DEF_ROTINAS>
    ///<DEF_ROTINAS> -> E
    if(lista_tokens[atual].codigo==31){ //function
        funcao();
        def_rotinas();
    }
    else if(lista_tokens[atual].codigo==32){ //procedure
        procedimento();
        def_rotinas();
    }
    else{
        cout << "E" << endl;
    }
}

void corpo(void){
    if(lista_tokens[atual].codigo==21){ //begin
        atual++;
        cout << "beginCorpo" << endl;
        comandos();
        if(lista_tokens[atual].codigo==22){ //end
            atual++;
            cout << "endCorpo" << endl;
        }else{
            erro();
        }
    }else{
        declaracoes();
        if(lista_tokens[atual].codigo==21){ //begin
            atual++;
            cout << "beginCorpo" << endl;
            comandos();
            if(lista_tokens[atual].codigo==22){ //end
                atual++;
                cout << "endCorpo" << endl;
            }else{
                erro();
            }
        }else{
            erro();
        }
    }
}

void erro(void){
    cout << "Erro no token " << lista_tokens[atual].word << " na linha " << lista_tokens[atual].linha << endl;
    exit(-1);
}

int main(){
    char entrada[100] ="saida_lexico_sin.txt";
    //char entrada[100] ="teste.txt";
    token t;
    string line;
    ifstream myfile;
    myfile.open(entrada);
    if(myfile.is_open()){
        while(!myfile.eof()){
            getline(myfile,line);
            t.word = line;
            getline(myfile,line);
            istringstream aux (line);
            aux >> t.linha;
            getline(myfile,line);
            istringstream aux2 (line);
            aux2 >> t.codigo;
            lista_tokens.push_back(t);
        }
        myfile.close();
    }
    else
        cout << "Erro ao abrir o arquivo " << entrada;
    atual =0;
    programa();
    return 0;
}

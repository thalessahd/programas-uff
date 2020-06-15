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

09/11
A GRAMÁTICA ESTAVA COM UM ERRINHO
ERRADO <CONSTANTES_2> -> <CONSTANTE>
CERTO <CONSTANTES_2> -> <CONSTANTES>
*/
///PROBLEMA
/*
REGRA <COMANDO> DEVERIA LEVAR TAMBÉM A REGRA <NOME_NUMERO>, MAS ISSO IRIA GERAR AMBIGUIDADE COM A REGRA
<NOME> := <EXP_MATEMATICA> E EU NÃO SOUBE RESOLVER A AMBIGUIDADE
*/
///SEMÂNTICO
/*
Implementado!
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
void erroSemantico(int erro);
void semantico(int x);
void debugSintatico(string mensagem); //Debug do Sintatico
string pegaTipo(bool lado);

///SEMANTICO
typedef struct SIMBOLO{
    string simbolo = "@"; //Nome do simbolo
    string classe = "@"; //Classe do simbolo, pode ser(const,var,type,funcao)
    string tipo = "@"; //Tipo do simbolo, pode ser(integer,real,array,record, identificador) para classe const(alfanumerico,numero)
    string escopo = "@"; //"Lugar" onde o simbolo foi declarado
    int quantParametros = -1; //Quantidade de parâmetros de uma rotina ou tamanho de um array
    string tipoArray = "@"; //Se tipo for array contém o tipo desse array(tudo de tipo)
}Simbolo;

Simbolo tabela_simbolos[1000]; //Número máximo de simbolos é 1000
int sim=0; //Indice da tabela de Simbolos
int quantParametros=0; //quantidade de parametros que depois será atribuida a algum simbolo do tipo função ou procedure
stack <string> escopoAtual; //pilha que contem os escopos
Simbolo simboloAtual; //simbolo atual para validação
vector <Simbolo> auxParametros; //vetor de simbolos que recebe os parametros lidos na chamada de uma função ou procedure
int posSimboloAtual=0; //indice da função ou procedure na tabela de simbolos
Simbolo simboloFuncAtual; //simbolo da chamada de função ou procedure
string tipo_esq, tipo_dir; //variáveis que vão conter o tipo do lado esquerdo da atribuição e do lado direito da mesma

///FUNÇÕES
void debugSintatico(string mensagem){
    //cout << mensagem << endl; //Descomente para ver o debug do Analisador Sintático
}

void op_logico(void){
    if(lista_tokens[atual].codigo!=3){ //operador_logico
        erro();
    }else{
        debugSintatico("op_logico");
        atual++;
    }
}

void op_matematico(void){
    if(lista_tokens[atual].codigo!=5){ //operador_matematico
        erro();
    }else{
        debugSintatico("operador_matematico");
        atual++;
    }
}
///Contém operações do analisador semântico
void identificador(void){
    if(lista_tokens[atual].codigo!=2){ //identificador
        erro();
    }else{
        debugSintatico("identificador");
        semantico(1); // Analisador semantico para as 2 primeiras regras
        atual++;
    }
}

void numero(void){
    if(lista_tokens[atual].codigo!=1){ //numero
        erro();
    }else{
        debugSintatico("numero");
        atual++;
    }
}
///Contém operações do analisador semântico
void tipo_dado(void){
    if(lista_tokens[atual].codigo==26){//integer
        debugSintatico("integer");
        atual++;
    }
    else if(lista_tokens[atual].codigo==27){//real
        debugSintatico("real");
        atual++;
    }
    else if(lista_tokens[atual].codigo==28){//array
        tabela_simbolos[sim].tipo = lista_tokens[atual].word; //SEMANTICO. Preenche campo tipo com "array"
        atual++; //prox token
        debugSintatico("array");
        if(lista_tokens[atual].codigo==12){//[
            atual++; //prox token
            debugSintatico("[");
            stringstream s2n(lista_tokens[atual].word); //Converte String para numero
            s2n >> tabela_simbolos[sim].quantParametros; //SEMANTICO. Tamanho do array
            numero();
            if(lista_tokens[atual].codigo==13){//]
                debugSintatico("]");
                atual++; //prox token
                if(lista_tokens[atual].codigo==29){//of
                    debugSintatico("of");
                    atual++; //prox token
                    tabela_simbolos[sim].tipoArray = lista_tokens[atual].word; //SEMANTICO. Preenche campo tipoArray
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
        tabela_simbolos[sim].tipo = lista_tokens[atual].word; //SEMANTICO. Preenche campo tipo com "record"
        escopoAtual.push(tabela_simbolos[sim].simbolo); //SEMANTICO. escopoAtual é o record
        debugSintatico("record");
        atual++; //prox token
        quantParametros=0;//SEMANTICO
        variaveis();
        for(int i=0;i<=sim;i++){ //SEMANTICO. Procura record na tabela onde quantPar==-1 e atribui a quantidade de parametros correta
            if(tabela_simbolos[i].simbolo==escopoAtual.top() && tabela_simbolos[i].quantParametros==-1)
                tabela_simbolos[i].quantParametros = quantParametros;//SEMANTICO
        }
        quantParametros=0;//SEMANTICO
        if(lista_tokens[atual].codigo==22){ //end
            debugSintatico("end");
            if(escopoAtual.size()>0)
                escopoAtual.pop(); //SEMANTICO. Encerrado o record o escopoAtual volta a ser global
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

void variaveis(void){
    ///<VARIAVEIS> -> <VARIAVEL> <VARIAVEIS_2>
    ///<VARIAVEIS> -> E
    ///<VARIAVEIS_2> -> ; <VARIAVEIS>
    ///<VARIAVEIS_2> -> E
    if(lista_tokens[atual].codigo==2){ //identificador
        variavel();
        variaveis_2();
    }else{
        debugSintatico("E");
    }
}

void variaveis_2(void){
    if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
        debugSintatico(";Variaveis_2");
        atual++; //prox token;
        variaveis();
    }else{
        debugSintatico("E"); //vazio
    }
}
///Contém operações do analisador semântico
void variavel(void){
    lista_id();
    if(lista_tokens[atual].codigo==7){ //dois_pontos
        debugSintatico(":Variavel");
        atual++; //prox token
        for(int i=0;i<=sim;i++){ //SEMANTICO. Depois de declarar uma lista de variáveis, acha elas na tabela e preenche o campo tipo
            if(tabela_simbolos[i].classe=="var" && tabela_simbolos[i].tipo=="@")
                tabela_simbolos[i].tipo = lista_tokens[atual].word;
        }
        tipo_dado();
    }else{
        erro();
    }
}
///Contém operações do analisador semântico
void lista_id(void){
    quantParametros++;//SEMANTICO. Incrementa quantidade de parametros
    sim++; //SEMANTICO. Incrementa indice da tabela de simbolos
    tabela_simbolos[sim].simbolo = lista_tokens[atual].word; //SEMANTICO. Preenche campo simbolo
    tabela_simbolos[sim].escopo = escopoAtual.top(); //SEMANTICO. Preenche campo escopo
    tabela_simbolos[sim].classe = "var"; //SEMANTICO. Preenche campo classe
    identificador();
    lista_id_2();
}

void lista_id_2(void){
    if(lista_tokens[atual].codigo==6){ //virgula
        debugSintatico(",Lista_id_2");
        atual++; //prox token
        lista_id();
    }else{
        debugSintatico("E"); //vazio
    }
}

void constantes(void){
    constante();
    constantes_2();
}

void constantes_2(void){
    ///<CONSTANTES_2> -> <CONSTANTES>
    ///<CONSTANTES_2> -> E
    if(lista_tokens[atual].codigo==2){ //identificador
        constantes();
    }else{
        debugSintatico("E"); //vazio
    }
}
///Contém operações do analisador semântico
void constante(void){
    sim++; //SEMANTICO. Incrementa indice da tabela de simbolos
    tabela_simbolos[sim].simbolo = lista_tokens[atual].word; //SEMANTICO. Preenche campo simbolo
    tabela_simbolos[sim].classe = "const"; //SEMANTICO. Preenche campo classe
    tabela_simbolos[sim].escopo = escopoAtual.top(); //SEMANTICO. Preenche campo escopo

    identificador();
    if(lista_tokens[atual].word=="="){
        debugSintatico("=Constante");
        atual++; //prox token
        const_valor();
        if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
            atual++;
            debugSintatico(";Constante");
        }else{
            erro();
        }
    }else{
        erro();
    }
}
///Contém operações do analisador semântico
void const_valor(void){
    if(lista_tokens[atual].codigo==14){ //alfanumerico
        atual++;
        debugSintatico("alfanumerico");
        if(tabela_simbolos[sim].classe=="const")
            tabela_simbolos[sim].tipo = "alfanumerico"; //SEMANTICO
    }
    else{
        if(tabela_simbolos[sim].classe=="const"){
            /*Gambiarra para trocar tipo numero para real ou integer*/
            stringstream s2n(lista_tokens[atual].word); //Converte String para numero
            float auxFloat;
            int auxInt;
            s2n >> auxFloat;
            auxInt = auxFloat;
            if(auxFloat==auxInt)
                tabela_simbolos[sim].tipo = "integer";
            else
                tabela_simbolos[sim].tipo = "real";
            /*Fim gambiarra*/
        }
        exp_matematica();
    }
}

void exp_matematica(void){
    if(lista_tokens[atual].codigo==10){ //abre_parentese
        debugSintatico("( Exp_matematica");
        atual++; //prox token
        nome_numero();
        op_matematico();
        exp_matematica();
        if(lista_tokens[atual].codigo==11){ //fecha_parentese
            atual++;
            debugSintatico(") Exp_matematica");
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
        debugSintatico("E"); //vazio
    }
}
///Contém operações do analisador semântico
void nome_numero(void){
    if(lista_tokens[atual-1].word=="(" || lista_tokens[atual-1].word==","){ //regra nome_numero está chamando uma função
        if(simboloFuncAtual.simbolo=="@"){ //pegar o nome da função que está sendo chamada
            simboloFuncAtual = simboloAtual;
            for(int i=0;i<=sim;i++){ //for para achar a função na tabela e pegar o indice dela
                if(tabela_simbolos[i].simbolo!="@"){
                    if(tabela_simbolos[i].simbolo==simboloFuncAtual.simbolo)
                        posSimboloAtual=i;
                }
                else
                    break;
            }
        }
        if(lista_tokens[atual].codigo==2){ //identificador
            identificador();
            auxParametros.push_back(simboloAtual);
            nome_3();
        }else{
            Simbolo auxSimbolo;
            auxSimbolo.simbolo = lista_tokens[atual].word;
            /*Gambiarra para trocar tipo numero para real ou integer*/
            stringstream s2n(lista_tokens[atual].word); //Converte String para numero
            float auxFloat;
            int auxInt;
            s2n >> auxFloat;
            auxInt = auxFloat;
            if(auxFloat==auxInt)
                auxSimbolo.tipo = "integer";
            else
                auxSimbolo.tipo = "real";
            /*Fim gambiarra*/
            auxParametros.push_back(auxSimbolo); //adiciona simbolo do tipo integer ou real como parametro
            numero();
        }
    }else{ //regra nome_numero normal
        if(lista_tokens[atual].codigo==2){ //identificador
            identificador();
            nome_3();
        }else{
            numero();
        }
    }
}
///Contém operações do analisador semântico
void nome_3(void){
    if(lista_tokens[atual].codigo==10){ //abre_parentese
        debugSintatico("( Nome_3");
        semantico(3); //SEMANTICO verificação regra 4 do semantico
        atual++; //prox token
        parametro();
        if(lista_tokens[atual].codigo==11){ //fecha_parentese
            semantico(5); //SEMANTICO verificação regra 7 do semantico
            atual++;
            debugSintatico(") Nome_3");
        }else{
            erro();
        }
    }else{
        nome_2();
    }
}
///Contém operações do analisador semântico
void nome_2(void){
    if(lista_tokens[atual].codigo==9){ //ponto
        for(int i=0;i<=sim;i++){ //SEMANTICO. Procura na tabela de simbolos o identificador que usa o '.'
            if(tabela_simbolos[i].simbolo==lista_tokens[atual-1].word){ //achei
                if(tabela_simbolos[i].escopo==escopoAtual.top()){
                    escopoAtual.push(tabela_simbolos[i].tipo); //O escopoAtual será o tipo desse identificador
                    break;
                }
            }
        }
        semantico(4); //SEMANTICO. Validação regra 5 do semantico
        debugSintatico(".");
        atual++; //prox token
        nome();
        if(escopoAtual.size()>0) //SEMANTICO. Ao terminar o acesso ao atributo pelo '.' o escopoAtual volta ao anterior
            escopoAtual.pop();
    }
    else if(lista_tokens[atual].codigo==12){ //abre_colchete
        debugSintatico("[ Nome_2");
        semantico(2); //SEMANTICO
        atual++; //prox token
        nome_numero();
        if(lista_tokens[atual].codigo==13){ //fecha_colchete
            atual++;
            debugSintatico("] Nome_2");
        }else{
            erro();
        }
    }
    else{
        debugSintatico("E"); //vazio
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
        debugSintatico(";Tipos_2");
        atual++;
        tipos();
    }else{
        debugSintatico("E"); //vazio
    }
}

void lista_param(void){
    nome_numero();
    lista_param_2();
}

void lista_param_2(void){
    if(lista_tokens[atual].codigo==6){ //virgula
        debugSintatico(",Lista_param2");
        atual++;
        lista_param();
    }else{
        debugSintatico("E");
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
        debugSintatico("E");
    }
}

void parametro(void){
    ///<PARAMETRO> -> <LISTA_PARAM>
    ///<PARAMETRO> -> E
    if(lista_tokens[atual].codigo==1 || lista_tokens[atual].codigo==2){ //numero ou identificador
        lista_param();
    }else{
        debugSintatico("E");
    }
}

void else_1(void){
    if(lista_tokens[atual].codigo==38){ //else
        debugSintatico("else");
        atual++;
        bloco();
    }else{
        debugSintatico("E");
    }
}

///Contém operações do analisador semântico
void comando(void){
    if(lista_tokens[atual].codigo==33){ //while
        debugSintatico("while");
        atual++;
        exp_logica();
        bloco();
    }else if(lista_tokens[atual].codigo==34){ //if
        debugSintatico("if");
        atual++;
        exp_logica();
        if(lista_tokens[atual].codigo==35){ //then
            debugSintatico("then");
            atual++;
            bloco();
            else_1();
        }else{
            erro();
        }
    }else if(lista_tokens[atual].codigo==36){ //write
        debugSintatico("write");
        atual++;
        const_valor();
    }else if(lista_tokens[atual].codigo==37){ //read
        debugSintatico("read");
        atual++;
        nome();
    }
    else{
        nome();
        if(lista_tokens[atual].codigo==8){ //atribuicao
            debugSintatico(":=");
            tipo_esq = pegaTipo(true); //Pega o tipo antes da atribuição
            atual++;
            tipo_dir = pegaTipo(false); //Pega o tipo depois da atribuição
            exp_matematica();
            semantico(6);  //Validação regra 8 do semântico
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
            debugSintatico(";Comandos");
            atual++;
            comandos();
        }else{
            erro();
        }
    }else{
        debugSintatico("E");
    }
}

void bloco(void){
    if(lista_tokens[atual].codigo==21){ //begin
        debugSintatico("beginBloco");
        atual++;
        comandos();
        if(lista_tokens[atual].codigo==22){ //end
            atual++;
            debugSintatico("endBloco");
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
///Contém operações do analisador semântico
void nome_rotina(void){
    tabela_simbolos[sim].simbolo = lista_tokens[atual].word;//SEMANTICO. Preenche campo simbolo
    tabela_simbolos[sim].escopo = escopoAtual.top();//SEMANTICO. Preenche campo escopo
    identificador();
    if(lista_tokens[atual].codigo==10){ //abre_parentese
        debugSintatico("( Nome_rotina");
        escopoAtual.push(tabela_simbolos[sim].simbolo);//SEMANTICO. Temos um novo escopo
        atual++;
        quantParametros=0;//SEMANTICO
        variaveis();
        for(int i=0;i<=sim;i++){ //SEMANTICO. Procura rotina na tabela e atribui a quantidade de parametros correta
            if(tabela_simbolos[i].simbolo==escopoAtual.top() && tabela_simbolos[i].quantParametros==-1)
                tabela_simbolos[i].quantParametros = quantParametros;//SEMANTICO
        }
        quantParametros=0;//SEMANTICO
        if(lista_tokens[atual].codigo==11){ //fecha_parentese
            atual++;
            debugSintatico(") Nome_rotina");
        }else{
            erro();
        }
    }else{
        erro();
    }
}
///Contém operações do analisador semântico
void procedimento(void){
    sim++; //SEMANTICO. Incrementa indice da tabela de simbolos
    if(lista_tokens[atual].codigo==32){ //procedure
        debugSintatico("procedure");
        tabela_simbolos[sim].classe = "procedure"; //SEMANTICO. Preenche campo classe com "procedure"
        atual++;
        nome_rotina();
        bloco_rotina();
    }else{
        erro();
    }
    if(escopoAtual.size()>0)
        escopoAtual.pop(); //SEMANTICO. Procedimento acabou, o escopo retorna para o escopo anterior
}
///Contém operações do analisador semântico
void funcao(void){
    sim++; //SEMANTICO. Incrementa indice da tabela de simbolos
    if(lista_tokens[atual].codigo==31){ //function
        debugSintatico("function");
        tabela_simbolos[sim].classe = "funcao"; //SEMANTICO. Preenche campo classe com "funcao"
        atual++;
        nome_rotina();
        if(lista_tokens[atual].codigo==7){ //dois_pontos
            debugSintatico(":Funcao");
            atual++;
            tipo_dado();
            for(int i=0;i<=sim;i++){ //SEMANTICO. Procura a funcao que foi declarada na tabela e preenche o campo tipo
                if(tabela_simbolos[i].classe=="funcao" && tabela_simbolos[i].tipo=="@")
                    tabela_simbolos[i].tipo = lista_tokens[atual-1].word; //SEMANTICO
            }
            bloco_rotina();
        }else{
            erro();
        }
    }else{
        erro();
    }
    if(escopoAtual.size()>0)
        escopoAtual.pop(); //SEMANTICO. Função acabou, o escopo retorna para o escopo anterior
}

void def_variaveis(void){
    if(lista_tokens[atual].codigo==25){ //var
        debugSintatico("var");
        atual++;
        variaveis();
    }else{
        debugSintatico("E");
    }
}

void def_tipos(void){
    if(lista_tokens[atual].codigo==24){ //type
        debugSintatico("type");
        atual++;
        tipos();
    }else{
        debugSintatico("E");
    }
}

void def_constantes(void){
    if(lista_tokens[atual].codigo==23){ //const
        debugSintatico("const");
        atual++;
        constantes();
    }else{
        debugSintatico("E");
    }
}
///Contém operações do analisador semântico
void tipo(void){
    sim++; //SEMANTICO. Incrementa indice da tabela de simbolos
    tabela_simbolos[sim].simbolo = lista_tokens[atual].word; //SEMANTICO. Preenche campo simbolo
    tabela_simbolos[sim].classe = "type"; //SEMANTICO. Preenche campo classe
    tabela_simbolos[sim].escopo = escopoAtual.top(); //SEMANTICO. Preenche campo escopo

    identificador();
    if(lista_tokens[atual].word=="="){
        debugSintatico("=Tipo");
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
///Contém operações do analisador semântico
void programa(void){
    if(lista_tokens[atual].codigo==20){ //program
        debugSintatico("program");
        atual++;
        tabela_simbolos[sim].simbolo = lista_tokens[atual].word; //SEMANTICO
        tabela_simbolos[sim].classe = "program"; //SEMANTICO
        tabela_simbolos[sim].escopo = escopoAtual.top(); //SEMANTICO
        identificador();
        if(lista_tokens[atual].codigo==4){ //ponto_e_virgula
            debugSintatico(";Programa");
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
        debugSintatico("E");
    }
}

void corpo(void){
    if(lista_tokens[atual].codigo==21){ //begin
        atual++;
        debugSintatico("beginCorpo");
        comandos();
        if(lista_tokens[atual].codigo==22){ //end
            atual++;
            debugSintatico("endCorpo");
        }else{
            erro();
        }
    }else{
        declaracoes();
        if(lista_tokens[atual].codigo==21){ //begin
            atual++;
            debugSintatico("beginCorpo");
            comandos();
            if(lista_tokens[atual].codigo==22){ //end
                atual++;
                debugSintatico("endCorpo");
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

void erroSemantico(int erro){
    cout << endl;
    cout << "**************" << endl;
    cout << "ERRO SEMANTICO" << endl;
    cout << "token " << lista_tokens[atual].word << endl;
    cout << "linha " << lista_tokens[atual].linha << endl;
    switch(erro){
        case 1: cout << "identificador ja declarado nesse escopo" << endl;
        break;
        case 2: cout << "identificador nao declarado" << endl;
        break;
        case 3: cout << "identificador precisa ser um array para usar []" << endl;
        break;
        case 4: cout << "identificador precisa ser uma funcao ou procedure para receber parametros" << endl;
        break;
        case 5: cout << "identificador precisa ser um record para acessar atributos via '.'" << endl;
        break;
        case 6: cout << "quantidade invalida de parametros" << endl;
        break;
        case 7: cout << "tipo do parametro diferente do declarado" << endl;
        break;
        case 8: cout << "tipos diferentes da atribuicao" << endl;
        break;
    }
    cout << "**************" << endl;
    //exit(-1);
}

void semantico(int x){
    Token tokenAtual;
    bool declarado=false;
    set<string> escopos;
    bool ok=false;
    string auxTipo;
    switch(x){
    case 1: //Verifica se identificador foi declarado e se existe identificadores com nomes iguais no mesmo escopo
        tokenAtual = lista_tokens[atual];
        //cout << "\ntokenAtual " << tokenAtual.word << " escopo " << escopoAtual.top() << endl;
        //cout << "--simbolos--" << endl;
        for(int i=0;i<1000;i++){
            if(tabela_simbolos[i].simbolo!="@"){
                //cout << "[" << tabela_simbolos[i].simbolo << "] ";
                if(tokenAtual.word==tabela_simbolos[i].simbolo){ //identificador declarado
                    if(tabela_simbolos[i].escopo==escopoAtual.top()){ //identificador declarado no escopo atual
                        simboloAtual=tabela_simbolos[i];
                        declarado=true;
                    }
                    else if(tabela_simbolos[i].escopo=="global"){ //identificador declarado globalmente
                        simboloAtual=tabela_simbolos[i];
                        declarado=true;
                    }
                    else //foi declarado localmente e está sendo usado fora do escopo
                        declarado=false;
                    if(escopos.count(tabela_simbolos[i].escopo)==0){ //primeira ocorrencia em um escopo
                        escopos.insert(tabela_simbolos[i].escopo);
                    }else{ //mesmo simbolo no mesmo escopo
                        erroSemantico(1);
                    }
                }
            }else{ //se achei simbolo==@ então já olhei a tabela de simbolos toda
                break;
            }
        }
        //cout << endl;
        if(!declarado){ //identificador não declarado
            erroSemantico(2);
        }
        escopos.clear();
    break;
    case 2: //Validação para só identificador do tipo array poder usar o '[]'
        cout << "\n--Log Regra Semantica 3--\n";
        cout << "SimboloAtual = " << simboloAtual.simbolo << endl;
        if(simboloAtual.tipo=="array"){ //se o tipo dele for "array" tudo certo
            ok=true;
            break;
        }else{
            auxTipo = simboloAtual.tipo;
            for(int i=0;i<1000;i++){ //se o tipo não for "array" verifica se trata-se de um type
                if(tabela_simbolos[i].simbolo!="@"){
                    if(tabela_simbolos[i].simbolo == auxTipo){ //acha o type na tabela
                        if(tabela_simbolos[i].tipo=="array"){ //se o tipo do type é "array" tudo certo
                            ok=true;
                            break;
                        }
                    }
                }else{ //se achei simbolo==@ então já olhei a tabela de simbolos toda
                    break;
                }
            }
        }
        if(ok) break; //tudo certo
        else erroSemantico(3); //não é array
    break;
    case 3: //Validação para só identificador do tipo funcao ou procedure poder usar '()'
        cout << "\n--Log Regra Semantica 4--\n";
        cout << "SimboloAtual = " << simboloAtual.simbolo << endl;
        if(simboloAtual.classe!="funcao" && simboloAtual.classe!="procedure"  )
            erroSemantico(4); //não é function nem procedure
    break;
    case 4: //Validação para só identificador do tipo record poder usar o '.'
    cout << "\n--Log Regra Semantica 5--\n";
    cout << "SimboloAtual = " << simboloAtual.simbolo << endl;
    for(int i=0;i<1000;i++){ //percorro a tabela de simbolos
        if(tabela_simbolos[i].simbolo!="@"){
            if(tabela_simbolos[i].simbolo==simboloAtual.tipo){ //achei o nome do tipo na tabela
                if(tabela_simbolos[i].tipo!="record") //Se não for um record da erro
                    erroSemantico(5); //não é record
                else //É record tudo certo
                    break;
            }
        }
        else{ //se achei simbolo==@ então já olhei a tabela de simbolos toda
            erroSemantico(5); //não é record
            break;
        }
    }
    break;
    case 5: //Validação chamada de uma função, a quantidade e tipos dos parâmetros devem ser iguais aos dos argumentos
    /*
    simboloFuncAtual => é a função que está sendo chamada
    auxParametros => é um vector que contem os simbolos lidos depois de '(' até ')'
    posSimboloAtual => é o indice da função na tabela de simbolos, conforme incrementa esse indice acessamos os parametros da
        função em questão, caso essa tenha parametros
    */
    cout << "\n--Log Regra Semantica 7--\n";
    cout << "quantParametros = " << simboloFuncAtual.quantParametros;
    cout << " | auxParametros.size() = " << auxParametros.size() << endl;
    if(simboloFuncAtual.quantParametros==auxParametros.size()){
        if(auxParametros.size()>0){ //precisa disso para permitir funções com 0 parametros
            cout << "posSimboloAtual = " << posSimboloAtual << endl;
            for(int i=1;i<=simboloFuncAtual.quantParametros;i++){
                cout << "[" << posSimboloAtual+i << "] " << tabela_simbolos[posSimboloAtual+i].simbolo  << " " << tabela_simbolos[posSimboloAtual+i].tipo << " ESPERADO" << endl;
                cout << "[" << i-1 << "] "  << auxParametros[i-1].simbolo << " " << auxParametros[i-1].tipo << " ACHADO" << endl;
                if(tabela_simbolos[posSimboloAtual+i].tipo!=auxParametros[i-1].tipo){ //tipo declarado diferente de tipo lido
                    erroSemantico(7);
                    //break;
                }
            }
        }
    }else{ //quantidade de parametros errada
        erroSemantico(6);
    }
    /*Limpeza variáveis globais*/
    auxParametros.clear();
    simboloFuncAtual.simbolo="@";
    simboloFuncAtual.quantParametros=0;
    /*Fim*/
    break;
    case 6:
    cout << "\n--Log Regra Semantica 8--\n";
    cout << "Tipo esq = " << tipo_esq << "\nTipo dir = " << tipo_dir << endl;
    if(tipo_esq!=tipo_dir)
        erroSemantico(8);
    break;
    tipo_esq = "@";
    tipo_dir = "@";
    break;
    }//fecha switch
}

string pegaTipo(bool lado){
    Token tokenAtual;
    tokenAtual = lista_tokens[atual-1];
    string tipo="null";
    if(lado){ //esquerdo
        //Analise feita de trás pra frente
        if(tokenAtual.word=="]"){ //Se tem colchetes é um array
            for(int i=0;i<1000;i++){
                if(tabela_simbolos[i].simbolo!="@"){
                    if(simboloAtual.tipo==tabela_simbolos[i].simbolo){
                        if(tabela_simbolos[i].tipo=="array")
                            tipo = tabela_simbolos[i].tipoArray;
                        else //é um type
                            tipo = tabela_simbolos[i].tipo;
                    }
                }else{ //acabou de percorrer a tabela de simbolos
                    break;
                }
            }
        }else
            tipo = simboloAtual.tipo;
    }else{ //direita
        vector<Token> tokensDireita;
        int i=atual;
        while(1){
            if(lista_tokens[i].word==";" || lista_tokens[i].word=="else"){
                break;
            }else{
                tokensDireita.push_back(lista_tokens[i]);
                i++;
            }
        }
        /*DEBUG*/
        cout << "\nLista tokens da direita: ";
        for(int i=0;i<tokensDireita.size();i++){
            cout << "[" << tokensDireita[i].word << "," << tokensDireita[i].codigo << "] ";
        }
        cout << endl;
        /*FIM_DEBUG*/
        i=0; //Só o primeiro token será analisado e este irá determinar o tipo do lado direito
            if(tokensDireita[i].codigo==1){ //numero
                /*Gambiarra para trocar tipo numero para real ou integer*/
                stringstream s2n(tokensDireita[i].word); //Converte String para numero
                float auxFloat;
                int auxInt;
                s2n >> auxFloat;
                auxInt = auxFloat;
                if(auxFloat==auxInt)
                    tipo = "integer";
                else
                    tipo = "real";
                /*Fim gambiarra*/
            }else{ //identificador
                for(int j=0;j<1000;j++){
                    if(tabela_simbolos[j].simbolo!="@"){
                        //Procura token na tabela de simbolos. Há também a verificação do escopo para garantir que vamos achar o simbolo certo.
                        if(tokensDireita[i].word==tabela_simbolos[j].simbolo && (tabela_simbolos[j].escopo==escopoAtual.top()||tabela_simbolos[j].escopo=="global")){
                            if(tabela_simbolos[j].classe=="funcao"){
                                if(tokensDireita[i+1].codigo==10) //ABRE_PARENTESE
                                    tipo = tabela_simbolos[j].tipo;
                                else
                                    tipo = "funcao";
                                break;
                            }else{
                                if(tokensDireita[i+1].codigo==12){ //ABRE_COLCHETE
                                    if(tabela_simbolos[j].tipo=="array")
                                        tipo = tabela_simbolos[j].tipoArray;
                                    else{
                                        for(int k=0;k<1000;k++){ //se o tipo não for "array" verifica se trata-se de um type
                                            if(tabela_simbolos[k].simbolo!="@"){
                                                if(tabela_simbolos[k].simbolo == tabela_simbolos[j].tipo){ //acha o type na tabela
                                                    if(tabela_simbolos[k].tipo=="array"){ //se o tipo do type é "array" pega o tipoArray
                                                        tipo = tabela_simbolos[k].tipoArray;
                                                        return tipo;
                                                    }
                                                }
                                            }else{ //acabou de percorrer a tabela de simbolos
                                                break;
                                            }
                                        }
                                    }
                                }else if(tokensDireita[i+1].codigo==9){ //PONTO
                                    for(int j=0;j<1000;j++){
                                        if(tabela_simbolos[j].simbolo!="@"){
                                        //Procura token na tabela de simbolos. Há também a verificação do escopo para garantir que vamos achar o simbolo certo.
                                            if(tokensDireita[i].word==tabela_simbolos[j].simbolo && (tabela_simbolos[j].escopo==escopoAtual.top()||tabela_simbolos[j].escopo=="global")){
                                                for(int k=0;k<1000;k++){
                                                    if(tabela_simbolos[k].simbolo!="@"){
                                                        if(tokensDireita[i+2].word==tabela_simbolos[k].simbolo && tabela_simbolos[k].escopo==tabela_simbolos[j].tipo){
                                                            tipo = tabela_simbolos[k].tipo;
                                                            return tipo;
                                                        }
                                                    }else{ //acabou de percorrer a tabela de simbolos
                                                        break;
                                                    }
                                                }
                                            }
                                        }else{ //acabou de percorrer a tabela de simbolos
                                            break;
                                        }
                                    }
                                }else{ //Não tem colchetes nem ponto então só retorna o tipo
                                    tipo = tabela_simbolos[j].tipo;
                                }
                            }
                        }
                    }else{ //acabou de percorrer a tabela de simbolos
                        break;
                    }
                }
            }
        //}
    }
    return tipo;
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
    escopoAtual.push("global");
    programa();
    cout << "\n" << "**Tabela Simbolos**" << "\n";
    cout << "[i] simbolo|classe|tipo|escopo|quantParametros|tipoArray" << "\n";
    for(int i=0;i<1000;i++){
        if(tabela_simbolos[i].simbolo!="@")
        cout << "[" << i << "] " << tabela_simbolos[i].simbolo << "|" << tabela_simbolos[i].classe << "|" << tabela_simbolos[i].tipo <<
        "|" << tabela_simbolos[i].escopo << "|" << tabela_simbolos[i].quantParametros << "|" << tabela_simbolos[i].tipoArray << endl;
    }
    return 0;
}

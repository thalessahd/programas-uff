/// Tratar aspas (Um token so)
/// Tratar := como um token
/// Separar quando começa com numero

#include <bits/stdc++.h>

#define NUMERO 1
#define IDENTIFICADOR 2
#define OPERADOR_LOGICO 3
#define PONTO_E_VIRGULA 4
#define OPERADOR_MATEMATICO 5
#define VIRGULA 6
#define DOIS_PONTOS 7
#define ATRIBUICAO 8
#define PONTO 9
#define ABRE_PARENTESE 10
#define FECHA_PARENTESE 11
#define ABRE_COLCHETE 12
#define FECHA_COLCHETE 13
#define ALFANUMERICO 14
#define ERRO 404

using namespace std;

string reservadas[] = {"program","begin","end","const","type","var","integer","real","array","of","record",
"function","procedure","while","if","then","write","read","else"};

vector<string> palavras_reservadas(reservadas,reservadas + sizeof(reservadas)/sizeof(string));

typedef struct Token{
        int linha;
        string word;
        int codigo;
}token;

string codigoToken2nomeToken(int codigo){
    switch(codigo){
        case 1: return "NUMERO";
        break;
        case 2: return "IDENTIFICADOR";
        break;
        case 3: return "OPERADOR_LOGICO";
        break;
        case 4: return "PONTO_E_VIRGULA";
        break;
        case 5: return "OPERADOR_MATEMATICO";
        break;
        case 6: return "VIRGULA";
        break;
        case 7: return "DOIS_PONTOS";
        break;
        case 8: return "ATRIBUICAO";
        break;
        case 9: return "PONTO";
        break;
        case 10: return "ABRE_PARENTESE";
        break;
        case 11: return "FECHA_PARENTESE";
        break;
        case 12: return "ABRE_COLCHETE";
        break;
        case 13: return "FECHA_COLCHETE";
        break;
        case 14: return "ALFANUMERICO";
        break;
        case 20: return "PROGRAM";
        break;
        case 21: return "BEGIN";
        break;
        case 22: return "END";
        break;
        case 23: return "CONST";
        break;
        case 24: return "TYPE";
        break;
        case 25: return "VAR";
        break;
        case 26: return "INTEGER";
        break;
        case 27: return "REAL";
        break;
        case 28: return "ARRAY";
        break;
        case 29: return "OF";
        break;
        case 30: return "RECORD";
        break;
        case 31: return "FUNCTION";
        break;
        case 32: return "PROCEDURE";
        break;
        case 33: return "WHILE";
        break;
        case 34: return "IF";
        break;
        case 35: return "THEN";
        break;
        case 36: return "WRITE";
        break;
        case 37: return "READ";
        break;
        case 38: return "ELSE";
        break;
        case 404: return "ERRO";
    }
}

int verificaReservada(string s, vector<string> v){
	for(unsigned int i=0;i<v.size();i++){
		if(s==v[i])
			return i+20;
	}
	return -1;
}

int classifica_token(string token){
	char c;
	int reservada;

    c = token[0];
    if(isalnum(c)){ //alphanumerico
        if(isalpha(c)){ //letra
            reservada = verificaReservada(token,palavras_reservadas);
            if(reservada!=-1){
                return reservada; //palavra reservada
            }
            else{
                return IDENTIFICADOR; //identificador
            }
        }
        else if(isdigit(c)){ //digito
            bool segundo_ponto = false;
            for(int i=1;i<token.size();i++){
                c = token[i];
                if(!isdigit(c)){
                    if(c=='.'){
                        if(segundo_ponto)
                            return ERRO;
                        else
                            segundo_ponto = true;
                    }
                }
            }
            return NUMERO;
        }
    }
    else{ //caractere especial
        if(c=='=' || c=='>' || c=='<' || c=='!')
            return OPERADOR_LOGICO;
        else if(c=='+' || c=='-' || c=='*' || c=='/')
            return OPERADOR_MATEMATICO;
        else if(token==":=")
            return ATRIBUICAO;
        else if(c==';')
            return PONTO_E_VIRGULA;
        else if(c==',')
            return VIRGULA;
        else if(c==':')
            return DOIS_PONTOS;
        else if(c=='.')
            return PONTO;
        else if(c=='(')
            return ABRE_PARENTESE;
        else if(c==')')
            return FECHA_PARENTESE;
        else if(c=='[')
            return ABRE_COLCHETE;
        else if(c==']')
            return FECHA_COLCHETE;
        else if(c=='"' && token[token.size()-1]=='"')
            return ALFANUMERICO;
        else
            return ERRO;
    }
}

vector<string> separaPalavras(string linha){
    vector<string> palavras;
    string palavra;
    string base;
    char c;
    int gravou;
    int dup=0;
    int pont=0;
    for(int i=0;i<linha.size();i++)
    {
        gravou=0;
        c=linha[i];
        if(palavra[0]==':'&&c=='='){ palavra+=c; palavras.push_back(palavra); palavra=base; dup=1;}
            else if(palavra[0]=='.'&&isdigit(c)){palavra+=c;}
                else if(palavra[0]==':'&&c!='=') {palavras.push_back(palavra); palavra=base;}
        if(c!='='&& c!=39 &&c!='\r'&&(!isalpha(palavra[0])||c!='.')&&c!=','&&c!=9&& c!=';' && c!='[' && c!=']' && c!='(' && c!=')' && c!='\n' &&c !=32&& c!='"'&& c!=':'&& c!='>'&& c!='<'&& c!='!'&& c!='+'&& c!='-'&& c!='*'&& c!='/'&&c!='{'&&c!='}' )
        {
            palavra+=c;
        }else
        {
            if(palavra.size()>0)
            {
                palavras.push_back(palavra);
                gravou=1;
                palavra=base;
            }
            if(c!='\n'&&c!='\r'&&dup!=1&&c!=0&&c!=9)
            {
                palavra=c;
                if(c!=':')
                {
                palavras.push_back(palavra);
                gravou=1;
                palavra=base;
                }
            }
            dup=0;
        }
        if(!gravou && i==(linha.size()-1))
        {
            palavras.push_back(palavra);
            palavra=base;
        }
    }

    return palavras;
}

void gravaToken(vector<token>*t,string palavra, int linha){
    if(palavra.size()>0){
        token tk;
        tk.word=palavra;
        tk.linha=linha;
        tk.codigo=classifica_token(palavra); //Thalessa adicionou
        t->push_back(tk);
    }
}

int tokenizador(vector<token>* t, char* nomearq){
    string base;
    token tk;
    ifstream codigo; //arquivo com o codigo
    string buff; // linha sendo analizada no momento
    string aux; // auxiliar
    char cbuff; // char sendo analizado no momento
    int linha; //contar qual linha está o token
    int j=0;
    vector<string> palavras; //palavra sendo analizada
    vector<string> token; // apos a palavra ser analizada, ela será tratada e, quando finalizada, colocada no vetor de tokens;
    ///semaforos
    int comecaComNumero=0;
    int aspas=0;
    int comentario=0;
    int gravou=0;

    codigo.open(nomearq);

    if(codigo.is_open())
    {
        linha=0;
        //cout <<"abriu";
        while(!codigo.eof())
        {
            getline(codigo,buff);
            linha++;//conta qual linha está
            //cout << buff<<endl;
            palavras=separaPalavras(buff); //Separa a linha lida em palavras. Pq não pegar palavras já separadas no arquivo? Pois assim não conseguiria ler os espaços em branco, e daria ruim na hora de ler string
            for(int i=0;i<palavras.size();i++)
            {
                j=0; // uso isso para ler a palavra desde o começo, sem usar um for.
                    if(palavras[i][0]=='"') //Tratamento de aspas para string
                    {
                        aspas=1;
                        while(aspas) // Se achou uma aspas, vai concatenando tudo até encontrar outra
                        {
                            aux+=palavras[i];
                            i++;
                            if(palavras[i][0]=='"') // Quando encontra outra aspas, sai do loop e reseta a variavel auxiliar
                            {
                                aux+="\"";
                                aspas=0; //desativa o sinal pra sair do loop
                                palavras[i]=aux;
                                aux=base;
                            }
                        }
                    }
                    if(palavras[i]=="{") // Tratamento de comentarios. Se achar um '{'
                    {
                            comentario=1; // ele ativa um sinalizador
                            while(comentario)
                            {
                                i++; // e vai ignorando até que
                                if(palavras[i]=="}") // encontre um '}'
                                {
                                    comentario=0; // e sai do loop
                                }
                            }
                    }
                    if(isdigit(palavras[i][j])) //Tratamento de palavras que começam com numero
                    {
                        comecaComNumero=1; // Se comeca com um numero, ativa um sinalizador
                        aux=base; // limpa a variavel aux para evitar problemas
                        while(comecaComNumero) // enquanto tiver numero na palavra
                        {
                            aux+=palavras[i][j];// ele vai juntando os numeros
                            j++;
                            if(!isdigit(palavras[i][j])&&palavras[i][j]!='.'){ // so para quando encontrar algo que nao seja um numero

                                gravaToken(t,aux,linha); // entao ele grava o numero num token
                                comecaComNumero=0; // desativa o sinalizador para sair do loop
                                aux=base; // aquela limpeza basica

                                for(int k=j;k<palavras[i].size();k++) // e percorre o restante da palavra para pegar a string que tem nela
                                {
                                    aux+=palavras[i][k];
                                }
                                gravaToken(t,aux,linha); // e grava essa string
                                gravou=1; // isso aqui é pra nao gravar dnv
                                aux=base; // lipadinha basica de levis
                            }
                        }
                    }
                    if(palavras[i]!=" "&&palavras[i]!="}"&&gravou==0) // se nada foi tratado, nada foi gravado e então ele grava a palavra normalmente
                        gravaToken(t,palavras[i],linha);
                    gravou=0; // desativa os sinais que ja foi gravado para ir para a proxima palavra
            }
        }
    }else{
        cout<<"faiou"; //arquivo falhou ao abrir
    }

}
int main(){

    char entrada[]="exemplo_entrada.txt"; //nome do arquivo

    vector<token> t;

    tokenizador(&t,entrada);
    for(int i=0;i<t.size();i++){
        cout << "["<<t[i].word<<","<<t[i].linha<<"] " << codigoToken2nomeToken(t[i].codigo) <<endl;
    }
    //cout <<t.linha<<t.word;
    ofstream saida;
    saida.open("saida_lexico_sin.txt");
    for(int i=0;i<t.size();i++){
        //saida << t[i].word << " " << t[i].linha << " " << codigoToken2nomeToken(t[i].codigo) << endl;
        saida << t[i].word << endl;
        saida << t[i].linha << endl;
        saida << t[i].codigo << endl;
    }
}

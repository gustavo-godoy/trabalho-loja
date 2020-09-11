#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Coluna{
private:
    string header;
    vector <string> dados;

public:
    Coluna(string headerEntrada){
        header = headerEntrada;
    }
    
    string getHeader() const{
        return header;
    }
        
	// Insert
	Coluna& operator<<(string entrada){
	    dados.push_back(entrada);
	    return *this;
	}
	
	// To Array
	
	size_t toFloat(float *&array){
	    array = new float[dados.size()];
	    for(size_t i=0; i < dados.size(); ++i){
	        array[i] = stof(dados[i]);
	    }
	    
	    return dados.size();
	}
	
	
	
};

class Tabela{
private:
    vector<string> headers;
    vector<Coluna> colunas;
    
public:
    Tabela(vector<string> entradaHeaders){
        headers = entradaHeaders;
        for(auto i = headers.begin(); i != headers.end(); i++){
            colunas.push_back( Coluna(*i) );
        }
    }
    
    Tabela& operator<<(vector<string> linha){
        if (linha.size() != headers.size()) {
            cerr << "Tentado inserir uma linha com " << linha.size() << " colunas em uma tabela de " << headers.size() << " colunas." << endl;
            throw "Erro ao inserir linha: dimensões invalidas!";
        }

        for(size_t i; i < headers.size(); ++i){
            colunas[i] << linha[i];
        }
        
        return *this;
    }
    
    Coluna& operator[](string header){
        for(auto i = colunas.begin(); i != colunas.end(); i++){
            if (header.compare(i->getHeader()) == 0){
                return *i;
            }
        }
        
        cerr << "Tentado acessar uma coluna chamada \""<< header << "\" de uma Tabela que não tem tal coluna." << endl;
        throw "Erro ao acessar uma coluna: coluna inexistente!";
    }
};


vector<string> quebrarLinha(const string linha, char virgula=','){
    vector<string> array;
    string token;
    stringstream stringFile(linha);
    while(getline(stringFile, token, virgula)){
        array.push_back(token);
    }

    return array;
}

Tabela lerCSV(const char* arquivo){
    ifstream arquivoCSV(arquivo);
    string buffer;
    vector<string> linhas;

    while(getline(arquivoCSV, buffer)){
        linhas.push_back(buffer);
    }
            
    Tabela matriz( quebrarLinha(linhas[0]) );
    for(auto i = ++linhas.begin(); i != linhas.end(); ++i){
        matriz << quebrarLinha(*i);
    }

   return matriz; 
}

int main(){
    float * array;
    Tabela arquivo = lerCSV("ativo.csv");
    size_t arraySize = arquivo["Close"].toFloat(array);
    
    for(size_t i=0; i< arraySize; ++i){
        cout << array[i] << endl;
    }
    
    return 0;
}

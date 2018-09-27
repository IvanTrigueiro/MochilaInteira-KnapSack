#include <iostream>
#include <fstream>
using namespace std;

//Utilizando a abordagem Bottom-Up

//Funcao de utilidade para valor maximo entre dois ints
int max(int x, int y){return (x > y)? x : y;}

int KnapSack(int M, int nElementos, int Peso[], int Valor[])
{
    //Tabela a ser preenchida
    int Tabela[nElementos+1][M+1];

    //Iniciando a primeira linha e coluna com 0
    for(int i = 1; i <= nElementos; i++)
        Tabela[i][0] = 0;
    for(int w = 0; w <= M; w++)
        Tabela[0][w] = 0;

    //Construindo a tabela em Bottom-Up
    for(int i = 1; i <= nElementos; i++){
        for(int w = 1; w <= M; w++){
            //Elemento pode fazer parte da solucao
            if(Peso[i - 1] <= w){
                if(Valor[i-1] + Tabela[i-1][w -Peso[i-1]] > Tabela[i-1][w])
                    Tabela[i][w] = max(Valor[i-1] + Tabela[i-1][w -Peso[i-1]], Tabela[i-1][w]);
                else
                    Tabela[i][w] = Tabela[i-1][w];
            }
            else
                Tabela[i][w] = Tabela[i-1][w];
        }
    }
    return Tabela[nElementos][M];
}


int main()
{
    /*
        Teste
        int nElementos = 7;
        int M = 23;
        int Peso[] = {1, 2, 5, 6, 7, 9, 11};
        int Valor[] = {1, 6, 18, 22, 28, 40, 60};
    */
    cout << "Digite 01 para mochila01, 02 para mochila02, 1000 para mochila1000";
    cout << "2500 para mochila2500 ou 5000 para mochila5000:" <<endl;

    string x;
    cin >> x;
    cout<<endl;
    string arquivo = "mochila"+x+".txt";

    ifstream inFile;
    inFile.open(arquivo);
    if(!inFile){
        cerr << "Unable to open file!";
        return 0;
    }
    //numero de elementos
    int nElementos;
    inFile >> nElementos;
    cout<< "Numero de elementos: " << nElementos <<endl;
    //Capacidade maxima da mochila: M
    int M;
    inFile >> M;
    cout<< "Capacidade maxima: " << M <<endl;

    int dados[2*nElementos];

    for(int i = 0; i < 2*nElementos; i++){
        inFile >> dados[i];
    }

    //Peso da cada elemento
    int Peso[nElementos];
    //cout<< "Pesos : ";
    for(int i = 0; i < nElementos; i++){
        Peso[i] = dados[2*i];
        //cout<<Peso[i]<<" - ";
    }

    //Valor de cada elemento
    int Valor[nElementos];
    //cout<< "Valores: ";
    for(int i = 0; i < nElementos; i++){
        Valor[i] = dados[2*i +1];
        //cout<<Valor[i]<<" - ";
    }

    int resultado = KnapSack(M, nElementos, Peso, Valor);
    cout<< "Resultado: " << resultado <<endl;

    return 0;
}

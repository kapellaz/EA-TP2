/*
    Rui Santos: 2020225542 
    Tomás Dias: 2020215701
    
    Task1:
        Para esta tarefa usamos uma matriz dp onde as colunas correspondem aos dias e as linhas 
        correspondem a se compramos ações nesse dia ou não. Para esta tarefa consideramos que compramos
        e vendemos o máximo de ações que podemos ter em mão.
        Inicializamos os valores da ultima coluna a 0 e depois percorremos a matriz do fim para o inicio, 
        começando na coluna d-1, seguindo uma abordagem bottom-up. Para cada dia experimentamos comprar e 
        vender e vemos qual compensa mais. Para o primeiro caso de teste do enunciado obtemos uma matriz
        do genero 600 600 600 510 0  onde o valor do profit máximo estará na 2 linha e 1 coluna.
                  510 450 0 0 0
    
    Task2:
        Para esta tarefa partimos da matriz dp obtida na task 1 e calculamos o caminho da seguinte forma:
        Começamos da ultima coluna para a primeira e analisamos a linha 1(vendas) e linha 2 (compras)
        Quando o valor aumenta quer dizer que houve uma venda/compra. Depois temos de garantir que a ordem
        dos acontecimentos é coerente, ou seja, nao ha 2 compras nem 2 vendas seguidas (porque estamos
        sempre a comprar e a vender o máximo de ações que podemos ter em mão).
        O exemplo do enunciado fica então assim: 0 3 0 -3 0


    Task3:
        Para esta tarefa, recorremos ao uso de programacao dinamica, uma vez que 
        neste problema podemos utilizar problemas de menor estrutura para resolver
        problemas de estrutura maior(subestrutura otima).
        A solucao de cada conjunto dia/acoes a comprar depende do dia anterior. 
        Na matriz stocksbyDay podemos obter o resultado do maximo lucro na primeira linha e ultima coluna.
        Para calcular os caminhos, temos a matriz paths que nos vai guardando para cada 
        conjunto dia/acoes os caminhos a percorrer, baseado também aos resultados do dia anterior,
        onde por exemplo, se no dia anterior temos dois resultados que contribuem para o resultado
        que queremos, o caminho vai ser a soma dos caminhos associados a esses dois resultados anteriores.
        Tal como na matriz stocksbyDay, para obter os caminhos com lucro maximo acedemos ao valor
        da matriz paths na primeira linha e ultima coluna.
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int task;

bool debug = false;
vector<vector<int>> v;
vector<int> ordem;
long long int res1;
int n, d, k, r;
vector<vector<long long int>> dp;
bool comprou = false;
bool vendeu = false;
long long best=0;
long long int valorAmodar=0;



long long int solveTask1(int linha){
    for(int i = d-1; i>=0; i--){
        for(int j = 0; j<2; j++){
            long long int profit = 0;
          
            if(j){ // comprar
                profit = max(-(k*v[linha][i] + k*r) + dp[0][i+1] ,0 + dp[1][i+1]);
            }else{ // vender
                profit = max(k*v[linha][i] + dp[1][i+1] ,0 + dp[0][i+1]);
            }

            dp[j][i] = profit;

        }
    }
    if(debug){
        for(int j = 0; j<2; j++){
            for(int p = 0; p<=d; p++){
                cout << dp[j][p] << " ";
            }
            cout << endl;
        }
    }
    return dp[1][0];
}

void solveTask2(){
    comprou = false;
    vendeu = false;
    ordem = vector<int>(d,0);
    if(dp[1][0]!=0){
        for(int i = d; i>=1; i--){
            if(dp[1][i]<dp[1][i-1] && vendeu != true) {
                //cout << "vendeu" << endl;
                ordem[i-1]=k;
                comprou=false;
                vendeu=true;
            }else if(dp[0][i]<dp[0][i-1] && comprou==true){
                for(int p = i-1; p<d+1; p++){
                    if(ordem[p]==-k){
                        ordem[p]=0;
                        ordem[i-1]=-k;
                        break;
                    }
                }
            }else if(dp[1][i]<dp[1][i-1] && vendeu == true){
                for(int p = i-1; p<d+1; p++){
                    if(ordem[p]==k){
                        ordem[p]=0;
                        ordem[i-1]=k;
                        break;
                    }
                }
            }
            if(dp[0][i]<dp[0][i-1] && comprou!=true){
                ordem[i-1]=-k;
                comprou=true;
                vendeu=false;
            }
        }
    }
}
    


void solveTask3(int linha){
    //matriz dias numero de acoes e em cada quadrado temos o melhor lucro 
    vector<vector<int>> stocksbyDay = vector<vector<int>> (k+1, vector<int>(d)); //guarda o lucro
    vector<vector<int>> paths = vector<vector<int>> (k+1, vector<int>(d,0));
    vector<int> profit = vector<int> (k+1);   

    for(int i = 0; i<k+1; i++){
        stocksbyDay[i][0] = -(i*(v[linha][0] + r));
        //cout << v[linha][0] << endl;
        //cout << stocksbyDay[0][i] << endl;
        paths[i][0] = 1;
    }

    const int MOD = 1e9+7;
    for(int i = 1; i<d; i++){
        for(int j = 0; j<k+1; j++){ //numero de acoes a ficar no dia
            for(int p = 0; p<k+1; p++){  // percorrer numero de acoes dia anterior
                if(j==p){
                    profit[p] = stocksbyDay[p][i-1];
                }
                else if(j<p){
                    profit[p] = stocksbyDay[p][i-1] + v[linha][i] * (p-j);    
                }else{
                    profit[p] = stocksbyDay[p][i-1] - (v[linha][i] + r)*(j-p);
                }
                
            }
            int max = -100000;
            for(int l = 0; l<k+1; l++){
                if(profit[l]> max) max = profit[l];
            }
            int conta = 0;
            for(int l = 0; l<k+1; l++){
                if(profit[l]== max){
                    conta = (conta%MOD + paths[l][i-1]%MOD)%MOD;
                }
            }
            paths[j][i] = conta;
            stocksbyDay[j][i] = max;
        }
    }

    int prof = stocksbyDay[0][d-1];
    int max_profitable_paths = paths[0][d-1];
    cout << prof << " " << max_profitable_paths << endl;
}




int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> task;
    cin >> n >> d >> k >> r;
    v = vector<vector<int>> (n, vector<int>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> v[i][j];
        }
    }

    
    if(task == 1){
        
        for(int i = 0; i<n; i++){
            dp = vector<vector<long long int>> (2, vector<long long int>(d+1, -1));
            dp[0][d]=0;
            dp[1][d]=0;
            cout << solveTask1(i) << endl;;
        }
    }
    
    if(task==2){
        for(int i = 0; i<n; i++){
            dp = vector<vector<long long int>> (2, vector<long long int>(d+1, -1));
            dp[0][d]=0;
            dp[1][d]=0;
            cout << solveTask1(i) << endl;;
            solveTask2();
            for(int j = 0; j<d; j++){
                if(comprou){
                    if(ordem[j]==-k){
                        ordem[j]=0;
                        comprou=false;
                    }
                }
                cout << ordem[j] << " ";
            }
            cout << endl;
        }
    }
    if(task==3){
        for(int i = 0; i<n; i++){
            solveTask3(i);
        }
    }
    
    return 0;
}
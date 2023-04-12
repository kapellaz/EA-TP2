#include <iostream>
#include <vector>

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



long long int solveTask12(int linha){
    for(int i = d-1; i>=0; i--){
        for(int j = 0; j<2; j++){
            long long int profit = 0;
          
            if(j){
                profit = max(-(k*v[linha][i] + k*r) + dp[0][i+1] ,0 +   dp[1][i+1]);
            }else{
                profit = max(k*v[linha][i] + dp[1][i+1] ,0 +   dp[0][i+1]);
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
    
/*long long int fact(long long int n) {
   if (n == 0 || n == 1)
   return 1;
   else
   return n * fact(n - 1);
}*/

long long int combination(long long int y, long long int x){
    if (x > y) {
        return 0;
    }
    long long int res = 1;
    for (int i = 1; i <= x; ++i) {
        res *= y--;
        res /= i;
    }
    return res;
}



void solveTask32(int linha){
    int possibilidadesCompra=0, possibilidadesVenda=0;
    bool compra=true;
    bool venda=false;


    valorAmodar=0;
    long long int conta1=0, conta2=0;
    vector<long long int> valoresCompra = vector<long long int>(d/2,0);
    vector<long long int> valoresVenda = vector<long long int>(d/2,0);
    for(int i = 0; i<d; i++){
        //cout << ordem[i] << " ";
        if(ordem[i] == k){
            valoresCompra[conta1]=v[linha][i];
            conta1++;
        }
        if(ordem[i]==-k){
            valoresVenda[conta2]=v[linha][i];
            conta2++;
        }
    }
    if(conta1==0 && conta2 == 0){
        valorAmodar = 0;
    }

    conta1=0, conta2=0;


    for(int j = 0; j<d; j++){
        //if(valoresCompra[conta1]==0 && valoresVenda[conta2]==0) break;
        if(compra){
            if(v[linha][j]==valoresCompra[conta1])possibilidadesCompra++;
            else if(v[linha][j]==valoresVenda[conta2]){
                compra=false;
                venda=true;
                conta1++;
            }
        }
        if(venda){
            if(v[linha][j]==valoresVenda[conta2]){possibilidadesVenda++;}
            if(v[linha][j]==valoresCompra[conta1] || j == d-1){
                compra=true;
                venda=false;
                conta2++;
                //cout << possibilidadesCompra << " " << possibilidadesVenda << endl;
                long long int valorAmodaraux=0;
                valorAmodaraux+=combination(k+possibilidadesCompra-1, possibilidadesCompra-1);
                valorAmodaraux*=combination(k+possibilidadesVenda-1, possibilidadesVenda-1);
                possibilidadesVenda=0;
                possibilidadesCompra=1;
                if(conta2==1){
                    valorAmodar=valorAmodaraux;
                }else valorAmodar *= valorAmodaraux;
                
            }
        }
    }
    //cout << valorAmodar << endl;
}


void solveTask3(){
    const int MOD = 1e9+7;
    cout << valorAmodar%MOD << endl;
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
            cout << solveTask12(i) << endl;;
        }
    }
    
    if(task==2){
        for(int i = 0; i<n; i++){
            dp = vector<vector<long long int>> (2, vector<long long int>(d+1, -1));
            dp[0][d]=0;
            dp[1][d]=0;
            cout << solveTask12(i) << endl;;
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
            dp = vector<vector<long long int>> (2, vector<long long int>(d+1, -1));
            dp[0][d]=0;
            dp[1][d]=0;
            cout << solveTask12(i) << " ";
            solveTask2();
            for(int j = 0; j<d; j++){
                if(comprou){
                    if(ordem[j]==-k){
                        ordem[j]=0;
                        comprou=false;
                    }
                }
            }
            solveTask32(i);
            solveTask3();
        }
    }
    
    return 0;
}
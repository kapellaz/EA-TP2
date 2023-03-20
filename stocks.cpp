#include <iostream>
#include <vector>

using namespace std;


int task;


void solveTask1(){
    int n, d, k, r;
    cin >> n >> d >> k >> r;

    vector<vector<int>> v(n, vector<int>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> v[i][j];
        }
    }
}


int main(){
    cin >> task;
    if(task == 1) solveTask1();
    return 0;
}
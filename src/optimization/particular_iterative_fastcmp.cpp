#include <bits/stdc++.h>
using namespace std;

#define T_MAX 2
#define N_MAX 50
#define W_MAX 1000

int T, N;
int b[N_MAX];
int C[T_MAX];
int c[T_MAX][N_MAX];
int dp[30][601][601];

// Utils
int my_max(int x, int y) { return (((y-x)>>(31))&(x^y))^y; }
int my_min(int x, int y) { return (((y-x)>>(31))&(x^y))^x; }

int main() {
    scanf("%d %d", &T, &N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }
    for(int i = 0; i < T; i++) {
        scanf("%d", &C[i]);
    }
    for(int i = 0; i < T; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &c[i][j]);
        }
    }


    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= C[0]; j++) {
            for(int k = 0; k <= C[1]; k++) {
                if(!i || !j || !k)
                    dp[i][j][k] = 0;
                else if(c[0][i - 1] <= j && c[1][i - 1] <= k)
                    dp[i][j][k] = my_max(b[i-1] + dp[i-1][j - c[0][i-1]][k - c[1][i-1]], dp[i-1][j][k]);
                else
                    dp[i][j][k] = dp[i-1][j][k];
            }
        }
    }

    printf("%d\n", dp[N][C[0]][C[1]]);

    return 0;
}

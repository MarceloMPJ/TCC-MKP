#include <bits/stdc++.h>
using namespace std;

#define T_MAX 2
#define N_MAX 50
#define W_MAX 1000

int T, N;
int b[N_MAX];
int C[T_MAX];
int c[T_MAX][N_MAX];

// DP
int dp[N_MAX][W_MAX][W_MAX];

// Utils
int my_max(int x, int y) { return (((y-x)>>(31))&(x^y))^y; }
int my_min(int x, int y) { return (((y-x)>>(31))&(x^y))^x; }

int solve(int idx, int weight_1, int weight_2) {
    if(idx < 0) return 0;
    if(dp[idx][weight_1][weight_2] != -1) return dp[idx][weight_1][weight_2];

    if(weight_1 - c[0][idx] >= 0 && weight_2 - c[1][idx] >= 0)
        return dp[idx][weight_1][weight_2] = my_max(solve(idx-1, weight_1, weight_2), solve(idx-1,  weight_1 - c[0][idx], weight_2 - c[1][idx]) + b[idx]);

    return dp[idx][weight_1][weight_2] = solve(idx-1, weight_1, weight_2);
}

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

    memset(dp, -1, sizeof(dp));

    printf("%d\n", solve(N-1, C[0], C[1]));

    return 0;
}

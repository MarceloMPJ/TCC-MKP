#include <bits/stdc++.h>
using namespace std;

#define T_MAX 50
#define N_MAX 50
#define PRIME1 524287

const int HASH_MAX = 1000000;

int T, N;
int b[N_MAX];
int C[T_MAX];
int c[T_MAX][N_MAX];

// Utils
int my_max(int a, int b) { return (a > b) ? a : b; }
int my_min(int a, int b) { return (a < b) ? a : b; }

// DP
struct hash {
    int idx;
    int *weights;
    int value;

    struct hash *next;
};

struct hash *dp[50][1000000];

int calc_hash(int *weights) {
    int m = 0;
    for(int i = 0; i < T; i++)
        m = my_max((m + ((weights[i] * PRIME1) << i)) % (HASH_MAX), m + ((weights[i] * PRIME1) << i/2)  % (HASH_MAX));
    return m % (HASH_MAX);
}

int get_dp(int idx, int *weights) {
    int offset = calc_hash(weights);

    if(dp[idx][offset] == NULL) return -1;

    for(struct hash *it = dp[idx][offset]; it != NULL; it = it->next) {
        if(it->idx == idx) {
            int aux = 0;
            for(int i = 0; i < T; i++) {
                if(it->weights[i] == weights[i])
                    aux++;
                if(aux == T) {
                    return it->value;
                }
            }
        }
    }
    return -1;
}

int set_dp(int idx, int *weights, int value) {
    int offset = calc_hash(weights);

    if(dp[idx][offset] == NULL) {
        dp[idx][offset] = (struct hash *) malloc(sizeof(struct hash));
        dp[idx][offset]->idx = idx;
        dp[idx][offset]->weights = weights;
        dp[idx][offset]->value = value;
        dp[idx][offset]->next = NULL;

        return value;
    }

    struct hash *aux;
    for(struct hash *it = dp[idx][offset]; it != NULL; it = it->next) aux = it;

    aux->next = (struct hash *) malloc(sizeof(struct hash));
    aux = aux->next;
    aux->idx = idx;
    aux->weights = weights;
    aux->value = value;
    aux->next = NULL;

    return value;
}

// Weights
bool validate_weights(int *weights, int idx) {
    for(int i = 0; i < T; i++) {
        if(weights[i] - c[i][idx] < 0) return false;
    }
    return true;
}

void update_weights(int *weights, int idx) {
    for(int i = 0; i < T; i++) weights[i] -= c[i][idx];
}

// Max and Min Weights
int sum_weights[T_MAX][N_MAX];
int prof_sum[N_MAX];
int min_weights[T_MAX][N_MAX];

bool validate_sum_weights(int *weights, int idx) {
    for(int i = 0; i < T; i++)
        if(weights[i] - sum_weights[i][idx] < 0)
            return false;
    return true;
}

bool validate_min_weights(int *weights, int idx) {
    for(int i = 0; i < T; i++)
        if(weights[i] - min_weights[i][idx] < 0)
            return false;
    return true;
}

void act_opt_arr() {
    for(int i = 0; i < T; i++) {
        sum_weights[i][0] = c[i][0];
        min_weights[i][0] = c[i][0];

        for(int j = 1; j < N; j++) {
            sum_weights[i][j] = c[i][j] + sum_weights[i][j-1];
            min_weights[i][j] = min(c[i][j], min_weights[i][j-1]);
        }
    }

    prof_sum[0] = b[0];
    for(int i = 1; i < N; i++)
        prof_sum[i] = b[i] + prof_sum[i-1];
}

// Free memory
vector< int * > memory;

void free_memory() {
    for(unsigned int i = 0; i < memory.size(); i++)
        free(memory[i]);
}

int solve(int idx, int *weights) {
    if(idx < 0) return 0;

    int dp_solve = get_dp(idx, weights);
    if(dp_solve != -1) return dp_solve;

    if(validate_sum_weights(weights, idx))
        return set_dp(idx, weights, prof_sum[idx]);

    if(!validate_min_weights(weights, idx))
        return 0;

    int *new_weights = (int *) malloc(sizeof(int) * T);
    memory.push_back(new_weights);

    for(int i = 0; i < T; i++) new_weights[i] = weights[i];

    if(validate_weights(weights, idx)) {
        update_weights(new_weights, idx);
        int ans = my_max(solve(idx-1, weights), solve(idx-1, new_weights) + b[idx]);
        return set_dp(idx, weights, ans);
    }

    int ans = solve(idx-1, weights);
    return set_dp(idx, weights, ans);
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

    int *vec = (int *) malloc(sizeof(int)*T);
    memory.push_back(vec);

    for(int i = 0; i < T; i++)
        vec[i] = C[i];

    act_opt_arr();

    printf("%d\n", solve(N-1, vec));

    free_memory();

    return 0;
}

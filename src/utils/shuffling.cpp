#include<bits/stdc++.h>
using namespace std;

int myrandom (int i) { return std::rand()%i;}

int main() {
  int T, N;
  std::srand ( unsigned ( std::time(0) ) );
  scanf("%d %d", &T, &N);

  int b[N];
  for(int i = 0; i < N; i++)
    scanf("%d", &b[i]);

  int C[T];
  for(int i = 0; i < T; i++)
    scanf("%d", &C[i]);

  int c[T][N];
  for(int i = 0; i < T; i++)
    for(int j = 0; j < N; j++)
      scanf("%d", &c[i][j]);

  // ---------------------
  cout << T << ' ' << N << '\n';

  for(int i = 0; i < N; i++)
    cout << b[i] << ' ';
  cout << '\n';

  for(int i = 0; i < T; i++)
    cout << C[i] << ' ';
  cout << '\n';

  vector<int> randomic;
  for(int i = 0; i < N; i++)
      randomic.push_back(i);

  for(int i = 0; i < T; i++) {
    for(int j = 0; j < N; j++) {

      std::random_shuffle ( randomic.begin(), randomic.end() );
      std::random_shuffle ( randomic.begin(), randomic.end(), myrandom );

      cout << c[i][ randomic[j] ] << ' ';
    }
    cout << '\n';
  }


  return 0;
}

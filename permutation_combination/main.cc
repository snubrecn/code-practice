#include <iostream>
#define MAX 5

using namespace std;

char src[MAX + 1] = {'\0' /*unused element*/, 97, 98, 'c', 'd', 'e'};
char a[MAX];
int visited[MAX + 1];

int N, R;  // N: among N elements, R: pick R elements

void Print() {
  cout << "[";
  for (int i = 1; i <= R; i++) {
    cout << a[i] << " ";
  }
  cout << "]\n";
}

void Combination(int n, int r) {
  if (r == 0) {
    // Finished.
    Print();
    return;
  }
  if (n < r) {
    // Invalid.
    return;
  }
  a[r] = src[n];
  Combination(n - 1, r - 1);
  Combination(n - 1, r);
}

void CombinationDup(int n, int r) {
  if (r == 0) {
    // Finished.
    Print();
    return;
  }
  if (n == 0) {
    // Invalid.
    return;
  }
  a[r] = src[n];
  // Note the order of recursive calls
  CombinationDup(n, r - 1);
  CombinationDup(n - 1, r);
}

void Permutation(int k /*level*/) {
  if (k == R) {
    // Finished.
    Print();
    return;
  }
  k++;
  for (int i = 1; i <= N; i++) {
    if (!visited[i]) {
      visited[i] = 1;
      a[k] = src[i];
      Permutation(k);
      visited[i] = 0;
    }
  }
}

void PermutationDup(int k /*level*/) {
  if (k == R) {
    // Finished.
    Print();
    return;
  }
  k++;
  for (int i = 1; i <= N; i++) {
    a[k] = src[i];
    PermutationDup(k);
  }
}

int main(void) {
  N = 5;
  R = 2;
  // Combination(N, R);
  // CombinationDup(N, R);
  // Permutation(0);
  // PermutationDup(0);

  return 0;
}

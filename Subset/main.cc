#include <iostream>
#define NUM 5
using namespace std;

char set[NUM] = {'a', 98, 99, 'd', 'e'};

int n;
int a[NUM];

void printSubset() {
  for (int i = 1; i <= n; i++) {
    if (a[i]) {
      cout << set[i - 1] << " ";
    }
  }
  cout << endl;
}

void allSubsetBit(int num /*number of elements in a set*/) {
  for (int i = 0; i < 1 << num; i++) {
    for (int j = 0; j < num; j++) {
      if (i & (1 << j)) {
        cout << set[j] << " ";
      }
    }
    cout << endl;
  }
}

void subset(int k /*level*/) {
  if (k == n) {
    printSubset();
    return;
  }
  k++;
  a[k] = 1;
  subset(k);
  a[k] = 0;
  subset(k);
}

int main(void) {
  int num_element = 5;
  n = num_element;

  // allSubsetBit(num_element);

  subset(0);

  return 0;
}
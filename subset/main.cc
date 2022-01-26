#include <iostream>
#define NUM 5

char set[NUM] = {'a', 98, 99, 'd', 'e'};
bool a[NUM];

void PrintSubsetsBit(int num) {
  for (int i = 0; i < 1 << num; i++) {
    std::cout << "[ ";
    for (int j = 0; j < num; j++)
      if (i & (1 << j)) std::cout << set[j] << " ";
    std::cout << "]\n";
  }
}

void PrintSubsetsBacktracking(int k /*level*/, int num /*number of elements*/) {
  if (k == num) {
    std::cout << "[ ";
    for (int i = 0; i < num; i++)
      if (a[i]) std::cout << set[i] << " ";
    std::cout << "]\n";
    return;
  }

  a[k] = true;
  PrintSubsetsBacktracking(k + 1, num);

  a[k] = false;
  PrintSubsetsBacktracking(k + 1, num);
}

int main(void) {
  std::cout << "Print all subsets by using bit operation\n";
  PrintSubsetsBit(NUM);

  std::cout << "Print all subsets by backtracking\n";
  PrintSubsetsBacktracking(0, NUM);

  return 0;
}

#include <chrono>
#include <functional>
#include <iostream>

#define MAX 10000

int fibonacci[MAX];

void MeasureExecutionTime(int n, std::function<void(int n)> execution) {
  std::chrono::steady_clock::time_point start =
      std::chrono::steady_clock::now();
  execution(n);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout << "Execution time: " << (end - start).count() * 1e-9
            << " secs\n\n";
}

int FibonacciRecursive(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }
  return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
}

int FibonacciBottomUp(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }
  int fibonacci[n];

  fibonacci[0] = fibonacci[1] = 1;

  for (int i = 2; i < n; i++) {
    fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
  }
  return fibonacci[n - 1] + fibonacci[n - 2];
}

int FibonacciTopDown(int n) {
  if (n == 0 || n == 1) {
    fibonacci[n] = 1;
    return 1;
  }
  if (fibonacci[n]) {
    return fibonacci[n];
  }
  fibonacci[n] = FibonacciTopDown(n - 1) + FibonacciTopDown(n - 2);
  return fibonacci[n];
}

int main(void) {
  int seq_num;
  while (1) {
    std::cin >> seq_num;
    MeasureExecutionTime(seq_num, [](int n) {
      std::cout << "Recursion\n";
      std::cout << "Fibonacci[" << n << "]: " << FibonacciRecursive(n)
                << std::endl;
    });

    MeasureExecutionTime(seq_num, [](int n) {
      std::cout << "Bottom-up dynamic programming\n";
      std::cout << "Fibonacci[" << n << "]: " << FibonacciBottomUp(n)
                << std::endl;
    });

    MeasureExecutionTime(seq_num, [](int n) {
      std::cout << "Top-down dynamic programming\n";
      std::cout << "Fibonacci[" << n << "]: " << FibonacciTopDown(n)
                << std::endl;
    });
  }

  return 0;
}

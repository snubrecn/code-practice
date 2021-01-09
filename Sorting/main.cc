#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#define INT_MAX 0x7fffffff;

void MeasureExecutionTime(int* src, int len, std::function<void(int* src, int len)> execution) {
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  execution(src, len);
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

  std::cout << "Execution time: " << (t2 - t1).count() * 1e-9 << " secs\n";
}

void MeasureExecutionTime(int* src, int s, int e,
                          std::function<void(int* src, int s, int e)> execution) {
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  execution(src, s, e);
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

  std::cout << "Execution time: " << (t2 - t1).count() * 1e-9 << " secs\n";
}

void CopyArray(int* src, int* dst, int len) {
  for (int i = 0; i < len; i++) *(dst + i) = *(src + i);
}

void BubbleSort(int* src, int len) {
  for (int i = 0; i < len; i++) {
    for (int j = 1; j < len - i; j++) {
      if (src[j - 1] > src[j]) {
        int tmp = src[j - 1];
        src[j - 1] = src[j];
        src[j] = tmp;
      }
    }
  }
}

void InsertionSort(int* src, int len) {
  for (int i = 1; i < len; i++) {
    for (int j = i; j != 0; j--) {
      if (src[j] < src[j - 1]) {
        int tmp = src[j];
        src[j] = src[j - 1];
        src[j - 1] = tmp;
      }
    }
  }
}

void SelectionSort(int* src, int len) {
  for (int i = 0; i < len - 1; i++) {
    int min = INT_MAX;
    int min_idx, tmp;
    for (int j = i; j < len; j++) {
      if (src[j] < min) {
        min = src[j];
        min_idx = j;
      }
    }
    tmp = src[i];
    src[i] = min;
    src[min_idx] = tmp;
  }
}

// s: inclusive start
// e: exclusisve end
void MergeSort(int* src, int s, int e) {
  if (s >= e - 1) return;
  int m = (s + e) / 2;
  MergeSort(src, s, m);
  MergeSort(src, m, e);

  int* tmp = new int[e- s];
  int idx = 0;
  int s1 = s;
  int s2 = m;

  while (s1 < m && s2 < e) {
    if (src[s1] <= src[s2])
      tmp[idx++] = src[s1++];
    else
      tmp[idx++] = src[s2++];
  }
  while (s1 < m) tmp[idx++] = src[s1++];
  while (s2 < e) tmp[idx++] = src[s2++];

  for (int i = s; i < e; i++) src[i] = tmp[i - s];
  delete[] tmp;
}

void QuickSort(int* src, int s, int e) {}

void PrintArray(int* src, int len) {
  std::cout << "[";
  for (int i = 0; i < len; i++) std::cout << src[i] << " ";
  std::cout << "]\n";
}

int main(void) {
  int len = 10000;
  std::vector<int> vector;
  vector.resize(len);
  for (int i = 0; i < len; ++i) vector[i] = i;
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(vector.begin(), vector.end(), std::default_random_engine(seed));
  int* arr = new int[len];
  int* arr_tmp = new int[len];
  for (int i = 0; i < len; ++i) arr[i] = arr_tmp[i] = vector[i];

  //  std::cout << "Original array\n";
  //  PrintArray(arr, len);

  std::cerr << "Bubble Sort Result\n";
  MeasureExecutionTime(arr_tmp, len, BubbleSort);
  //  PrintArray(arr_tmp, len);

  std::cerr << "Selection Sort Result\n";
  CopyArray(arr, arr_tmp, len);
  MeasureExecutionTime(arr_tmp, len, SelectionSort);
  //  PrintArray(arr_tmp, len);

  std::cerr << "Insertion Sort Result\n";
  CopyArray(arr, arr_tmp, len);
  MeasureExecutionTime(arr_tmp, len, InsertionSort);
  //  PrintArray(arr_tmp, len);

  std::cerr << "Merge Sort Result\n";
  CopyArray(arr, arr_tmp, len);
  MeasureExecutionTime(arr_tmp, 0, len, MergeSort);
  //  PrintArray(arr_tmp, len);

  delete[] arr_tmp;
  delete[] arr;

  return 0;
}

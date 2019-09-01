#include <iostream>

#define LEN 10
#define INT_MAX 0x7fffffff;

// To do: Add random int generator to make unsorted array of arbitrary length
// Compare time consumption of different sorting methods.

using namespace std;

int src[LEN] = {9, 4, 2, 8, 10, 5, 1, 3, 6, 7};

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

void MergeSort(int* src, int s, int e) {  // end index e : exclusive
  if (s < e - 1) {
    int m = (s + e) / 2;
    MergeSort(src, s, m);
    MergeSort(src, m, e);

    int s_1 = s;
    int s_2 = m;
    int idx = 0;
    int tmp[LEN];

    while (s_1 < m && s_2 < e) {
      if (src[s_1] < src[s_2]) {
        tmp[idx++] = src[s_1++];
      } else {
        tmp[idx++] = src[s_2++];
      }
    }
    while (s_1 < m) {
      tmp[idx++] = src[s_1++];
    }
    while (s_2 < e) {
      tmp[idx++] = src[s_2++];
    }
    for (int i = 0; i < idx; i++) {
      src[s + i] = tmp[i];
    }
  }
}

void QuickSort(int* src, int s, int e) {}

void PrintArray(int* src, int len) {
  cout << "[";
  for (int i = 0; i < len; i++) {
    cout << src[i] << " ";
  }
  cout << "]\n";
}

int main(void) {
  int len = LEN;
  cout << "Before sorting\n";

  PrintArray(src, len);
  // BubbleSort(src, len);
  // SelectionSort(src, len);
  // InsertionSort(src, len);
  // MergeSort(src, 0, len);

  cout << "After sorting\n";
  PrintArray(src, len);
  return 0;
}

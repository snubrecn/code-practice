#ifndef HEAP_H_
#define HEAP_H_
#include <iostream>

namespace heap {

class Heap {
 public:
  Heap(const int capacity) : capacity_(capacity), size_(0) {
    data_ = new int[capacity + 1];
    // set unused element at 0
    data_[0] = 0;
  }
  ~Heap() { delete[] data_; }

  void Push(int data) {
    if (size_ > capacity_) return;
    data_[++size_] = data;
    int idx = size_;
    while (idx != 1 && data_[idx] < data_[idx / 2]) {
      int tmp = data_[idx];
      data_[idx] = data_[idx / 2];
      data_[idx / 2] = tmp;
      idx /= 2;
    }
  }
  void Pop(int* const value) {
    if (size_ == 0) return;
    int idx = 1;
    *value = data_[idx];
    data_[idx] = data_[size_--];
    while (idx <= size_ / 2) {
      int left = data_[idx * 2];
      int right = data_[idx * 2 + 1];
      int next_idx = left < right ? idx * 2 : idx * 2 + 1;
      if (data_[next_idx] < data_[idx]) {
        int tmp = data_[idx];
        data_[idx] = data_[next_idx];
        data_[next_idx] = tmp;
        idx = next_idx;
      } else {
        break;
      }
    }
  }

 private:
  int capacity_;
  int* data_;
  int size_;
};

}  // namespace heap

#endif

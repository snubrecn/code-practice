#include <iostream>

class LinkedList {
 public:
  LinkedList() { Init(); }
  ~LinkedList() { Free(); }

  void Init() {
    head_ = new Node();
    tail_ = new Node();
    head_->prev = nullptr;
    head_->next = tail_;
    tail_->prev = head_;
    tail_->next = nullptr;
    cnt_ = 0;
  }

  void Print() {
    Node* pos = head_->next;
    std::cout << "list: ";
    while (pos->next) {
      std::cout << pos->data << " ";
      pos = pos->next;
    }
    std::cout << std::endl;
  }

  void Append(int data) {
    Node* new_node = new Node();
    new_node->data = data;
    new_node->prev = tail_->prev;
    new_node->next = tail_;
    tail_->prev->next = new_node;
    tail_->prev = new_node;
    cnt_++;
  }

  void Insert(int position, int data) {
    if (position > cnt_) return;
    Node* pos = head_->next;
    while (position--) pos = pos->next;
    Node* new_data = new Node();
    new_data->data = data;
    new_data->prev = pos->prev;
    new_data->next = pos;
    pos->prev->next = new_data;
    pos->prev = new_data;
    cnt_++;
  }

  int Delete(int position, int* value) {
    if (position >= cnt_) return 0;
    Node* pos = head_->next;
    while (position--) pos = pos->next;
    *value = pos->data;
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
    cnt_--;
    return 1;
  }

  void Free() {
    Node* pos = head_->next;
    while (pos->next) {
      delete pos->prev;
      pos = pos->next;
    }
    delete tail_;
    cnt_ = 0;
  }

 private:
  struct Node {
    int data;
    Node* prev;
    Node* next;
  };
  Node* head_;
  Node* tail_;
  int cnt_;
};

int main(void) {
  LinkedList list;
  list.Print();
  list.Append(-3);
  list.Print();
  list.Append(-19);
  list.Print();
  list.Append(1);
  list.Print();
  list.Insert(1, -5);
  list.Print();
  list.Append(4);
  list.Print();
  list.Insert(2, 10);
  list.Print();

  int value;
  if (list.Delete(2, &value)) {
    list.Print();
    std::cout << "Deleted value: " << value << std::endl;
  }
  return 0;
}

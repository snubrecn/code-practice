#include <iostream>
#include <random>
#define INT_MAX 0x7fffffff

// Hash Table of integer ids
// A singly-linked list corresponds to each key value
class HashTableByMod {
 public:
  struct Node {
    int id;
    Node* next;
  };
  HashTableByMod(const int max_hash) : max_hash_(max_hash) { table_ = new Node*[max_hash]; }
  ~HashTableByMod() {
    for (int i = 0; i < max_hash_; ++i) {
      if (table_[i] == nullptr) continue;
      Node* pos = table_[i];
      Node* next = pos->next;
      while (next) {
        delete pos;
        pos = next;
        next = next->next;
      }
      delete pos;
    }
  }

  void Add(int id) {
    int key = GetKey(id);
    Node* new_node = new Node();
    new_node->id = id;
    new_node->next = nullptr;
    if (table_[key] == nullptr) {
      table_[key] = new_node;
    } else {
      Node* pos = table_[key];
      while (pos->next) pos = pos->next;
      pos->next = new_node;
    }
  }
  void Delete(int id) {
    int key = GetKey(id);
    if (table_[key] == nullptr) return;
    Node* pos = table_[key];
    if (pos->id == id) {
      table_[key] = pos->next;
      delete pos;
    } else {
      Node* next = pos->next;
      while (next) {
        if (next->id == id) {
          pos->next = next->next;
          delete next;
        }
        pos = next;
        next = next->next;
      }
    }
  }
  Node* Find(int id) {
    int key = GetKey(id);
    Node* pos = table_[key];
    if (pos != nullptr) {
      while (pos) {
        if (pos->id == id) return pos;
        pos = pos->next;
      }
    }
    return nullptr;
  }
  void Print() {
    for (int i = 0; i < max_hash_; ++i) {
      Node* pos = table_[i];
      std::cout << "Key " << i << ": ";
      while (pos) {
        std::cout << pos->id << " ";
        pos = pos->next;
      }
      std::cout << std::endl;
    }
  }

 private:
  int GetKey(const int id) { return id % max_hash_; }
  Node** table_;
  int max_hash_;
};

int main(void) {
  int max_hash = 10;
  HashTableByMod table(max_hash);
  int ids[100] = {
      0,
  };
  std::random_device rd;
  std::mt19937 rng{rd()};
  std::uniform_int_distribution<int> dist(0, INT_MAX);

  for (int i = 0; i < 100; i++) {
    int id = dist(rng) % 3000;
    table.Add(id);
    ids[i] = id;
  }

  std::cout << "Added 100 ids\n";
  table.Print();

  for (int i = 0; i < 50; i++) {
    table.Delete(ids[i]);
  }

  std::cout << "\nDeleted first half\n";
  table.Print();

  for (int i = 50; i < 100; i++) {
    table.Delete(ids[i]);
  }

  std::cout << "\nDeleted last half\n";
  table.Print();

  return 0;
}

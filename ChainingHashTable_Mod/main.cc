#include <malloc.h>
#include <stdlib.h>
#include <iostream>

#define MAX_HASH 10
#define GET_KEY(id) id % MAX_HASH

typedef struct node {
  int id;
  struct node* next;
} Node;

Node* table[MAX_HASH];

void Add(int id) {
  int key = GET_KEY(id);

  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->id = id;

  if (table[key] == NULL) {
    table[key] = new_node;
    new_node->next = NULL;
  } else {
    new_node->next = table[key];
    table[key] = new_node;
  }
}

void Delete(int id) {
  int key = GET_KEY(id);

  if (table[key] == NULL) {
    return;
  }

  Node* curr = table[key];
  Node* next = curr->next;

  if (curr->id == id) {
    free(curr);
    table[key] = next;
    return;
  }

  while (next) {
    if (next->id == id) {
      curr->next = next->next;
      free(next);
      break;
    }
    curr = next;
    next = next->next;
  }
}

Node* Find(int id) {
  int key = GET_KEY(id);

  if (table[key] == NULL) {
    return NULL;
  }

  Node* curr = table[key];
  while (curr) {
    if (curr->id == id) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

void Print() {
  for (int key = 0; key < MAX_HASH; key++) {
    if (table[key]) {
      Node* pos = table[key];
      while (pos->next) {
        std::cout << pos->id << " ";
        pos = pos->next;
      }
      std::cout << std::endl;
    }
  }
}

int main(void) {
  int ids[100] = {
      0,
  };

  for (int i = 0; i < 100; i++) {
    int id = rand() % 3000;
    Add(id);
    ids[i] = id;
  }

  std::cout << "Added 100 ids\n";
  Print();

  for (int i = 0; i < 50; i++) {
    Delete(ids[i]);
  }

  std::cout << "\nDeleted first half\n";
  Print();

  for (int i = 50; i < 100; i++) {
    Delete(ids[i]);
  }

  std::cout << "\nDeleted last half\n";
  Print();

  return 0;
}

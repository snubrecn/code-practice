#include <malloc.h>

#include <iostream>

typedef struct node {
  int data;
  struct node* prev;
  struct node* next;
} Node;

Node* head;
Node* tail;
int cnt;

void Init() {
  head = (Node*)malloc(sizeof(Node));
  tail = (Node*)malloc(sizeof(Node));

  head->prev = NULL;
  head->next = tail;

  tail->prev = head;
  tail->next = NULL;
}

void Print() {
  std::cout << "List count: " << cnt << " elements: ";

  Node* pos = head->next;
  for (int i = 0; i < cnt; i++) {
    std::cout << pos->data << " ";
    pos = pos->next;
  }
  std::cout << std::endl;
}

void Append(int data) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->data = data;

  new_node->prev = tail->prev;
  tail->prev->next = new_node;

  tail->prev = new_node;
  new_node->next = tail;

  cnt++;
}

void Insert(int position, int data) {
  if (position >= cnt) {
    Append(data);
  } else {
    Node* pos = head->next;

    for (int i = 0; i < position; i++) {
      pos = pos->next;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    new_node->next = pos->next;
    new_node->prev = pos;

    pos->next->prev = new_node;
    pos->next = new_node;

    cnt++;
  }
}

int Delete(int position, int* value) {
  if (position <= cnt) {
    Node* pos = head->next;

    for (int i = 0; i < position; i++) {
      pos = pos->next;
    }

    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;

    *value = pos->data;

    free(pos);
    cnt--;

    return 1;
  } else {
    std::cout << "List out-of-range\n";
    return 0;
  }
}

void Free() {
  Node* pos = head->next;
  while (pos) {
    free(pos->prev);
    pos = pos->next;
  }
  free(tail);
  cnt = 0;
}

int main(void) {
  Init();

  int value;

  std::cout << "Just after initialize" << std::endl;
  Print();

  Append(-3);
  Print();
  Append(-19);
  Print();
  Append(1);
  Print();
  Insert(1, -5);
  Print();

  Append(4);
  Print();

  Insert(2, 10);
  Print();

  if (Delete(2, &value)) {
    Print();
    std::cout << "Deleted value: " << value << std::endl;
  }

  Free();

  return 0;
}
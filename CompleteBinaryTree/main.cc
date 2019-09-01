#include <iostream>
#define MAX 10

using namespace std;

// Let the index of root be 1
int left_c[MAX] = {0 /*unused*/, 2, 4, 6, 8, 10};
int right_c[MAX] = {1 /*unused*/, 3, 5, 7, 9};

int src[2 * (MAX + 1)] = {0 /*unused*/, 97,  98,  99,  100,
                          101,          102, 103, 104, 105};

void BFS(int start) {
  int queue[2 * (MAX + 1)];
  int front, rear, u;
  front = rear = 0;

  queue[rear++] = start;

  while (front != rear) {
    u = queue[front++];
    cout << char(src[u]) << endl;
    if (src[2 * u]) {
      queue[rear++] = 2 * u;
    }
    if (src[2 * u + 1]) {
      queue[rear++] = 2 * u + 1;
    }
  }
}

void PreOrder(int root) {
  if (src[root]) {
    cout << char(src[root]) << endl;
    PreOrder(root * 2);
    PreOrder(root * 2 + 1);
  }
}

void InOrder(int root) {
  if (src[root]) {
    InOrder(root * 2);
    cout << char(src[root]) << endl;
    InOrder(root * 2 + 1);
  }
}

void PostOrder(int root) {
  if (src[root]) {
    PostOrder(root * 2);
    PostOrder(root * 2 + 1);
    cout << char(src[root]) << endl;
  }
}

void PreOrderByIndexArray(int root) {
  if (src[root]) {
    cout << char(src[root]) << endl;
    PreOrderByIndexArray(left_c[root]);
    PreOrderByIndexArray(right_c[root]);
  }
}

void InOrderByIndexArray(int root) {
  if (src[root]) {
    InOrderByIndexArray(left_c[root]);
    cout << char(src[root]) << endl;
    InOrderByIndexArray(right_c[root]);
  }
}

void PostOrderByIndexArray(int root) {
  if (src[root]) {
    PostOrderByIndexArray(left_c[root]);
    PostOrderByIndexArray(right_c[root]);
    cout << char(src[root]) << endl;
  }
}

int main(void) {
  int start = 1;
  cout << "BFS traversal: \n";
  BFS(start);
  cout << "Pre-order traversal: \n";
  PreOrder(start);
  cout << "In-order traversal: \n";
  InOrder(start);
  cout << "Post-order traversal: \n";
  PostOrder(start);

  return 0;
}

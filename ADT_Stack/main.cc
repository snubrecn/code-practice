#include <iostream>
#define CAPACITY 20
#define INT_MIN 0x80000000

using namespace std;

int stack[CAPACITY];
int top;

bool IsFull() { return top == CAPACITY; }

bool IsEmpty() { return top == 0; }

void Push(int data) {
  if (IsFull()) {
    cout << "Stack Overflow\n";
    return;
  }
  stack[top++] = data;
}

void Pop() {
  if (IsEmpty()) {
    cout << "Stack Empty\n";
    return;
  }
  top--;
}

int Top() {
  if (IsEmpty()) {
    cout << "Stack Empty\n";
    return INT_MIN;
  }
  return stack[top - 1];
}

void PrintStack() {
  cout << "[";
  for (int i = 0; i < top; i++) {
    cout << stack[i] << " ";
  }
  cout << "]" << endl;
}

int main(void) {
  PrintStack();
  Pop();

  Push(10);
  PrintStack();
  Push(20);
  PrintStack();
  Push(-30);
  PrintStack();

  for (int i = 0; i < CAPACITY; i++) {
    Push(i);
    PrintStack();
    cout << "Current Top: " << Top() << endl;
  }

  for (int i = 0; i < CAPACITY + 3; i++) {
    Pop();
    PrintStack();
    cout << "Current Top: " << Top() << endl;
  }

  return 0;
}

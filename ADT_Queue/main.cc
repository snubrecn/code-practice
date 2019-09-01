#include <iostream>
#define CAPACITY 20
#define INT_MAX 0x7fffffff
#define USE_LINEAR_QUEUE

using namespace std;

int q[CAPACITY];
int c_q[CAPACITY];
int c_q_cnt;

int front, rear;

#ifdef USE_LINEAR_QUEUE

bool IsFull() { return rear == CAPACITY; }

bool IsEmpty() { return front == rear; }

int Enqueue(int data) {
  if (IsFull()) {
    cout << "Queue Overflow\n";
    return 0;
  }
  q[rear++] = data;
  return 1;
}

/**
  Everytime Dequeue is called,
  actual capacity of linear queue is decreased by 1
  (actual capacity: CAPACITY - front)
 */
int Dequeue(int* data) {
  if (IsEmpty()) {
    cout << "Queue Empty\n";
    return 0;
  }
  *data = q[front++];
  return 1;
}

void PrintQueue() {
  cout << "[";
  for (int i = front; i < rear; i++) {
    cout << q[i] << " ";
  }
  cout << "]" << endl;
}

#else  // USE_CIRCULAR_QUEUE

#endif

int main(void) {
  int dequeued_val;
  PrintQueue();
  Dequeue(&dequeued_val);

  Enqueue(10);
  PrintQueue();
  Enqueue(20);
  PrintQueue();
  Dequeue(&dequeued_val);
  cout << "De-queued value: " << dequeued_val << endl;
  PrintQueue();
  Enqueue(-30);
  PrintQueue();

  for (int i = 0; i < CAPACITY; i++) {
    Enqueue(i);
    PrintQueue();
  }

  for (int i = 0; i < CAPACITY; i++) {
    Dequeue(&dequeued_val);
    PrintQueue();
    cout << "De-queued value: " << dequeued_val << endl;
  }

  return 0;
}

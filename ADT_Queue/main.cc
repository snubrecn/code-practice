#include <iostream>
#define CAPACITY 20
//#define USE_LINEAR_QUEUE

using namespace std;

int q[CAPACITY];
int c_q[CAPACITY];
int c_q_cnt;

int front, rear;

#ifdef USE_LINEAR_QUEUE

bool IsFull() { return rear == CAPACITY; }

bool IsEmpty() { return front == rear; }

bool Enqueue(int data) {
  if (IsFull()) {
    cout << "Queue Overflow\n";
    return false;
  }
  q[rear++] = data;
  return true;
}

/**
  Everytime Dequeue is called,
  actual capacity of linear queue is decreased by 1
  (actual capacity: CAPACITY - front)
 */
bool Dequeue(int* data) {
  if (IsEmpty()) {
    cout << "Queue Empty\n";
    return false;
  }
  *data = q[front++];
  return true;
}

void PrintQueue() {
  cout << "[";
  for (int i = front; i < rear; i++) {
    cout << q[i] << " ";
  }
  cout << "]" << endl;
}

#else  // USE_CIRCULAR_QUEUE

bool IsEmpty() { return front == rear; }

bool IsFull() { return (rear + 1) % CAPACITY == front; }

bool Enqueue(int data) {
  if (IsFull()) {
    cout << "Queue Overflow!\n";
    return false;
  }
  c_q_cnt++;
  q[rear] = data;
  rear = (rear + 1) % CAPACITY;
  return true;
}

bool Dequeue(int* data) {
  if (IsEmpty()) {
    cout << "Queue Empty\n";
    return false;
  }
  c_q_cnt--;
  *data = q[front];
  front = (front + 1) % CAPACITY;
  return true;
}

void PrintQueue() {
  cout << "[";
  for (int i = 0; i < c_q_cnt; i++) {
    cout << q[(front + i) % CAPACITY] << " ";
  }
  cout << "]\n";
}

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
    cout << "De-queued value: " << dequeued_val << endl;
    PrintQueue();
  }

  return 0;
}

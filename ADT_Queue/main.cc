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

bool isFull() {
    return rear == CAPACITY;
}

bool isEmpty() {
    return front == rear;
}

int enQueue(int data) {
    if(isFull()) {
        cout << "Queue Overflow\n";
        return 0;
    }
    q[rear++] = data;
    return 1;
}

/**
  Everytime deQueue is called,
  actual capacity of linear queue is decreased by 1
  (actual capacity: CAPACITY - front)
 */
int deQueue(int* data) {
    if(isEmpty()) {
        cout << "Queue Empty\n";
        return 0;
    }
    *data = q[front++];
    return 1;
}

void printQueue() {
    cout << "[";
    for(int i = front; i < rear; i++) {
        cout << q[i] << " ";
    }
    cout << "]" << endl;
}

#else   // USE_CIRCULAR_QUEUE

#endif

int main(void) {
    int dequeued_val;
    printQueue();
    deQueue(&dequeued_val);

    enQueue(10);
    printQueue();
    enQueue(20);
    printQueue();
    deQueue(&dequeued_val);
    cout << "De-queued value: " << dequeued_val << endl;
    printQueue();
    enQueue(-30);
    printQueue();

    for(int i = 0; i < CAPACITY; i++) {
        enQueue(i);
        printQueue();
    }

    for(int i = 0; i < CAPACITY; i++) {
        deQueue(&dequeued_val);
        printQueue();
        cout << "De-queued value: " << dequeued_val << endl;
    }

	return 0;
}

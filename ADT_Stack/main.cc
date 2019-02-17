#include <iostream>
#define CAPACITY 20
#define INT_MIN 0x80000000

using namespace std;

int stack[CAPACITY];
int top_;

bool isFull() {
    return top_ == CAPACITY;
}

bool isEmpty() {
    return top_ == 0;
}

void push(int data) {
    if(isFull()) {
        cout << "Stack Overflow\n";
        return;
    }
    stack[top_++] = data;
}

void pop() {
    if(isEmpty()) {
        cout << "Stack Empty\n";
        return;
    }
    top_--;
}

int top() {
    if(isEmpty()) {
        cout << "Stack Empty\n";
        return INT_MIN;
    }
    return stack[top_ - 1];
}

void printStack() {
    cout << "[";
    for(int i = 0; i < top_; i++) {
        cout << stack[i] << " ";
    }
    cout << "]" << endl;
}

int main(void) {
    printStack();
    pop();

    push(10);
    printStack();
    push(20);
    printStack();
    push(-30);
    printStack();

    for(int i = 0; i < CAPACITY; i++) {
        push(i);
        printStack();
        cout << "Current top: " << top() << endl;
    }

    for(int i = 0; i < CAPACITY + 3; i++) {
        pop();
        printStack();
        cout << "Current top: " << top() << endl;
    }

	return 0;
}

#include <iostream>
#define MAX 10

using namespace std;

// Let the index of root be 1
int left_c[MAX] = {0/*unused*/, 2, 4, 6, 8, 10};
int right_c[MAX] = {1/*unused*/, 3, 5, 7, 9};

int src[2 * (MAX + 1)] = {0/*unused*/, 97, 98, 99, 100, 101, 102, 103, 104, 105};

void bfs(int start) {
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

void preOrder(int root) {
	if (src[root]) {
		cout << char(src[root]) << endl;
		preOrder(root * 2);
		preOrder(root * 2 + 1);
	}
}

void inOrder(int root) {
	if (src[root]) {
		inOrder(root * 2);
		cout << char(src[root]) << endl;
		inOrder(root * 2 + 1);
	}
}

void postOrder(int root) {
	if (src[root]) {
		postOrder(root * 2);
		postOrder(root * 2 + 1);
		cout << char(src[root]) << endl;
	}
}

void preOrderByIndexArray(int root) {
	if (src[root]) {
		cout << char(src[root]) << endl;
		preOrderByIndexArray(left_c[root]);
		preOrderByIndexArray(right_c[root]);
	}
}

void inOrderByIndexArray(int root) {
	if (src[root]) {
		inOrderByIndexArray(left_c[root]);
		cout << char(src[root]) << endl;
		inOrderByIndexArray(right_c[root]);
	}
}

void postOrderByIndexArray(int root) {
	if (src[root]) {
		postOrderByIndexArray(left_c[root]);
		postOrderByIndexArray(right_c[root]);
		cout << char(src[root]) << endl;
	}
}

int main(void) {
	int start = 1;
	cout << "BFS traversal: \n";
	bfs(start);
	cout << "Pre-order traversal: \n";
	preOrder(start);
	cout << "In-order traversal: \n";
	inOrder(start);
	cout << "Post-order traversal: \n";
	postOrder(start);

	return 0;
}
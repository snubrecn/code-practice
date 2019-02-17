#include <iostream>
#define MAX 5

using namespace std;

char src[MAX + 1] = {'\0'/*unused element*/, 97, 98, 'c', 'd', 'e' };
char a[MAX];
int visited[MAX + 1];

int N, R;	// N: among N elements, R: pick R elements

void print() {
	cout << "[";
	for (int i = 1; i <= R; i++) {
		cout << a[i] << " ";
	}
	cout << "]\n";
}

void combination(int n, int r) {
	if (r == 0) {
		// Finished.
		print();
		return;
	}
	if (n < r) {
		// Invalid.
		return;
	}
	a[r] = src[n];
	combination(n - 1, r - 1);
	combination(n - 1, r);
}

void combinationDup(int n, int r) {
	if (r == 0) {
		// Finished.
		print();
		return;
	}
	if (n == 0) {
		// Invalid.
		return;
	}
	a[r] = src[n];
	// Note the order of recursive calls
	combinationDup(n, r - 1);
	combinationDup(n - 1, r);
}

void permutation(int k/*level*/) {
	if (k == R) {
		// Finished.
		print();
		return;
	}
	k++;
	for (int i = 1; i <= N; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			a[k] = src[i];
			permutation(k);
			visited[i] = 0;
		}
	}
}

void permutationDup(int k/*level*/) {
	if (k == R) {
		// Finished.
		print();
		return;
	}
	k++;
	for (int i = 1; i <= N; i++) {
		a[k] = src[i];
		permutation(k);
	}
}

int main(void) {
	N = 5;
	R = 2;
	//combination(N, R);
	//combinationDup(N, R);
	//permutation(0);
	//permutationDup(0);

	return 0;
}
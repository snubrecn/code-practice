#include <iostream>
#define NUM 5
using namespace std;

char set[NUM] = { 'a', 98, 99, 'd', 'e' };

void allSubsetBit(int num/*number of elements in a set*/) {
	for (int i = 0; i < 1 << num; i++) {
		for (int j = 0; j < num; j++) {
			if (i & (1 << j)) {
				cout << set[j] << " ";
			}
		}
		cout << endl;
	}
}

int main(void) {
	int num_element = /*num*/3;

	allSubsetBit(num_element);
	
	return 0;
}
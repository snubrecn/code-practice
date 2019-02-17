#include <iostream>

#define MAX_LEN 20

using namespace std;

int strLen(char* str) {
	int i = 0;
	while (str[i++]);
	return i - 1;
}

void strCpy(char* src, char* dst) {
	int i = 0;
	while (dst[i] = src[i++]);
}

int strCmp(char* s_1, char* s_2) {
	int i = 0;
	while (s_1[i]) {
		if (s_1[i] != s_2[i]) {
			break;
		}
		i++;
	}

	if (s_1[i] == '\0') return 0;
	
	
	if (s_1[i] > s_2[i]) {
		return 1;
	}
	else {
		return -1;
	}
}
//
int my_atoi(char* str) {
	int i = 0;
	int num;
	while (str[i]) {
		int decipher = str[i] - '0';
	}
}

//int my_itoa(int num, char* dst) {
//}

int main(void) {

	char str_1[MAX_LEN] = "what the hell?";
	char str_2[MAX_LEN] = "what the jell?";
	char str_3[MAX_LEN];

	cout << "Length of \'" << str_1 << "\' is " << strLen(str_1) << endl;
	cout << "Comparison between \'" << str_1 << "\' and \'" << str_2 << "\' is " << strCmp(str_1, str_2) << endl;

	strCpy(str_1, str_3);
	cout << "Copied string \'" << str_1 << "\', result is: \'" << str_3 << "\'\n";

	return 0;
}
#include <iostream>

#define MAX_LEN 30

using namespace std;

int strLen(char* str) {
	int i = 0;
	while (str[i++]);
	return i - 1;
}

void strCpy(char* src, char* dst) {
	while (*dst++ = *src++);
}

int strCmp(char* s_1, char* s_2) {
	int i = 0;
	while (s_1[i]) {
		if (s_1[i] != s_2[i]) {
			break;
		}
		i++;
	}

	if (s_1[i] > s_2[i]) {
		return 1;
	}
	else if (s_1[i] < s_2[i] {
		return -1;
	}
	return 0;
}

int my_atoi(char* str) {
	int i = 0;
	int sign = 1;

	int num = 0;

	while (str[i]) {
		if (i == 0) {
			if (str[i] == '-') {
				sign = -1;
				i++;
				continue;
			}
		}
		if (str[i] < '0' || str[i] > '9') {
			break;
		}
		int decipher = str[i] - '0';
		num = num * 10 + decipher;
		i++;
	}

	return sign * num;
}

void my_itoa(int num, char* dst) {
	int i = 0;
	int decipher = 0;
	int sign = 1;

	if (num == 0) {
		dst[i++] = '0';
		dst[i] = '\0';
		return;
	}
	else {
		if (num < 0) {
			num *= -1;
			sign = -1;
		}
	}

	while (num) {
		decipher = num % 10;
		num /= 10;
		dst[i++] = '0' + decipher;
	}

	for (int j = 0; j < i / 2; j++) {
		char tmp = dst[j];
		dst[j] = dst[i - j - 1];
		dst[i - j - 1] = tmp;
	}

	
	if (sign == -1) {
		for (int j = i; j--; j == 0) {
			dst[j + 1] = dst[j];
		}
		dst[0] = '-';
		i++;
	}
	
	dst[i] = '\0';
}

int main(void) {

	char str_1[MAX_LEN] = "what the hell?";
	char str_2[MAX_LEN] = "what the jell?";
	char str_3[MAX_LEN];
	char c_num[MAX_LEN] = "-17325";
	int i_num = -344120;
	char c_num2[MAX_LEN];

	cout << "Length of \'" << str_1 << "\' is " << strLen(str_1) << endl;
	cout << "Comparison between \'" << str_1 << "\' and \'" << str_2 << "\' is " << strCmp(str_1, str_2) << endl;

	strCpy(str_1, str_3);
	cout << "Copied string \'" << str_1 << "\', result is: \'" << str_3 << "\'\n";

	cout << "Number string " << c_num << " is integer " << my_atoi(c_num) << endl;

	my_itoa(i_num, c_num2);
	cout << "Integer number " << i_num << " is string number " << c_num2 << endl;

	return 0;
}
#include <iostream>

struct Trie {
    Trie() {
        is_terminal = false;
        cnt = 0;
        for (int i = 0; i < 26; ++i) next[i] = nullptr;
    }
    void Push(char* str) {
        if (str == nullptr) return;
        if (*str == '\0') {
            is_terminal = true;
            cnt++;
            return;
        }
        int idx = *str - 'a';
        if (next[idx] == nullptr) next[idx] = new Trie;
        next[idx]->Push(++str);
    }
    Trie* Find(char* str) {
        if (str == nullptr) return nullptr;
        if (*str == '\0') {
            if (is_terminal) return this;
            return nullptr;
        }
        int idx = *str - 'a';
        if (next[idx]) return next[idx]->Find(++str);
        return nullptr;
    }
    bool is_terminal;
    int cnt;
    Trie* next[26];
};

int main(void) {
    Trie* root = new Trie();

    char str_arr[][10] = {"abcd", "acbd", "bcd", "abce",
                       "acbabc", "db", "debt", "dell",
                       "debt", "debt", "debt", "debts",
                       "abcdd", "bcde", "dbs", "bced"};

    for (int i = 0; i < 16; ++i) root->Push(str_arr[i]);

    char str[10] = "bcde";

    Trie* p = root->Find(str);

    if (p == nullptr) std::cout << str << " does not exist\n";
    else std::cout << p->cnt << " " << str << " exist\n";

    return 0;
}


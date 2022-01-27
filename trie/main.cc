#include <iostream>

struct Trie {
    Trie() {
        cnt = 0;
        for (int i = 0; i < 26; ++i) next[i] = nullptr;
    }
    void Add(char* str) {
        if (str == nullptr) return;
        if (*str == '\0') {
            cnt++;
            return;
        }
        int idx = *str - 'a';
        if (next[idx] == nullptr) next[idx] = new Trie;
        next[idx]->Add(str + 1);
    }
    Trie* Find(char* str) {
        if (str == nullptr) return nullptr;
        if (*str == '\0') {
            if (cnt) return this;
            return nullptr;
        }
        int idx = *str - 'a';
        if (next[idx]) return next[idx]->Find(str + 1);
        return nullptr;
    }
    void Remove(char *str) {
        if (str == nullptr) return;
        if (*str == '\0') {
            cnt = 0;
            return;
        }
        int idx = *str - 'a';
        if (next[idx]) next[idx]->Remove(str + 1);
    }
    void Free() {
        for (int i = 0; i < 26; ++i)
            if (next[i]) next[i]->Free();
        delete this;
    }
    int cnt;
    Trie* next[26];
};

int main(void) {
    Trie* root = new Trie();

    char str_arr[][10] = {"abcd", "acbd", "bcd", "abce",
                       "acbabc", "db", "debt", "dell",
                       "debt", "debt", "debt", "debts",
                       "abcdd", "bcde", "dbs", "bced"};

    for (int i = 0; i < 16; ++i) root->Add(str_arr[i]);

    char str[10] = "bcds";

    Trie* p = root->Find(str);

    if (p == nullptr) std::cout << str << " does not exist\n";
    else std::cout << p->cnt << " " << str << " exist\n";

    root->Free();
    return 0;
}


#include <iostream>
#include <string>
using namespace std;

// Cấu trúc Trie Node
struct TrieNode {
    char character;
    int count;
    TrieNode* children[26];
    TrieNode(char ch) : character(ch), count(0) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};
// Hàm chèn một từ vào Trie
void insert(TrieNode*& root, const string& word) {
    if (!root) {
        root = new TrieNode('\0'); // Gốc rỗng
    }
    TrieNode* current = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (!current->children[index]) {
            current->children[index] = new TrieNode(ch);
        }
        current = current->children[index];
    }
    current->count++;
}
// Hàm duyệt Trie và lưu các từ cùng tần suất vào mảng
void traverse(TrieNode* node, string currentWord, string words[], int counts[], int& size) {
    if (!node) return;
    if (node->count > 0) {
        words[size] = currentWord;
        counts[size] = node->count;
        size++;
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            traverse(node->children[i], currentWord + node->children[i]->character, words, counts, size);
        }
    }
}
// Hàm sắp xếp các từ theo tần suất giảm dần (sắp xếp nổi bọt)
void sortWords(string words[], int counts[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (counts[j] < counts[j + 1]) {
                // Hoán đổi counts
                int tempCount = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tempCount;
                // Hoán đổi words
                string tempWord = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tempWord;
            }
        }
    }
}

int main() {
    int n, k;
    cout << "Nhap so luong tu: ";
    cin >> n;
    string* dict = new string[n];
    cout << "Nhap cac tu:\n";
    for (int i = 0; i < n; i++) {
        cin >> dict[i];
    }
    cout << "Nhap gia tri k: ";
    cin >> k;
    // Chèn các từ vào Trie
    TrieNode* root = nullptr;
    for (int i = 0; i < n; i++) {
        insert(root, dict[i]);
    }
    // Duyệt Trie và lưu các từ cùng tần suất
    string* words = new string[n];
    int* counts = new int[n];
    int size = 0;
    traverse(root, "", words, counts, size);
    // Sắp xếp các từ theo tần suất giảm dần
    sortWords(words, counts, size);
    // In ra k từ có tần suất cao nhất
    cout << "Cac tu xuat hien nhieu nhat:\n";
    for (int i = 0; i < k && i < size; i++) {
        cout << words[i] << " xuat hien " << counts[i] << " lan\n";
    }
    // Giải phóng bộ nhớ
    delete[] dict;
    delete[] words;
    delete[] counts;

    return 0;
}

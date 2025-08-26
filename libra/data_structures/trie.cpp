#include <bits/stdc++.h>
using namespace std;

/*
 * Pointer-based Trie for lowercase 'a'–'z' with:
 * - insert(word)
 * - search(word)
 * - startsWith(prefix)
 * - countWordsEqualTo(word)
 * - countWordsStartingWith(prefix)
 * - remove(word): only when word is present; decrements counts, unmarks end; does NOT free nodes.
 */

struct TrieNode {
    TrieNode* children[26];
    bool is_end;
    int prefix_count; // how many words pass through this node
    int end_count;    // how many words end exactly at this node
    TrieNode() {
        is_end = false;
        prefix_count = 0;
        end_count = 0;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie.
    void insert(const string &word) {
        TrieNode* node = root;
        node->prefix_count++;
        for (char ch : word) {
            int idx = ch - 'a';
            if (idx < 0 || idx >= 26) {
                // Skip invalid characters (assuming only lowercase expected)
                continue;
            }
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->prefix_count++;
        }
        node->is_end = true;
        node->end_count++;
    }

    // Search if a full word is present in the trie.
    bool search(const string &word) const {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (idx < 0 || idx >= 26 || !node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return node->is_end;
    }

    // Check if there is any word that starts with the given prefix.
    bool startsWith(const string &prefix) const {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (idx < 0 || idx >= 26 || !node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }

    // Count how many times the exact word was inserted (minus removes).
    int countWordsEqualTo(const string &word) const {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (idx < 0 || idx >= 26 || !node->children[idx]) {
                return 0;
            }
            node = node->children[idx];
        }
        return node->end_count;
    }

    // Count how many words currently in the trie start with the given prefix.
    int countWordsStartingWith(const string &prefix) const {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (idx < 0 || idx >= 26 || !node->children[idx]) {
                return 0;
            }
            node = node->children[idx];
        }
        return node->prefix_count;
    }

    // Simplified remove: only called when word is known to be present.
    // It:
    //  - walks the path, collecting nodes in a vector
    //  - if end_count > 0 at terminal, decrements end_count and possibly unmarks is_end
    //  - decrements prefix_count along the path
    //  - does NOT free any nodes
    void remove(const string &word) {
        TrieNode* node = root;
        vector<TrieNode*> path;
        path.reserve(word.size() + 1);
        path.push_back(root);

        for (char ch : word) {
            int idx = ch - 'a';
            if (idx < 0 || idx >= 26 || node->children[idx] == nullptr) {
                return;
            }
            node = node->children[idx];
            path.push_back(node);
        }
        if (node->end_count == 0) {
            return;
        }

        node->end_count--;
        if (node->end_count == 0) {
            node->is_end = false;
        }

        for (TrieNode* nd : path) {
            nd->prefix_count--;
        }

    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Trie trie;
    int Q;
    if (!(cin >> Q)) return 0;
    while (Q--) {
        string cmd, s;
        cin >> cmd >> s;
        if (cmd == "insert") {
            trie.insert(s);
        }
        else if (cmd == "search") {
            bool found = trie.search(s);
            cout << (found ? "Found\n" : "Not Found\n");
        }
        else if (cmd == "prefix") {
            bool ok = trie.startsWith(s);
            cout << (ok ? "Yes\n" : "No\n");
        }
        else if (cmd == "countEq") {
            int cnt = trie.countWordsEqualTo(s);
            cout << cnt << "\n";
        }
        else if (cmd == "countPre") {
            int cnt = trie.countWordsStartingWith(s);
            cout << cnt << "\n";
        }
        else if (cmd == "delete") {
            // Optional: you could check if present first, but remove() handles absence safely
            trie.remove(s);
            // Example feedback:
            // cout << "Removed one occurrence of: " << s << "\n";
        }
        else {
            // Unknown command: ignore or handle error
            // cerr << "Unknown command: " << cmd << "\n";
        }
    }

    return 0;
}

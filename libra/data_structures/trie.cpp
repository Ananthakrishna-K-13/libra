struct TrieNode {
    TrieNode* children[26];
    bool is_end;
    int prefix_count;
    int end_count;
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

    void insert(const string &word) {
        TrieNode* node = root;
        node->prefix_count++;
        for (char ch : word) {
            int idx = ch - 'a';
            if (idx < 0 || idx >= 26) {
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
// Trie trie;

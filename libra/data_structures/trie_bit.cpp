struct BitTrieNode {
    BitTrieNode* child[2];
    int count;
    BitTrieNode() {
        child[0] = child[1] = nullptr;
        count = 0;
    }
};
class BitTrie {
private:
    BitTrieNode* root;
    static const int BIT_LEN = 31;

public:
    BitTrie() {
        root = new BitTrieNode();
    }

    void insert(int x) {
        BitTrieNode* node = root;
        node->count++;
        for (int b = BIT_LEN - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (!node->child[bit]) {
                node->child[bit] = new BitTrieNode();
            }
            node = node->child[bit];
            node->count++;
        }
    }
    void remove(int x) {
        if (!contains(x)) {
            return;
        }
        BitTrieNode* node = root;
        node->count--;
        for (int b = BIT_LEN - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            BitTrieNode* nxt = node->child[bit];
            nxt->count--;
            node = nxt;
        }
    }
    bool contains(int x) const {
        BitTrieNode* node = root;
        for (int b = BIT_LEN - 1; b >= 0; b--) {
            if (!node) return false;
            int bit = (x >> b) & 1;
            if (!node->child[bit] || node->child[bit]->count == 0) {
                return false;
            }
            node = node->child[bit];
        }
        return node && node->count > 0;
    }
    int maxXor(int x) const {
        BitTrieNode* node = root;
        int result = 0;
        for (int b = BIT_LEN - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int desired = bit ^ 1; 
            if (node->child[desired] && node->child[desired]->count > 0) {
                result |= (1 << b);
                node = node->child[desired];
            } else if (node->child[bit] && node->child[bit]->count > 0) {
                node = node->child[bit];
            } else {
                break;
            }
        }
        return result;
    }
};
// BitTrie trie;
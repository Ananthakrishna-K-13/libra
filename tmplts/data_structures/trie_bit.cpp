#include <bits/stdc++.h>
using namespace std;

/*
 * BitTrie: a binary trie for non-negative integers.
 * Supports:
 *  - insert(x): insert integer x into the trie.
 *  - remove(x): remove one occurrence of x (assumes x was inserted at least once).
 *  - contains(x): check if x is present (count > 0).
 *  - maxXor(x): find the integer in trie that maximizes (x XOR y). Assumes trie is non-empty.
 *
 * Internals:
 *  - Each node has two children pointers: children[0] and children[1].
 *  - We store a count at each node: how many inserted numbers pass through this node.
 *  - Depth: for 32-bit integers, we typically use bits 30..0 (31 bits) if inputs fit in signed 32-bit.
 *    You can adjust BIT_LEN if you need more bits.
 *  - remove(x) simply walks the path of x, decrements counts, and does NOT free nodes. 
 *    This is simpler in CP; total nodes allocated stays within limits if total distinct prefixes is bounded.
 */

struct BitTrieNode {
    BitTrieNode* child[2];
    int count; // how many numbers pass through this node
    BitTrieNode() {
        child[0] = child[1] = nullptr;
        count = 0;
    }
};

class BitTrie {
private:
    BitTrieNode* root;
    static const int BIT_LEN = 31; 
    // Use 31 if numbers are up to < 2^31. 
    // For unsigned 32-bit, you might use 32 bits (0..31). Adjust as needed.

public:
    BitTrie() {
        root = new BitTrieNode();
    }

    // Insert x into trie
    void insert(int x) {
        BitTrieNode* node = root;
        node->count++;
        // Traverse from most significant bit to least
        for (int b = BIT_LEN - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (!node->child[bit]) {
                node->child[bit] = new BitTrieNode();
            }
            node = node->child[bit];
            node->count++;
        }
    }

    // Remove one occurrence of x. Assumes x was inserted at least once.
    // If x is not present, this does nothing.
    void remove(int x) {
        if (!contains(x)) {
            return;
        }
        BitTrieNode* node = root;
        node->count--;
        for (int b = BIT_LEN - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            BitTrieNode* nxt = node->child[bit];
            // nxt must be non-null since contains(x) was true
            nxt->count--;
            // We do NOT free nodes even if count becomes 0
            node = nxt;
        }
    }

    // Check if x is present (i.e., was inserted more times than removed)
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
        // If we reach here, path exists with positive counts. No explicit 'end' flag, 
        // but since we increment count at leaf, count>0 implies presence.
        return node && node->count > 0;
    }

    // Query for maximum XOR: find y in trie that maximizes x ^ y.
    // Assumes trie is non-empty (i.e., at least one number has been inserted and not fully removed).
    int maxXor(int x) const {
        BitTrieNode* node = root;
        int result = 0;
        for (int b = BIT_LEN - 1; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int desired = bit ^ 1; // prefer opposite bit to maximize XOR
            if (node->child[desired] && node->child[desired]->count > 0) {
                // we can go this way
                result |= (1 << b);
                node = node->child[desired];
            } else if (node->child[bit] && node->child[bit]->count > 0) {
                node = node->child[bit];
                // result bit remains 0 at position b
            } else {
                // No valid path? Shouldn't happen if trie is non-empty and counts maintained correctly.
                break;
            }
        }
        return result;
    }
};

// Example of usage in main for CP:
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BitTrie trie;
    // Example: read Q queries of form:
    // 1 x  => insert x
    // 2 x  => remove x
    // 3 x  => query max xor with x, print result
    // 4 x  => check contains x, print "Yes"/"No"
    int Q;
    if (!(cin >> Q)) return 0;
    while (Q--) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            trie.insert(x);
            // cout << "Inserted " << x << "\n"; // optional feedback
        } else if (type == 2) {
            trie.remove(x);
            // cout << "Removed " << x << "\n";
        } else if (type == 3) {
            // Ensure trie is non-empty before calling
            // If empty, behavior is undefined; handle separately if needed
            int ans = trie.maxXor(x);
            cout << ans << "\n";
        } else if (type == 4) {
            bool ok = trie.contains(x);
            cout << (ok ? "Yes\n" : "No\n");
        }
        // else: ignore invalid type
    }
    return 0;
}

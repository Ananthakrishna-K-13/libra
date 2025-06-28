// faster than normal trie but not memeroy efficinet as there is no deletions


#include<bits/stdc++.h>
using namespace std;


const int MAX_BITS = 31; // For 32-bit integers (bit positions 0–30)

struct TrieNode {
    int next[2] = {-1, -1}; // next[0] and next[1]
    int count = 0;          // number of elements passing through this node
};

struct BitTrie {
    vector<TrieNode> trie;

    BitTrie() {
        trie.emplace_back(); // root node at index 0
    }

    void insert(int num) {
        int node = 0;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (trie[node].next[bit] == -1) {
                trie[node].next[bit] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].next[bit];
            trie[node].count++;
        }
    }

    int maxXor(int num) {
        int node = 0, result = 0;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int opposite = bit ^ 1;
            if (trie[node].next[opposite] != -1 &&
                trie[trie[node].next[opposite]].count > 0) {
                result |= (1 << i);
                node = trie[node].next[opposite];
            } else if (trie[node].next[bit] != -1) {
                node = trie[node].next[bit];
            } else {
                break; // shouldn't happen if num was previously inserted
            }
        }
        return result;
    }
};

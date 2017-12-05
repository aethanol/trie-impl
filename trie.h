// Ethan Anderson
// cse374 - hw5
// This is the header file for an autocomplete program implemented with a trie

#ifndef TRIE_H
#define TRIE_H

#define MAX_WORD_LEN 500
#define ALPHABET_LEN 128

// trieNode is a struct that represents a word and/or a pointer
// to other words in the trie
typedef  struct trieNode {
    // NULL if the node is not a leaf
    char *word;
    // array of pointers other nodes in the trie
    struct trieNode *children[ALPHABET_LEN];
}TrieNode;

// newNode allocates a new Trie node at a given pointer
// and initalizes it's data fields
TrieNode* newNode(TrieNode *child);

// addWord adds a newWord to the Trie. It takes in a pointer to the root
// of the Trie and a word that is going to be added
TrieNode* addWord(TrieNode *root, const char *string);

// search searches a Trie starting at a root node for all words that begin with a prefix
void search(TrieNode *root, const char *prefix);

// printTrie prints an entire trie from the node that it is passed
void printTrie(TrieNode *root);

// freeTrie recurseively frees all allocated data in a given Trie
void freeTrie(TrieNode *root);

#endif

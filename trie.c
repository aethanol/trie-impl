// Ethan Anderson
// cse374 - hw5
// This is a file that defines a Trie data structure in C.
// It was completed as part of a homework assignment for cse 374

#include "trie.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// newNode allocates a new Trie node at a given pointer
// and initalizes it's data fields
TrieNode* newNode(TrieNode *child) { 
    // allocate a new trieNode and handle the error
    child = (TrieNode*) malloc(sizeof(TrieNode));
    if (child == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(1);
    }
    // make sure to init the children array
    // and the word at the node
    child->word = NULL;
    for (int i = 0; i < ALPHABET_LEN; i++) {
        child->children[i] = NULL;
    }
    // return the newly allocated child
    return child;
}

// freeTrie recurseively frees all allocated data in a given Trie
void freeTrie(TrieNode *root) {
    // recurse on every child if the current node isn't null
    if (root != NULL) {
        for (int i = 0; i < ALPHABET_LEN; i++) {
            freeTrie(root->children[i]);
        }
        // free the word if it exists
        if (root->word != NULL) {
            free(root->word);
        }
        // free the node
        free(root);
    }
}

// addWord adds a newWord to the Trie. It takes in a pointer to the root
// of the Trie and a word that is going to be added
TrieNode* addWord(TrieNode *root, const char *newWord) {
    // make sure that root and the string are not null
    if (root == NULL || newWord == NULL) {
        fprintf(stderr, "Error adding word\n");
        exit(1);
    }
    
    // get a pointer to the current node
    TrieNode *curr = root;
    
    // get the length of the new word so we can add each character
    int len = strlen(newWord);
    
    // iterate through each character of the newWord and add it as a trieNode
    for(int i = 0; i < len; i++) {
        // get the child of the current trie at the curr char
        TrieNode  *child = curr->children[(int)newWord[i]];

        // check if there isnt already a node at the next char
        if (curr->children[(int)newWord[i]] == NULL) {
            // allocate a new node for that child
            child = newNode(curr->children[(int)newWord[i]]);
            // set the child of curr
            curr->children[(int)newWord[i]] = child;
        }
        // go to the new child to continue the loop
        curr = child;
    }

    // at the end of the path
    // allocate a new word if it doesn't exist already
    if(curr->word == NULL) {
        // calloc a new word pointer with a null byte at the end
        curr->word = (char*) calloc((len+1), sizeof(char));
        if (curr->word == NULL) {
            fprintf(stderr, "Error: out of memory\n");
            exit(1);
        }
        // copy in the string to the new child we created (because created with calloc the null byte is implicit)
        strcpy(curr->word, newWord);
    }
    return root;
}

// search searches a Trie starting at a root node for all words that begin with a prefix
void search(TrieNode *root, const char *prefix) {
    // check the error
    if(root == NULL) {
        fprintf(stderr, "No trie provided to search\n");
    }
    
    // get the length and traverse the trie to the end of the prefix
    int len = strlen(prefix);
    for(int i = 0; i < len; i++) {
        // get the child for each char of the prefix
        // and exit if we ever run into the end of the trie
        // in that case there are no valid words with that prefix
        root = root->children[(int)prefix[i]];
        if (root == NULL) {
            printf("No words start with %s\n", prefix);
            return;
        }
    }
    // if we get to a valid point print the rest of the trie from there (will include all words that start with prefix
    printTrie(root);
} 

// printTrie prints an entire trie from the node that it is passed
void printTrie(TrieNode *root) {
    // at the end of a path return from the callstack
    if (root == NULL ) {
        return;
    }
    // recurse on every child
    for (int i = 0; i < ALPHABET_LEN; i++) {
        printTrie(root->children[i]);
    }
    // print the word if there is one
    if (root->word != NULL) {
        printf("%s\n",root->word);
    }
}
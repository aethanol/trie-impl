// Ethan Anderson
// cse374 - hw5
// This is the main file for an autocomplete program implemented
// with a trie.

#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// buildTrie opens a file and builds a trie from each line in it
TrieNode* buildTrie(char *fname);

// userInput prompts a user for input and exits on EOF (ctrl-D)
void userInput();

int main (int argc, char *argv[]) {
    // check that the user provided adequate input
    if (argc != 2) {
        fprintf(stderr, "usage: %s FILE\n", argv[0]);
        exit(1);
    }

    // build the trie with the file parameter given
    TrieNode *root = buildTrie(argv[1]);
    userInput(root);

    // free up all of the allocated memory to prevent memory leaks
    freeTrie(root);
    return 0;
}

// userInput prompts a user for input to search the trie for prefix
// and exits on EOF (ctrl-D)
void userInput(TrieNode *root) {
    // create a buffer to get the user input into
    char prefix[MAX_WORD_LEN];
    // read until EOF
    while (fgets(prefix, sizeof(prefix), stdin)) {
        // remove any newlines from fgets
        prefix[strcspn(prefix, "\n")] = 0;
        // search for that prefix
        search(root, prefix);
    }
}

TrieNode* buildTrie(char *fname) {
    // attempt to open the file that the user passed
    FILE *file;
    if ( (file = fopen (fname, "r")) == NULL ) {
        fprintf(stderr, "%s could not be opened\n", fname);
        exit(1);
    }
    
    // create a new root for the trie
    TrieNode *root = NULL;
    root = newNode(root);
    
    // add a new trieNode for every word in the file
    char word[MAX_WORD_LEN];
    while ( fgets(word, sizeof(word), file) != NULL ) {
        // remove any newlines from fgets
        word[strcspn(word, "\n")] = 0;
        // if the word is greater than zero add it
        if (strlen(word) > 0) {
            root = addWord(root, word);
        }
    }
    // make sure to close the file
    fclose(file);

    // return the root of the trie
    return root;
}


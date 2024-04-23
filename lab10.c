#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    struct TrieNode *children[26]; // Assuming English alphabet
    int isEndOfWord;
};

// Trie structure
struct Trie
{
    struct TrieNode *root;
};

// Create a new Trie node
struct TrieNode *createNode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node)
    {
        node->isEndOfWord = 0;
        for (int i = 0; i < 26; i++)
            node->children[i] = NULL;
    }
    return node;
}

// Inserts the word into the trie
void insert(struct Trie *pTrie, char *word)
{
    struct TrieNode *current = pTrie->root;
    int index;
    for (int i = 0; word[i] != '\0'; i++)
    {
        index = word[i] - 'a';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct TrieNode *current = pTrie->root;
    int index;
    for (int i = 0; word[i] != '\0'; i++)
    {
        index = word[i] - 'a';
        if (!current->children[index])
            return 0;
        current = current->children[index];
    }
    return current->isEndOfWord;
}

// Deallocate memory for the Trie
struct Trie *deallocateTrie(struct Trie *pTrie)
{

    void deallocateNode(struct TrieNode * node)
    {
        if (!node)
            return;
        for (int i = 0; i < 26; i++)
            deallocateNode(node->children[i]);
        free(node);
    }

    if (pTrie)
    {
        deallocateNode(pTrie->root);
        free(pTrie);
    }
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (pTrie)
    {
        pTrie->root = createNode();
    }
    return pTrie;
}

// Read the dictionary file
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    int numWords = 0;
    char word[256]; // Assuming maximum word length is 255 characters
    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = strdup(word); // Store a copy of the word
        numWords++;
    }
    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}

// Implements a dictionary's functionality

#include "dictionary.h"

// personally enhanced Larson hash, which I found on https://www.strchr.com/hash_functions
uint32_t hasher(const char *key, size_t len)
{
    uint32_t hash = 0;
    for (uint32_t i = 0; i < len; ++i)
    {
        hash = 101 * hash + key[i];
    }
    return hash % BUCKETS;
}

// create a hashtable and set buckets to NULL
node *hashtable[BUCKETS];

// boolean for checking if the dictionary is loaded or not.
bool loaded = false;

// create word counter
unsigned int word_count;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // get word length
    int word_length = strlen(word);
    // copy the word to be used, contents of a constant char are immutable
    char word_copy[word_length + 1];

    // create a lowercased copy of the word
    for (int i = 0; i < word_length; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    // add the null terminator to the word
    word_copy[word_length] = '\0';

    // calculate word hash
    unsigned int hash = hasher(word_copy, word_length);

    // set a pointer on the index/hash of the hashtable
    node *ptr = hashtable[hash];

    // look until pointer returns NULL / so nothing found
    while (ptr != NULL)
    {
        // compare the 2 words, 0 == equal
        if (strcmp(ptr->word, word_copy) == 0)
        {
            // word in dictionary
            return true;
        }
        else
        {
            // check next node
            ptr = ptr->next;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    // open the dictionary file
    FILE *dic_file = fopen(dictionary, "r");

    if (dic_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // read the dictionary word for word
    while (fscanf(dic_file, "%s", word) != EOF)
    {
        // hash the word
        int word_length = strlen(word);
        unsigned int hash = hasher(word, word_length);

        // create a node for the word
        node *new_node = malloc(sizeof(node));
        new_node->next = NULL;

        // check in case new node could not be created
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // copy the word to the node
        strncpy(new_node->word, word, word_length + 1);
        new_node->word[word_length] = '\0';

        // put node in the hashtable
        // first create a pointer to the hash/index in the hashtable
        node *ptr = hashtable[hash];

        // if it's an empty bucket, insert the node
        if (ptr == NULL)
        {
            hashtable[hash] = new_node;
        }
        // if bucket isn't empty, insert it in first position
        // check Doug Lloyds video on single linked lists
        // and hashtables regarding this choice
        else
        {
            new_node->next = hashtable[hash];
            hashtable[hash] = new_node;
        }
        // increase word counter
        word_count++;
    }

    // close the dictionary file
    fclose(dic_file);

    // set loaded to true when dictionary is loaded
    loaded = true;

    // all worked out
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < BUCKETS; i++)
    {
        node *ptr = hashtable[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    loaded = false;
    return true;
}
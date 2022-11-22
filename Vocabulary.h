#pragma once

#include <string>
#include <vector>

static const int ALPHABET_SIZE = 26; 
  
// Структура узела дерева 
class TrieNode
{ 
private:
    TrieNode *children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;

public:
    TrieNode();

    TrieNode *get_children(int index);
    TrieNode *getNewNode();
    void insert(std::string key);
    bool search(std::string key);
    bool isEmpty(TrieNode* current);
    TrieNode* remove(TrieNode*, std::string, int depth = 0);
    void correcting_word(std::string& key);
    void search_affix(std::vector<std::string>& similar_word, TrieNode* current, std::string& buffer, int index);
    void search_similar_word(std::string key, std::vector<std::string>& similar_word, std::string buffer = "", int index = 0);

    ~TrieNode();
};

#include <iostream>
#include <bits/stdc++.h>
#include "Vocabulary.h"
#include <vector>

// конструктор
TrieNode::TrieNode()
{
    this -> isEndOfWord = false;
    for(int i = 0; i < ALPHABET_SIZE; ++i)
        this -> children[i] = nullptr;
}

//возвращает новый узел с пустыми детьми
TrieNode* TrieNode::getNewNode()
{
    // Выделяем память по новый узел
    TrieNode *pNode =  new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode -> isEndOfWord = false; 

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = nullptr;

    return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void TrieNode::insert(std::string key) 
{
    TrieNode* node = this; 

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a'; 

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node -> children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
bool TrieNode::search(std::string key) 
{ 
    TrieNode *node = this; 

    for (int i = 0; i < key.length(); i++) 
    {
        int index = key[i] - 'a'; 
        if (!node->children[index]) 
            return false;

        node = node->children[index]; 
    }

    return (node != nullptr && node->isEndOfWord); 
}

// Вохвращает true если root имеет лист, иначе false 
bool TrieNode::isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
} 

// Рекурсивная функция удаления ключа из дерева 
TrieNode* TrieNode::remove(TrieNode* root, std::string key, int depth) 
{ 
    // Если дерево пустое 
    if (!root)
        return nullptr;
  
    // если дошли до конца ключа 
    if (depth == key.size()) { 
  
        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false; 
  
        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) { 
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1); 
  
    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) { 
        delete (root);
        root = nullptr; 
    }
  
    // возвращаем новый корень
    return root; 
}

//функция автоисправления слова
void TrieNode::correcting_word(std::string& key)
{
    std::string buffer;
    TrieNode* current = this;
    for(int i = 0; i < key.length(); ++i)
    {
        if(current -> children[key[i] - 'a'] != nullptr)
        {
            buffer += key[i];
            current = current -> children[key[i] - 'a'];
        }
        else if(i == key.length() - 1)
        {
            for(int j = 0; j < ALPHABET_SIZE; ++j)\
            {
                if(current -> children[j] != nullptr && current -> children[j] -> isEndOfWord == true)
                    buffer += j + 'a';
            }
        }
        else
        {
            for(int j = 0; j < ALPHABET_SIZE; ++j)
            {
                if(current -> children[j] != nullptr)
                {
                    if(current -> children[j] -> children[key[i + 1] - 'a'] != nullptr)
                    {
                        buffer += j + 'a';
                        buffer += key[i + 1];
                        current = current -> children[j] -> children[key[i + 1] - 'a'];
                        ++i;
                    }
                }
            }
        }
    }
    if(buffer.length() == key.length() && current -> isEndOfWord == true)
    {
        key = buffer;
    }
    else
    {
        for(int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if(current -> children[i] != nullptr)
            {
                buffer += i + 'a';
                current = current -> children[i];
                i = -1;
            }
            if(current -> isEndOfWord == true)
                break;
        }
        key = buffer;
    }
}

//рекурсивная функция поиска суффиксов слова
void TrieNode::search_affix(std::vector<std::string>& similar_word, TrieNode* current, std::string& buffer, int index)
{
    if(current -> isEndOfWord == true)
        similar_word.emplace_back(buffer);
    for(int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if(current -> children[i] != nullptr)
        {
            if(index < buffer.length())
                buffer.at(index) = i + 'a';
            else
                buffer += i + 'a';
            search_affix(similar_word, (current -> children[i]), buffer, (index + 1));
        }
    }
}

//функция поиска совпадающих слов
void TrieNode::search_similar_word(std::string key, std::vector<std::string>& similar_word, std::string buffer, int index)
{
    TrieNode *current = this;
    for(int i = 0; i < key.length(); ++i)
    {
        if(current -> children[key[i] - 'a'] != nullptr)
        {
            current = current -> children[key[i] - 'a'];
            buffer += key[i];
            ++index;
        }
    }
    if(current != this)
    {
        search_affix(similar_word, current, buffer, index);
    }
    else
    {
        insert(key);
    }
}

//Деструктор
TrieNode::~TrieNode()
{
    for(int i = 0; i < ALPHABET_SIZE; ++i)
        if(this -> children[i] != nullptr)
            delete this -> children[i];
}
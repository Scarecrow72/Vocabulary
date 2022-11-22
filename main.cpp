#include <iostream>
#include "Vocabulary.h"
#include <string>
#include <vector>

int main()
{
    TrieNode vocabulary;

    std::string key = "enter";
    vocabulary.insert(key);
    key = "hello";
    vocabulary.insert(key);
    key = "program";
    vocabulary.insert(key);
    key = "mother";
    vocabulary.insert(key);
    key = "similar";
    vocabulary.insert(key);
    std::vector<std::string> similar_word;

    bool key_change {true};
    std::cout << "The program of auto-correction and auto-completion of words." << std::endl;
    std::cout << "To enable/disable the automatic word correction function, enter ~." << std::endl;
    std::cout << "To auto-complete words, select a word from the suggested list for each word of the entered string." << std::endl;
    
    while (true)
    {
        std::cout << "For escape the program, enter /" << std::endl;
        std::cout << "Enter ~ for enable/disable the automatic word correction" << std::endl;
        std::cout << "Or enter your text" << std::endl;
        std::string text;
        while(text.empty())
        {
            std::getline(std::cin, text);
        }
        if(text == "~")
        {
            if(key_change)
            {
                std::cout << "Auto-correction function disabled" << std::endl;
                key_change = false;
            }
            else
            {
                std::cout << "Auto-correction function enabled" << std::endl;
                key_change = true;
            }
            continue;
        }
        if(text == "/")
            break;
        int index {0};
        
        while(index < text.length())
        {
            int start_index {index};
            std::string buffer;
            while(text[index] != ' ' && index < text.length())
            {
                buffer += text[index++];
            }
            if(buffer.empty())
                continue;
            if(key_change)
            {
                vocabulary.correcting_word(buffer);
            }
            else
            {
                similar_word.emplace_back(buffer);
                vocabulary.search_similar_word(buffer, similar_word);
                if(!similar_word.empty() )
                {
                    for(int i = 0; i < similar_word.size(); ++i)
                    {
                        std::cout << i << " - " << similar_word.at(i) << std::endl;
                    }
                    std::cout << "Enter the number of the appropriate word: ";
                    int word_number;
                    std::cin >> word_number;
                    if(word_number > 0 && word_number < similar_word.size())
                    {
                        if(word_number == 0)
                            vocabulary.insert(similar_word.at(0));
                        buffer = similar_word.at(word_number);
                    }
                }
            }
            std::string new_text;
            for(int i = 0; i < start_index; ++i)
                new_text += text[i];
            new_text += buffer;
            for(int i = index; i < text.length(); ++i)
                new_text += text[i];
            index = start_index + buffer.length();
            text.clear();
            text = new_text;
            new_text.clear();
            buffer.clear();
            ++index;
            similar_word.clear();
        }
        std::cout << "Your corrected text: " << text << std::endl;
    }
    
    return 0;
}
#pragma once
#include <string>
#include <vector>

using Tokens = std::vector<std::string>;

class Tokenizer{
private:
    std::string text;
    Tokens tokens;
public:
    Tokenizer(std::string text) : text(text){}
    Tokens tokenize(){
        tokens.clear();
        std::string current;
        for (char c : text){
            if (c!=' '){
                current.push_back(c);
            }
            else{
                tokens.push_back(current);
                current.clear();
            }
        }
        if(current != "") {
            tokens.push_back(current);
        }
        return tokens;
    }
};
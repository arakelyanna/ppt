#include "Tokenizer.h"


bool prs::Token::is_string() const{
    return type == TokenType::String;
}

bool prs::Token::is_option() const{
    
    return type == TokenType::Option;
}

bool prs::Token::is_number() const{
    return type == TokenType::Number;
    
}

bool prs::Token::is_bool() const{
    return type == TokenType::Boolean;
}



const std::string prs::Tokenizer::read_word() {
    char c;
    std::string result ="";
    while(input.get(c)){
        if (isspace(c) || c==',') break;

        result.push_back(c);  
        ++position;  
        check_length();

    }
    return result;
}

const std::string prs::Tokenizer::read_string() {
    char c;
    std::string result = "";
    while(input.get(c)){
        if (c == '"') break;
        
        result.push_back(c);  
        ++position;
        if (input.eof() && c != '"')
        {
            throw std::runtime_error("Unterminated string literal");
        }
        check_length();
        
    }
    return result;
}


const std::string prs::Tokenizer::read_number() {
    char c;
    std::string result = "";
    while(input.get(c)){
        if (isspace(c) || c==',') break;

        if(c == '.' || c=='e' || c=='E' || isdigit(c)){
            result.push_back(c);
            ++position;
        }
        else{
            throw std::runtime_error("Invalid number format");
        }
        check_length();
    }
    return result;
}


prs::Token prs::Tokenizer::getToken(){    
    std::string word;
    Token tok;

    if (input.fail()) {
        throw std::runtime_error("Input stream error");
    }
    else if (input.eof())
    {
        tok.value = "";
        tok.type = TokenType::Eof;
        return tok;
    }
    
    char c;
    
    c = input.get();
    position++;

    if (c == '-')
    {
        tok.value.push_back(c);
        c = input.peek();

        if(isdigit(c)){
            tok.type= TokenType::Number;
            tok.value = read_number();
        }
        else {
            tok.type = TokenType::Option;
            tok.value = read_word();
        }
    }
    else if(c =='"')
    {
        tok.type=TokenType::String;
        tok.value = read_string();
    }
    else if (c == 't' || c=='f')
    {
        input.unget();
        --position;

        std::string word;
        input >> word;

        tok.type = (word == "true" || word == "false") ? TokenType::Boolean : TokenType::Command;
        tok.value= word;
    }
    else if(isdigit(c)){
        input.unget();
        --position;

        tok.type = TokenType::Number;
        tok.value = read_number();
    }
    else{
        input.unget();
        --position;
        tok.type = TokenType::Command;
        tok.value = read_word();
    }
    
    return tok;
}

void prs::Tokenizer::check_length() const {
    if (position > 50)
        throw std::runtime_error("ERROR: Command length should not be greater than 50!");
}
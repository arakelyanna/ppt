#include "Tokenizer.h"


bool dec::Token::is_string() const{
    return type == TokenType::String;
}

bool dec::Token::is_option() const{
    
    return type == TokenType::Option;
}

bool dec::Token::is_number() const{
    return type == TokenType::Number;
    
}

bool dec::Token::is_bool() const{
    return type == TokenType::Boolean;
}

bool dec::Token::eof() const{
    return type == TokenType::Eof;
}

bool dec::Token::err() const{
    return type == TokenType::Err;
}

const std::string dec::CLI_Tokenizer::read_word() {
    char c;
    std::string result ="";
    while(buffer.get(c)){
        if (isspace(c) || c==',') {
            // buffer.unget();
            break;
        }
        result.push_back(c);  
        ++position;
        check_length();

    }
    return result;
}

const std::string dec::CLI_Tokenizer::read_string() {
    char c;
    std::string result = "";
    while(buffer.get(c)){
        if (c == '"'){ break;}
        
        result.push_back(c);  
        ++position;
        if (buffer.eof() && c != '"')
        {
            throw std::runtime_error("Unterminated string literal");
        }
        check_length();
        
    }
    return result;
}


const std::string dec::CLI_Tokenizer::read_number() {
    char c;
    std::string result = "";
    while(buffer.get(c)){
        if (isspace(c) || c==',') {
            // buffer.unget();
            break;
        }

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


dec::Token dec::CLI_Tokenizer::getToken(){    
    Token tok;
    char c;
    while(buffer.get(c) && isspace(c)) {
        position++;
    }
    if (buffer.eof()) {
        tok.value = "";
        tok.type = TokenType::Eof;
        std::cout << c << '\n';
        return tok;
    }
    if (buffer.fail()) {
        throw std::runtime_error("Input stream error");
    }
    


    if (c == '-')
    {
        
        if(isdigit(buffer.peek())){
            tok.value.push_back(c);
            tok.type= TokenType::Number;
            tok.value.append(read_number());
        }
        else {
            tok.type = TokenType::Option;
            tok.value.append(read_word());
        }
    }
    else if(c =='"')
    {
        tok.type=TokenType::String;
        tok.value = read_string();
        buffer.get(c); 
        position++;
    }
    else if (c == 't' || c=='f')
    {
        buffer.unget();
        --position;

        std::string word;
        buffer >> word;
        position += word.length();

        tok.type = (word == "true" || word == "false") ? TokenType::Boolean : TokenType::Command;
        tok.value= word;
    }
    else if(isdigit(c)){
        buffer.unget();
        --position;

        tok.type = TokenType::Number;
        tok.value = read_number();
    }
    else{
        buffer.unget();
        --position;
        tok.type = TokenType::Command;
        tok.value = read_word();
    }
    
    return tok;
}


void dec::CLI_Tokenizer::check_length() const {
    if (position > 50)
        throw std::runtime_error("ERROR: Command length should not be greater than 50!");
}
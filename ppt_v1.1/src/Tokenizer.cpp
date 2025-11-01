#include <vector>
#include "Tokenizer.h"


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


const std::string dec::CLI_Tokenizer::read_coord() {
    char c;
    std::string result;
    skip_spaces();

    result = read_number();
    
    skip_spaces();
    if (tok.type == TokenType::Number && c!=')')
    {
        throw std::runtime_error("ERROR: missing closing parenthesis");
    }
}
const std::string dec::CLI_Tokenizer::read_number() {
    char c;
    std::string result = "";
    while(buffer.get(c)){
        if (isspace(c) || c==',') break;

        if(c == '.' || c=='e' || c=='E' || isdigit(c)){
            result.push_back(c);
            ++position;
        }
        else{
            std::cout << c << '\n';
            throw std::runtime_error("Invalid number format");
        }
        check_length();
    }
    return result;
}

void dec::CLI_Tokenizer::skip_spaces(){
    char c;
    while(buffer.get(c) && isspace(c)) {
        position++;
    }
    
}

dec::Token& dec::CLI_Tokenizer::getToken(){
    char c;
    skip_spaces();
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
    else if (c == '(')
    {

        
        tok.type = TokenType::Number;
        tok.value = read_coord();
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
    else if(isalpha(c)){
        buffer.unget();
        --position;
        tok.type = TokenType::Command;
        tok.value = read_word();
    }
    else{
        throw std::runtime_error("ERROR: unexpected symbol at " + std::to_string(position));
    }
    return tok;
}


void dec::CLI_Tokenizer::check_length() const {
    if (position > 50)
        throw std::runtime_error("ERROR: Command length should not be greater than 50!");
}
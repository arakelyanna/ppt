#include "Tokenizer.h"


bool prs::Token::is_string() const{

}

bool prs::Token::is_option() const{

}

bool prs::Token::is_number() const{

}

bool prs::Token::is_bool() const{

}



const std::string prs::Tokenizer::read_word() {
    char c;
    std::string result;
    while(input.good() && !iswspace(c)){
        result.push_back(c);  
        ++position;      
    }
    return result;
}

const std::string prs::Tokenizer::read_string() {
    char c;
    std::string result;
    while(input.good() && c != '"'){
        result.push_back(c);  
        ++position;      
    }
    return result;
}


const std::string prs::Tokenizer::read_number() {
    char c;
    std::string result;
    while(input.good() && !iswspace(c)){
        c = input.get();
        ++position;
        if(c == '.' || c=='e' || c=='E' || isdigit(c)){
            result.push_back(c);
        }
        else{
            throw std::runtime_error("Invalid number format");
        }
        result.push_back(c);
        
    }
    return result;
}

bool prs::Tokenizer::is_bool() {
    std::string result;
    input >> result;
    position+= result.size();
    return (result == "true" || result == "false");

}


const prs::Token& prs::Tokenizer::getToken(){
    std::string word;
    if (position > 50) throw "ERROR: Command length should not be greater than 50";
    Token tok;

    if (input.eof()) 
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
        c = input.get();
        position++;

        if(isdigit(c)){
            tok.type= TokenType::Number;
            tok.value.push_back(c);
            tok.value.append(read_number());
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
        tok.type = is_bool() ? TokenType::Boolean : TokenType::Command;
        tok.value= read_word();
    }
    else{
        input.unget();
        --position;
        tok.type = TokenType::Command;
        tok.value = read_word();
    }
    
    return tok;
}
// std::istream& input;
// size_t position;
#include <vector>
#include "Tokenizer.h"

void dec::CLI_Tokenizer::init()  {
    std::string line;
    std::getline(input, line);
    buffer = std::stringstream(line);
    position = 0;  // Reset position for new line
    tok.value = "";
    tok.type = TokenType::End;
}

const std::string dec::CLI_Tokenizer::read_word() {
    char c;
    std::string result = "";
    while(buffer.get(c)){
        if (isspace(c) || c==',') {
            break;
        }
        result.push_back(c); // պետք ա Value-ի վարիանտի սթեյթերը ստուգես
        ++position;
        check_length();
    }
    return result;
}

std::pair<double, double> dec::CLI_Tokenizer::parse_coordinate(const std::string& coord) {
    size_t comma_pos = coord.find(',');
    if (comma_pos == std::string::npos) {
        throw std::runtime_error("Invalid coordinate format");
    }
    
    std::string x_str = coord.substr(0, comma_pos);
    std::string y_str = coord.substr(comma_pos + 1);
    
    return {std::stod(x_str), std::stod(y_str)};
}

const std::string dec::CLI_Tokenizer::read_string() {
    char c;
    std::string result;

    while (buffer.get(c)) {
        ++position;
        check_length();

        if (c == '"') {
            return result;
        }

        result.push_back(c);
    }

    throw std::runtime_error("(tokenizer) ERROR: Unterminated string literal");
}


const std::string dec::CLI_Tokenizer::read_number() {
    char c;
    std::string result = "";
    while(buffer.get(c)){
        if(c == '.' || c=='e' || c=='E' || isdigit(c) || c=='-'){
            result.push_back(c);
            ++position;
            check_length();
        }
        else if (isspace(c) || c==',' || c==')') {
            buffer.unget();
            break;
        }
        else {
            throw std::runtime_error("(tokenizer) ERROR: Invalid number format");
        }
    }
    return result;
}

void dec::CLI_Tokenizer::skip_spaces(){
    char c;
    while(buffer.get(c) && (isspace(c))) {
        position++;
    }
    if (buffer && !buffer.eof()) {
        buffer.unget();
    }
}

dec::Token& dec::CLI_Tokenizer::getToken(){
    tok.value.clear();
    tok.type = TokenType::Err;
    
    char c;
    skip_spaces();
    
    if (!buffer.get(c)) {
        tok.value = "";
        tok.type = TokenType::End;
        return tok;
    }
    position++;

    if (buffer.fail()) {
        throw std::runtime_error("(tokenizer) ERROR: Input stream error");
    }
    
    if (c == '-')
    {
        if(isdigit(buffer.peek())){
            tok.value.clear();
            tok.value.push_back(c);
            tok.value.append(read_number());
            tok.type = TokenType::Number;
        }
        else {
            tok.type = TokenType::Option;
            tok.value.append(read_word());
        }
    }
    else if(c == '"')
    {
        tok.type = TokenType::String;
        tok.value = read_string();
    }
    else if (c == '(')
    {
        tok.type = TokenType::Coord;
        
        std::string num1 = read_number();
        
        skip_spaces();
        
        if (!buffer.get(c) || c != ',') {
            throw std::runtime_error("(tokenizer) ERROR: Expected ',' in coordinate");
        }
        position++;
        
        skip_spaces();
        
        std::string num2 = read_number();
        
        skip_spaces();
        
        if (!buffer.get(c) || c != ')') {
            throw std::runtime_error("(tokenizer) ERROR: Missing closing parenthesis");
        }
        position++;
        
        tok.value = num1 + "," + num2;
    }
    else if (c == 't' || c == 'f') {
        buffer.unget();
        --position;

        std::string word = read_word();
        tok.type = (word == "true" || word == "false") ? TokenType::Boolean : TokenType::Command;
        tok.value = word;
    }
    else if(isdigit(c)){
        buffer.unget();
        --position;

        tok.value = read_number();
        tok.type = TokenType::Number;
    }
    else if(isalpha(c)){
        buffer.unget();
        --position;
        tok.type = TokenType::Command;
        tok.value = read_word();
    }
    else{
        throw std::runtime_error("(tokenizer) ERROR: unexpected symbol '" + std::string(1, c) + "' at " + std::to_string(position));
    }

    return tok;
}

void dec::CLI_Tokenizer::check_length() {
    if (position > 250) {
        throw std::runtime_error("(tokenizer) ERROR: Command length should not be greater than 250!");
    }
}
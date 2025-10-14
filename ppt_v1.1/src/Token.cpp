#include "Token.h"


dec::Token::Token(const Token& other): type(other.type), value(other.value) {}


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
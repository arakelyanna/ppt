#include "Token.h"


dec::Token::Token(const Token& other): type(other.type), value(other.value) {}


bool dec::Token::is_string() const{
    return type == TokenType::String;
}

bool dec::Token::is_option() const{
    
    return type == TokenType::Option;
}


bool dec::Token::is_int() const {
    char* end;
    long val = std::strtol(value.c_str(), &end, 10);
    return end != value.c_str() && *end == '\0';
}

bool dec::Token::is_double() const {
    char* end;
    std::strtod(value.c_str(), &end);
    return end != value.c_str() && *end == '\0';
}

bool dec::Token::is_bool() const{
    return type == TokenType::Boolean;
}
bool dec::Token::is_coord() const{
    return type == TokenType::Coord;
}
bool dec::Token::is_command() const{
    return type == TokenType::Command;
}

bool dec::Token::end() const{
    return type == TokenType::End;
}

bool dec::Token::err() const{
    return type == TokenType::Err;
}
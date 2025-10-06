#include "Tokenizer.h"


bool prs::Token::is_string() const{

}

bool prs::Token::is_option() const{

}

bool prs::Token::is_number() const{

}

bool prs::Token::is_bool() const{

}



// std::string prs::Tokenizer::read_command() const{
    
// }

// std::string prs::Tokenizer::read_string() const{
    
// }

// std::string prs::Tokenizer::read_option() const{
    
// }

// double prs::Tokenizer::read_number() const{
    
// }

// bool prs::Tokenizer::read_bool() const{
    
// }


const prs::Token& prs::Tokenizer::getToken(){
    std::string word;
    if (position > 50) throw "ERROR: Command length should not be greater than 50";
    Token tok;

    if (input.bad()) 
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
       c = input.get();
       position++;
       if(isdigit(c)){
        tok.type= TokenType::Number;
        // tok.value.push_back('-');
        // read_number();
       }else tok.type = TokenType::Option;
    }
    else if(c =='"')
    {
        tok.type=TokenType::String;
    }
    else if (c == 't' || c=='f')
    {
        tok.type = TokenType::Boolean;
    }
    else{
        tok.type = TokenType::Command;
    }
    
    
    


    return tok;
}
// std::istream& input;
// size_t position;
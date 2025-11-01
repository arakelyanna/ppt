#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "Token.h"

namespace dec {
    

    class CLI_Tokenizer
    {
    public:
        CLI_Tokenizer() : position(0){
            std::string line;
            std::getline(std::cin, line);
            buffer = std::stringstream(line);
            tok.value = "";
            tok.type = TokenType::Eof;
        }

        CLI_Tokenizer(std::istream& input) : position(0) {
            std::string line;
            std::getline(input, line);
            buffer = std::stringstream(line);
            tok.value = "";
            tok.type = TokenType::Eof;
        }

        Token& getToken();
    private:
        const std::string read_word();
        const std::string read_number();
        const std::string read_string();
        const std::string read_coord();
        void skip_spaces();
        void check_length() const;
    private:
        std::stringstream buffer;
        size_t position;
        Token tok;
    };

    
}
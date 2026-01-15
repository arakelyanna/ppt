#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "Token.h"

namespace dec {
    

    class CLI_Tokenizer
    {
    public:
        CLI_Tokenizer(std::istream& input = std::cin) : position(0), input(input) {}

        void init();
        std::pair<double, double> parse_coordinate(const std::string& coord);
        Token& getToken();
        
    private:
        const std::string read_word();
        const std::string read_number();
        const std::string read_string();
        // const std::string read_coord();
        void skip_spaces();
        void check_length();
    private:
        std::istream& input;
        std::stringstream buffer;
        size_t position;
        Token tok;
    };

    
}
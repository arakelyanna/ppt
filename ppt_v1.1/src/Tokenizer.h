#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace dec {
    enum class TokenType {
        Command,
		String,
		Option,
		Number,
		Boolean,
		Err,
		Eof
	};

	class Token {
    public:
        Token() : value(""), type(TokenType::Err){}

		TokenType type;
		std::string value;
        
        bool is_command() const;
        bool is_string() const;
        bool is_option() const;
        bool is_number() const;
        bool is_bool() const;
        bool eof() const;
        bool err() const;
	};

    class CLI_Tokenizer
    {
    public:
        CLI_Tokenizer() : position(0) {
            std::string line;
            std::getline(std::cin, line);
            buffer = std::stringstream(line);
        }

        CLI_Tokenizer(std::istream& input) : position(0) {
            std::string line;
            std::getline(input, line);
            buffer = std::stringstream(line);
        }

        Token getToken();
    private:
        const std::string read_word();
        const std::string read_number();
        const std::string read_string();

        void check_length() const;

        std::stringstream buffer;
        size_t position;
    };

    
}
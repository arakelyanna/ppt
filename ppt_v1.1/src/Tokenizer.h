#pragma once
#include <iostream>
#include <istream>
#include <string>

namespace prs {
    enum class TokenType {
		Command,
		String,
		Option,
		Number,
		Boolean,
		Err,
		Eof
	};

	struct Token {
        Token() : value(""), type(TokenType::Err){}

		TokenType type;
		std::string value;

        bool is_command() const;
        bool is_string() const;
        bool is_option() const;
        bool is_number() const;
        bool is_bool() const;
	};

    
    class Tokenizer
    {
    public:
        Tokenizer() : position(0), input(std::cin){}
        Tokenizer(std::istream& input) : position(0), input(input){}
        const std::string read_word();
        const std::string read_number();
        const std::string read_string();
        Token getToken();

    private:
        void check_length() const;
        std::istream& input;
        size_t position;
    };

    
}
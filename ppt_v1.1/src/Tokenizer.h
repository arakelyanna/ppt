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
		Comma,
		Eof
	};

	struct Token {
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

        const Token& getToken();

    private:

        std::istream& input;
        size_t position;
    };

    
}
#pragma once
#include <string>
#include <vector>

namespace dec{
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
        Token(const Token& other);
		TokenType type;
		std::string value;
        
        bool is_command() const;
        bool is_string() const;
        bool is_option() const;
        bool is_number() const;
        bool is_bool() const;
        bool is_array() const;
        bool eof() const;
        bool err() const;
	};
}
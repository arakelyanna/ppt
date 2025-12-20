#pragma once
#include <string>
#include <vector>

namespace dec{
    enum class TokenType {
        Command, //0
		String, //1
		Option, //2
		Number, //3
		Boolean, //4
        Coord, //5
		Err, //6
		End //7
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
        bool is_int() const;
        bool is_double() const;
        bool is_bool() const;
        bool is_coord() const;
        bool end() const;
        bool err() const;
	};
}
#include "Parser.h"
#include "Command.h"
#include <array>
#include <algorithm>
#include <memory>

// std::array<std::string, 4> keywords = {"shape", "picture", "text", "slide"};

void dec::Parser::init_transition() {
    for (size_t i = 0; i < 25; i++)
    {
        for (size_t j = 0; j < 25; j++)
        {
            transition[i][j] = State::Err;
        }
        
    }
    
    transition[(int)State::Start][(int)TokenType::Command] = State::Command;
    transition[(int)State::Command][(int)TokenType::Option] = State::Option;
    transition[(int)State::Command][(int)TokenType::Command] = State::Args;
    transition[(int)State::Command][(int)TokenType::Eof] = State::Eof;
    transition[(int)State::Args][(int)TokenType::Option] = State::Option;
    transition[(int)State::Option][(int)TokenType::Number] = State::Number;
    transition[(int)State::Option][(int)TokenType::String] = State::String;
    transition[(int)State::Option][(int)TokenType::Boolean] = State::Boolean;
    transition[(int)State::Number][(int)TokenType::Eof] = State::Eof;
    transition[(int)State::Number][(int)TokenType::Number] = State::Number;
    transition[(int)State::String][(int)TokenType::Eof] = State::Eof;
    transition[(int)State::Boolean][(int)TokenType::Eof] = State::Eof;
    
    transition[(int)State::Number][(int)TokenType::Option] = State::Option;
    transition[(int)State::String][(int)TokenType::Option] = State::Option;
    transition[(int)State::Boolean][(int)TokenType::Option] = State::Option;
}


std::unique_ptr<cmd::ICommand> dec::Parser::parse() {
    Token tok;
    State currentState = State::Start;
    std::unique_ptr<cmd::ICommand> command;
    std::string key; double num; std::string value; bool flag;
    while (true)
    {
        tok = tokenizer.getToken();

        if(tok.eof()) break;
        else if(tok.err()) throw std::runtime_error("Unkown token...");


        switch (currentState)
        {
        case State::Start:
            currentState = transition[(int)State::Start][(int)tok.type];
            break;
        case State::Command:
            
            tok = tokenizer.getToken();
            currentState = transition[(int)State::Command][(int)tok.type];
            break;
        case State::Args:
            currentState = transition[(int)State::Args][(int)tok.type];

            if (tok.value == "shape")
            {
                tok = tokenizer.getToken();
                if (tok.type == TokenType::Option)
                {
                    command = std::make_unique<cmd::AddShape>(tok.value);
                    tok = tokenizer.getToken();
                    currentState = transition[(int)State::Args][(int)tok.type];
                }
                else throw std::runtime_error("ERROR: Expected the shape name (-<shape name>>)\n");
            }
            else if(tok.value == "slide") {
                command = std::make_unique<cmd::AddSlide>();
            }
            else if(tok.value == "picture") {
                tok = tokenizer.getToken();
                if (tok.type == TokenType::String)
                {
                    command = std::make_unique<cmd::AddPicture>(tok.value);
                }
                
            }
            else if(tok.value == "text") {
                command = std::make_unique<cmd::AddText>();
            }
            else currentState = State::Err;
            

        break;
        case State::Option:
            key = tok.value;
            tok = tokenizer.getToken();
            currentState = transition[(int)State::Option][(int)tok.type];
            break;

        default:
            throw std::runtime_error("ERROR: Invalid Token '" + tok.value + "'!");
            break;
        }
        
    }
    
    
}

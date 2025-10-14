#include "Parser.h"
#include "Command.h"
#include <array>
#include <algorithm>
#include <memory>

std::array<std::string, 4> keywords = {"shape", "picture", "text", "slide"};


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
                command = std::make_unique<cmd::AddShape>();
            }
            else if(tok.value == "slide") {
                command = std::make_unique<cmd::AddSlide>();
            }
            else if(tok.value == "picture") {
                command = std::make_unique<cmd::AddPicture>();
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
        case State::Number:
            num = std::stod(tok.value);
            command->opt.set(key, cmd::Data{tok.value});

            tok = tokenizer.getToken();
            currentState = transition[(int)State::Number][(int)tok.type];
            break;
        case State::String:
            value = tok.value;
            command->opt.set(key, cmd::Data{tok.value});

            tok = tokenizer.getToken();
            currentState = transition[(int)State::Number][(int)tok.type];
            break;
        case State::Boolean:
            flag = (tok.value == "true");
            command->opt.set(key, cmd::Data{tok.value});

            tok = tokenizer.getToken();
            currentState = transition[(int)State::Number][(int)tok.type];
            break;
        default:
            throw std::runtime_error("ERROR: Invalid Token '" + tok.value + "'!");
            break;
        }
        
    }
    
    
}

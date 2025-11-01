#include <array>
#include <algorithm>
#include <memory>
#include "app/cmd/Command.h"
#include "app/cmd/CmdBuilder.h"
#include "app/cmd/CmdFactory.h"
#include "Parser.h"
// std::array<std::string, 4> keywords = {"shape", "picture", "text", "slide"};

void dec::Parser::init_transition() {
    for (size_t i = 0; i < (int)State::Eof; i++)
    {
        for (size_t j = 0; j < (int)TokenType::Eof; j++)
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
    transition[(int)State::Option][(int)TokenType::Coord] = State::Coord;
    transition[(int)State::Option][(int)TokenType::String] = State::String;
    transition[(int)State::Option][(int)TokenType::Boolean] = State::Boolean;

    transition[(int)State::Number][(int)TokenType::Eof] = State::Eof;
    transition[(int)State::Number][(int)TokenType::Number] = State::Number;
    transition[(int)State::Number][(int)TokenType::Coord] = State::Coord;

    transition[(int)State::Coord][(int)TokenType::Number] = State::Number;

    transition[(int)State::String][(int)TokenType::Eof] = State::Eof;
    transition[(int)State::Boolean][(int)TokenType::Eof] = State::Eof;
    
    transition[(int)State::Number][(int)TokenType::Option] = State::Option;
    transition[(int)State::String][(int)TokenType::Option] = State::Option;
    transition[(int)State::Boolean][(int)TokenType::Option] = State::Option;
}


std::unique_ptr<cmd::I_Command> dec::Parser::parse() {
    Token tok;
    State currentState = State::Start;
    std::string key;
    cmd::CmdFactory cmdFactory;
    std::unique_ptr<cmd::I_Command> command;
    cmd::Coord coord;
    while (true)
    {
        tok = tokenizer.getToken();

        if(tok.eof()) break;
        else if(tok.err()) throw std::runtime_error("ERROR: Unkown token...");


        switch (currentState)
        {
        case State::Start:
            currentState = transition[(int)State::Start][(int)tok.type];
            break;
        case State::Command:
            if (tok.value == "open"){
                key = "file";
                command = cmdFactory.create(tok.value);
                tok=tokenizer.getToken();
                val = tok.value;
                currentState = transition[(int)State::Option][(int)TokenType::String];
                break;
            } 
            else if(tok.value == "save"){
                key="file";
                command = cmdFactory.create(tok.value);
                tok=tokenizer.getToken();
                val = tok.value;
                currentState = transition[(int)State::Command][(int)tok.type];
                break;
            }
            val = tok.value;
            tok = tokenizer.getToken();

            if (!tok.is_command())
            {
                command = cmdFactory.create(*(std::get_if<std::string>(&val)));
            }
            
            currentState = transition[(int)State::Command][(int)tok.type];
            break;
        case State::Args:
            if (tok.value=="as")
            {
                key = "file";
                tok=tokenizer.getToken();
                val = tok.value;
                currentState = transition[(int)State::Option][(int)TokenType::String];
                break;
            }
            else if (tok.value == "at") {
                key = "pos";
                tok=tokenizer.getToken();
                val = tok.value;
                currentState = transition[(int)State::Option][(int)TokenType::String];
                break;
            }

            if (auto s = std::get_if<std::string>(&val)) {
                s->append(" " + tok.value);
            } else {
                throw std::runtime_error("ERROR: smth wrong with args");
            }

            currentState = transition[(int)State::Args][(int)tok.type];
            if(!command) command = cmdFactory.create(*std::get_if<std::string>(&val));
            break;
        case State::Option:
            key = tok.value;
            tok = tokenizer.getToken();
            if (tok.is_option()) command->set("args", tok.value);
            currentState = transition[(int)State::Option][(int)tok.type];
            break;
        case State::Number:
            val = std::stod(tok.value);
            command->set(key, val);
            tok = tokenizer.getToken();
            currentState = transition[(int)State::Number][(int)tok.type];
            break;
        case State::Coord:
            coord = tokenizer.parse_coordinate(tok.value);
            std::get<5>(val).push_back(coord);
            command->set(key, val);
            currentState = transition[(int)State::Coord][(int)tok.type];
            
            break;
        case State::Boolean:
            val = (tok.value == "true");
            command->set(key, val);
            tok = tokenizer.getToken();
            currentState = transition[(int)State::Number][(int)tok.type];
            break;
        case State::String:
            command->set(key, val);
            tok = tokenizer.getToken();
            currentState = transition[(int)State::Number][(int)tok.type];
            break;
        case State::Err:
            throw std::runtime_error("ERROR: Invalid Token '" + tok.value + "'!");
            break;
        case State::Eof:
            break;
        default:
            currentState = State::Err;
            break;
        }
    }
    command->build();
    return command; 
}

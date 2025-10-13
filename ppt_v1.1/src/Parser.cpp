#include "Parser.h"
#include "Command.h"
#include <array>
#include <algorithm>
#include <memory>

std::array<std::string, 4> keywords = {"shape", "picture", "text", "slide"};


std::unique_ptr<dec::ICommand> dec::Parser::parse() {
    Token tok;
    State currentState = State::Start;
    std::unique_ptr<ICommand> command;
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
                command = std::make_unique<AddShape>();
            }
            else if(tok.value == "slide") {
                command = std::make_unique<AddSlide>();
            }
            else if(tok.value == "picture") {
                command = std::make_unique<AddPicture>();
            }
            else if(tok.value == "text") {
                command = std::make_unique<AddText>();
            }
            else currentState = State::Err;
            

        break;
        case State::Option:
            
        break;
        default:
            break;
        }
        
    }
    
    
}

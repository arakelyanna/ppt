#pragma once
#include <memory>
#include <array>
#include "Tokenizer.h"
#include "Command.h"

namespace dec{
    
    enum class State {Start, Command, Option, Args, String, Number, Boolean, Err, Eof}; // Args = {Slide, Shape, .....}
    
    
    
    
    class Parser
    {
    public:
        Parser(std::istream input):tokenizer(input) {
            init_transition();
        }
        Parser():tokenizer(std::cin){
            init_transition();
        }
        
        std::unique_ptr<cmd::ICommand> parse();

    private:
    
        void init_transition(){
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
            transition[(int)State::String][(int)TokenType::Eof] = State::Eof;
            transition[(int)State::Boolean][(int)TokenType::Eof] = State::Eof;
            
            transition[(int)State::Number][(int)TokenType::Option] = State::Option;
            transition[(int)State::String][(int)TokenType::Option] = State::Option;
            transition[(int)State::Boolean][(int)TokenType::Option] = State::Option;
        }

        CLI_Tokenizer tokenizer;

        using TransitionTable = std::array<std::array<State, 25>, 25>;
        TransitionTable transition;
    };


}
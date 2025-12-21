#include "Parser.h"

void dec::Parser::init_transition() {
    for (size_t i = 0; i < (int)State::End; i++)
    {
        for (size_t j = 0; j < (int)TokenType::End; j++)
        {
            transition[i][j] = State::Err;
        }
    }
    
    transition[(int)State::Start][(int)TokenType::Command] = State::Command;
    transition[(int)State::Start][(int)TokenType::End] = State::End;
    transition[(int)State::Command][(int)TokenType::Command] = State::Command;
    transition[(int)State::Command][(int)TokenType::Option] = State::Argument;
    transition[(int)State::Command][(int)TokenType::End] = State::End;

    transition[(int)State::Argument][(int)TokenType::Number] = State::Value;
    transition[(int)State::Argument][(int)TokenType::Boolean] = State::Value;
    transition[(int)State::Argument][(int)TokenType::Coord] = State::Value;
    transition[(int)State::Argument][(int)TokenType::String] = State::Value;
    
    transition[(int)State::Value][(int)TokenType::Option] = State::Argument;
    transition[(int)State::Value][(int)TokenType::Coord] = State::Value;
    transition[(int)State::Value][(int)TokenType::End] = State::End;
}


std::unique_ptr<cmd::I_Command> dec::Parser::parse() {
    Token tok;
    tokenizer.init();
    currentState = State::Start;
    command_name = "";
    cmd_creator.reset(); // Reset cmd_creator for new parse
    coord_buffer.clear(); // Clear coordinate buffer
    
    while (currentState != State::End && currentState != State::Err)
    {
        tok = tokenizer.getToken();
        process(tok);
    }
    
    // Handle empty input (just Enter pressed)
    if (command_name.empty() && currentState == State::End) {
        return nullptr; // Return nullptr for empty commands
    }
    
    // Handle error state or missing cmd_creator
    if (currentState == State::Err || !cmd_creator)
    {
        throw std::runtime_error("(parser) ERROR: Invalid command '" + command_name + "'");
    }
    
    return std::move(cmd_creator->create());
}

void dec::Parser::process(Token& tok) {
    
    State previousState = currentState;
    
    if (currentState != State::Err)
        currentState = transition[(int)currentState][(int)tok.type];
    
    obj::Coord coord; 
    std::string find_result;
    
    switch (currentState)
    {
        case State::Command:
            command_name += tok.value;
            
            find_result = cmd_register.find(command_name);
            if (find_result == "starts_with") {
                command_name += ' ';
            }
            else if (find_result == "is") {
                cmd_creator = cmd_register.get(command_name);
            }
            else {
                // Command not found
                currentState = State::Err;
            }
            break;
            
        case State::Argument:
            if(!cmd_creator) {
                currentState = State::Err;
                break;
            }
            
            if (previousState == State::Value && !coord_buffer.empty() && cmd_creator) {
                cmd::Value coord_value = coord_buffer;
                cmd_creator->set(key, coord_value);
                coord_buffer.clear();
            }
            
            
            if (cmd::filled_shapes.find(tok.value) != cmd::filled_shapes.end() || 
                cmd::lined_shapes.find(tok.value) != cmd::lined_shapes.end())
            {
                cmd_creator->set("shape", tok.value);
                currentState = State::Value;
                key = "";
            }
            else {
                key = tok.value;
                
                if (!cmd_creator->get(key).getsArg)
                {
                    cmd_creator->set(key, true);
                    currentState = State::Value;
                }
                else {
                    currentState = State::Argument;
                }
            }
            break;
        case State::Value:
            if(!cmd_creator) {
                currentState = State::Err;
                break;
            }
            switch (tok.type)
            {
                case TokenType::Number:
                    if (tok.is_int()) {
                        cmd_creator->set(key, std::stoi(tok.value));
                    }
                    else if (tok.is_double()) {
                        cmd_creator->set(key, std::stod(tok.value));
                    }
                    break;
                    
                case TokenType::Coord:
                {
                    coord = tokenizer.parse_coordinate(tok.value);
                    coord_buffer.push_back(coord);
                    break;
                }
                    
                case TokenType::Boolean:
                    cmd_creator->set(key, (tok.value == "true"));
                    break;
                    
                default:
                    cmd_creator->set(key, tok.value);
                    break;
            }
            break;
            
        case State::Err:
            throw std::runtime_error("(parser) ERROR: Syntax Violation by '" + tok.value + "'!\n");
            break;
            
        case State::End:
            if (!coord_buffer.empty() && cmd_creator) {
                cmd::Value coord_value = coord_buffer;
                cmd_creator->set(key, coord_value);
                coord_buffer.clear();
            }
            break;
            
        default:
            currentState = State::Err;
            break;
    }
}
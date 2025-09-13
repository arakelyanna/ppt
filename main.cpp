#include <iostream>
#include "Tokenizer.h"
#include "Fetcher.h"


int main(int argc, char* argv[]){
    std::string text= "a b c";
    Tokenizer t(text);
    try
    {
        Fetcher file(argv[1]);
        while(1){
            auto line = file.next_line();
            if(!line) break;
            std::cout << *line << '\n';
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
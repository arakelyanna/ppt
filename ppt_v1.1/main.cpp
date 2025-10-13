#include "PPT.h"

int main(int argc, char* argv[]){
    try
    {
        dec::CLI_Tokenizer tok(std::cin);

        dec::Token token;
        while(true){
            token = tok.getToken();
            if (token.type == dec::TokenType::Eof)
            {
                break;
            }
            
            std::cout << "val = " << token.value << ' ';
            std::cout << (int)token.type << '\n';
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
  
    return 0;
}

// asdfghjkl;kjhgfdsasdfghjkl;lkjhgfdsasdfghjkl;'mnb c83trynwfybgvt6v q57 70454100530687430.5053301
// asdfghjkl;kjhgfdsasdfghjkl;lkjhgfdsasdfghjkl;'mnb
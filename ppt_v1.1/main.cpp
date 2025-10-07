#include "PPT.h"

int main(int argc, char* argv[]){
    try
    {
        prs::Tokenizer tok(std::cin);

        prs::Token token;
        while(token.type != prs::TokenType::Eof){
            token = tok.getToken();
            std::cout << token.value << '\n';
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
#include <iostream>
#include <string>
#include "CLI_Viewer.h"

namespace view {

    void CLI_Viewer::show(const doc::Ppt& ppt) const {
        for (size_t i = 0; i < ppt.size(); i++)
        {
            ppt[i].show();
        }
        std::cout << "\n||||||||||||||||||||||||\n";
        
    }
    void CLI_Viewer::show_slide(const doc::Ppt& ppt, size_t pos = 0) const {
        ppt[pos].show();
    }
    
}
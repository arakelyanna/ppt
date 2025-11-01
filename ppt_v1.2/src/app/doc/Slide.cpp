#include "Slide.h"

namespace doc{
    void Slide::show() const {
        std::cout << "\n========== " << id << " ============\n";
        for (auto& obj : objects)
        {
            obj->show();
        }
        std::cout << "\n=========================\n";
    }
}
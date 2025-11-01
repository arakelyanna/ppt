#pragma once
#include "../doc/Presentation.h"

namespace view{
    class I_Viewer {
    public:
        virtual void show(const doc::Ppt& ppt) const = 0;
        virtual void show_slide(const doc::Ppt& ppt, size_t pos) const = 0;

        static std::unique_ptr<I_Viewer> create(const std::string& type);
    };
}
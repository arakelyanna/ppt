#pragma once
#include <memory>
#include "Viewer.h"
#include "../doc/Presentation.h"

namespace view{
    class CLI_Viewer : public I_Viewer {
    public:
        void show(const doc::Ppt& ppt) const override;
        void show_slide(const doc::Ppt& ppt, size_t type) const override;

    };
}
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../objects/Object.h"

namespace doc{
    class Slide{
    public:
        Slide() : id(0){}

        void set_id(size_t i) {
            id = i;
        }
        void add_object(std::unique_ptr<obj::Object> obj){
            objects.push_back(std::move(obj));
        }
        void show() const;
    private:
        size_t id;
        std::vector<std::unique_ptr<obj::Object>> objects;
    };
}
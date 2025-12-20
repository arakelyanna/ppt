#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../../objects/Object.h"

namespace doc{
    class Slide{
    public:
        Slide();
        
        void set_id(size_t i);
        size_t get_id() const;

        void add_object(std::shared_ptr<obj::Object> obj);
        std::shared_ptr<obj::Object> get_object(const obj::Coord& pos);
        std::shared_ptr<obj::Object> remove_object(std::shared_ptr<obj::Object> obj);

        using const_iterator = std::vector<std::shared_ptr<obj::Object>>::const_iterator;
        
        const_iterator begin() const { return objects.begin(); }
        const_iterator end() const { return objects.end(); }

    private:
        bool point_position(const obj::Geometry& shape, const obj::Coord& p);

        size_t id;
        std::vector<std::shared_ptr<obj::Object>> objects;
    };
}
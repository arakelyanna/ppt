#pragma once
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <cassert>
#include "../Object.h"

namespace obj {
    class Text : public Object {
    public:
        Text();
        Text(const Text&) = default;
        Text(Text&&) = default;

        Text& operator=(const Text&) = delete;
        Text& operator=(Text&&) = default; 
        
        void accept(const out::IVisitor& visitor) override;

        Text(const std::string& value, size_t size = 11, const std::string& color = "black", const std::string& style = "arial");

        void create(const Geometry& coords);
        void set_value(const std::string& val);
        void set_size(size_t size);
        void set_style(const std::string& value);
        void set_color(const std::string& value);
        
        const std::string& get_color() const;
        const std::string& get_text() const;
        const std::string& get_style() const;
        size_t get_size() const;
        const Geometry& get_geometry() const;

    private:
        const std::array<std::string, 4> styles = {"arial", "roberto", "sylfaen", "times new roman"};
        
        Geometry pos;
        std::string value;
        size_t size;
        std::string style;
        std::string color;
    };
}
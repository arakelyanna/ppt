#pragma once
#include <algorithm>
#include <set>
#include <string>
#include <memory>
#include <variant>
#include <unordered_map>
#include <vector>
#include "../../objects/Object.h"
#include "../../objects/Shapes/Shape.h"
#include "../../objects/Text/Text.h"
#include "../../objects/Picture/Picture.h"

namespace cmd {
    using Coord = std::pair<double, double>;
    using Position = std::vector<Coord>;
    using Value = std::variant<std::monostate, int, double, bool, std::string, Position>;
    using Option = std::unordered_map<std::string, Value>;

    extern const std::set<std::string> filled_shapes;
    extern const std::set<std::string> lined_shapes;

    class Builder {
    public:
        void set(const std::string key, const Value& val);
        std::unique_ptr<obj::IShape> build_shape();
        obj::Picture build_picture();
        std::unique_ptr<obj::Text> build_text();
        const std::string& build_file();
        size_t build_slide_command();
        
    private:
        Option options = {
            {"args", ""},
            {"file", ""},
            {"pos", ""},
            {"height", ""},
            {"width", ""},
            {"color", ""},
            {"text", ""},
            {"size", ""},
            {"borderline_color", ""},
            {"borderline_width", ""},
            {"filled", ""},
            {"radius", ""}
        };
    };
}
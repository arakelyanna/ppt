#include "Slide.h"
#include <algorithm>
#include <cmath>

namespace doc{

    Slide::Slide() : id(0) {
    }

    void Slide::set_id(size_t i) {
        id = i;
    }

    size_t Slide::get_id() const {
        return id;
    }

    void Slide::add_object(std::shared_ptr<obj::Object> obj) {
        objects.push_back(obj);
    }

    std::shared_ptr<obj::Object> Slide::get_object(const obj::Coord& pos) {
        for (auto obj : objects) {
            if(point_position(obj->get_geometry(), pos)) return obj;
        }
        return nullptr;
    }

    std::shared_ptr<obj::Object> Slide::remove_object(std::shared_ptr<obj::Object> obj) {
        auto it = std::find(objects.begin(), objects.end(), obj);
        if (it == objects.end())
            return nullptr;

        auto removed = *it;   // copy BEFORE erase
        objects.erase(it);
        return removed;
    }


    bool Slide::point_position(const obj::Geometry& shape, const obj::Coord& p) {
        const double eps = 1e-9;

        if (shape.size() == 1)
            return (std::abs(p.first - shape[0].first) < eps && std::abs(p.second - shape[0].second) < eps) 
                ? true 
                : false;

        int n = shape.size();

        for (int i = 0; i < n; ++i) {
            const obj::Coord& a = shape[i];
            const obj::Coord& b = shape[(i + 1) % n];

            if (std::abs(p.first - a.first) < eps && std::abs(p.second - a.second) < eps)
                return true;

            double cross = (b.first - a.first) * (p.second - a.second) - (b.second - a.second) * (p.first - a.first);
            if (std::abs(cross) < eps) {
                double dot = (p.first - a.first) * (b.first - a.first) + (p.second - a.second) * (b.second - a.second);
                double len_sq = (b.first - a.first)*(b.first - a.first) + (b.second - a.second)*(b.second - a.second);
                if (dot >= 0 && dot <= len_sq)
                    return true;
            }
        }

        double prev = 0;
        for (int i = 0; i < n; ++i) {
            const obj::Coord& a = shape[i];
            const obj::Coord& b = shape[(i + 1) % n];
            double cross = (b.first - a.first)*(p.second - a.second) - (b.second - a.second)*(p.first - a.first);
            if (i == 0) prev = cross;
            else if (cross * prev < -eps) return false;
        }

        return true;
    }
}
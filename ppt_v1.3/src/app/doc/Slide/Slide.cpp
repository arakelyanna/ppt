#include "Slide.h"
#include <algorithm>
#include <cmath>

namespace doc{

    Slide::Slide() : id(0) {}

    void Slide::set_id(size_t i) {
        id = i;
    }

    size_t Slide::get_id() const {
        return id;
    }

    void Slide::set_color(const std::string& color) {
        this->color = color;
    }

    const std::string& Slide::get_color() const {
        return color;
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
        const double CLICK_TOLERANCE = 5;  // 10 pixels
        
        // Single point (Text)
        if (shape.size() == 1) {
            double dx = p.first - shape[0].first;
            double dy = p.second - shape[0].second;
            return (dx*dx + dy*dy) <= CLICK_TOLERANCE * CLICK_TOLERANCE;
        }
        
        // Line or Arrow (2 points)
        if (shape.size() == 2) {
            return distanceToSegment(shape[0], shape[1], p) <= CLICK_TOLERANCE;
        }
        
        // Polygon (Triangle, Rectangle, etc.) - check if inside OR near boundary
        // First check if near any edge
        for (int i = 0; i < shape.size(); ++i) {
            const obj::Coord& a = shape[i];
            const obj::Coord& b = shape[(i + 1) % shape.size()];
            if (distanceToSegment(a, b, p) <= CLICK_TOLERANCE) {
                return true;
            }
        }
        
        // Then check if inside (ray casting algorithm)
        return isPointInPolygon(shape, p);
    }

    double Slide::distanceToSegment(const obj::Coord& a, const obj::Coord& b, const obj::Coord& p) {
        double dx = b.first - a.first;
        double dy = b.second - a.second;
        double len_sq = dx*dx + dy*dy;
        
        if (len_sq < 1e-9) {
            // Segment is actually a point
            double pdx = p.first - a.first;
            double pdy = p.second - a.second;
            return std::sqrt(pdx*pdx + pdy*pdy);
        }
        
        // Project point onto line
        double t = ((p.first - a.first) * dx + (p.second - a.second) * dy) / len_sq;
        t = std::max(0.0, std::min(1.0, t));  // Clamp to segment
        
        double proj_x = a.first + t * dx;
        double proj_y = a.second + t * dy;
        
        double dist_x = p.first - proj_x;
        double dist_y = p.second - proj_y;
        return std::sqrt(dist_x*dist_x + dist_y*dist_y);
    }

    // Ray casting algorithm for point in polygon
    bool Slide::isPointInPolygon(const obj::Geometry& poly, const obj::Coord& p) {
        int n = poly.size();
        bool inside = false;
        
        for (int i = 0, j = n - 1; i < n; j = i++) {
            double xi = poly[i].first, yi = poly[i].second;
            double xj = poly[j].first, yj = poly[j].second;
            
            bool intersect = ((yi > p.second) != (yj > p.second))
                && (p.first < (xj - xi) * (p.second - yi) / (yj - yi) + xi);
            if (intersect) inside = !inside;
        }
        
        return inside;
    }
}
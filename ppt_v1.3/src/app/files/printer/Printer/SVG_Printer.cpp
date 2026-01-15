#include "Printer.h"
#include <sstream>
#include <fstream>
#include <cmath>

namespace out {
    // Helper function to convert colors to SVG format
    std::string colorToSVG(const std::string& color) {
        // If color is already in hex format or a named color, return as is
        if (color.empty()) return "black";
        return color;
    }

    // Helper function to convert text style to SVG
    std::string textStyleToSVG(const std::string& style) {
        if (style.find("bold") != std::string::npos) return "font-weight=\"bold\"";
        if (style.find("italic") != std::string::npos) return "font-style=\"italic\"";
        return "";
    }

    void SVGPrinter::printSlide(std::shared_ptr<doc::Slide> slide) { /*visitor handles this one*/ }

    void SVGPrinter::print_rectangle(const obj::Rectangle& obj) {
        auto geom = obj.get_geometry();
        double x = std::min(geom[0].first, geom[1].first);
        double y = std::min(geom[0].second, geom[1].second);
        double width = obj.get_width();
        double height = obj.get_height();

        std::stringstream ss;
        ss << "  <rect x=\"" << x << "\" y=\"" << y 
           << "\" width=\"" << width << "\" height=\"" << height << "\"";
        
        if (obj.is_filled()) {
            ss << " fill=\"" << colorToSVG(obj.get_color()) << "\"";
        } else {
            ss << " fill=\"none\"";
        }
        
        ss << " stroke=\"" << colorToSVG(obj.get_line_color()) << "\""
           << " stroke-width=\"" << obj.get_line_width() << "\" />\n";

        // Add text if present
        if (!obj.get_text().empty()) {
            double text_x = x + width / 2;
            double text_y = y + height / 2;
            ss << "  <text x=\"" << text_x << "\" y=\"" << text_y 
               << "\" text-anchor=\"middle\" dominant-baseline=\"middle\""
               << " fill=\"" << colorToSVG(obj.get_text_color()) << "\""
               << " font-size=\"" << obj.get_text_size() << "\""
               << " " << textStyleToSVG(obj.get_text_style()) << ">"
               << obj.get_text() << "</text>\n";
        }

        svgContent += ss.str();
    }

    void SVGPrinter::print_triangle(const obj::Triangle& obj) {
        auto geom = obj.get_geometry();
        
        std::stringstream ss;
        ss << "  <polygon points=\""
           << geom[0].first << "," << geom[0].second << " "
           << geom[1].first << "," << geom[1].second << " "
           << geom[2].first << "," << geom[2].second << "\"";
        
        if (obj.is_filled()) {
            ss << " fill=\"" << colorToSVG(obj.get_color()) << "\"";
        } else {
            ss << " fill=\"none\"";
        }
        
        ss << " stroke=\"" << colorToSVG(obj.get_line_color()) << "\""
           << " stroke-width=\"" << obj.get_line_width() << "\" />\n";

        // Add text if present (at centroid)
        if (!obj.get_text().empty()) {
            double text_x = (geom[0].first + geom[1].first + geom[2].first) / 3.0;
            double text_y = (geom[0].second + geom[1].second + geom[2].second) / 3.0;
            ss << "  <text x=\"" << text_x << "\" y=\"" << text_y 
               << "\" text-anchor=\"middle\" dominant-baseline=\"middle\""
               << " fill=\"" << colorToSVG(obj.get_text_color()) << "\""
               << " font-size=\"" << obj.get_text_size() << "\""
               << " " << textStyleToSVG(obj.get_text_style()) << ">"
               << obj.get_text() << "</text>\n";
        }

        svgContent += ss.str();
    }

    void SVGPrinter::print_circle(const obj::Circle& obj) {
        auto geom = obj.get_geometry();
        double cx = (geom[0].first + geom[1].first) / 2.0;
        double cy = (geom[0].second + geom[1].second) / 2.0;
        double radius = obj.get_radius();

        std::stringstream ss;
        ss << "  <circle cx=\"" << cx << "\" cy=\"" << cy 
           << "\" r=\"" << radius << "\"";
        
        if (obj.is_filled()) {
            ss << " fill=\"" << colorToSVG(obj.get_color()) << "\"";
        } else {
            ss << " fill=\"none\"";
        }
        
        ss << " stroke=\"" << colorToSVG(obj.get_line_color()) << "\""
           << " stroke-width=\"" << obj.get_line_width() << "\" />\n";

        // Add text if present
        if (!obj.get_text().empty()) {
            ss << "  <text x=\"" << cx << "\" y=\"" << cy 
               << "\" text-anchor=\"middle\" dominant-baseline=\"middle\""
               << " fill=\"" << colorToSVG(obj.get_text_color()) << "\""
               << " font-size=\"" << obj.get_text_size() << "\""
               << " " << textStyleToSVG(obj.get_text_style()) << ">"
               << obj.get_text() << "</text>\n";
        }

        svgContent += ss.str();
    }

    void SVGPrinter::print_square(const obj::Square& obj) {
        auto geom = obj.get_geometry();
        double x = std::min(geom[0].first, geom[1].first);
        double y = std::min(geom[0].second, geom[1].second);
        double side = obj.get_side();

        std::stringstream ss;
        ss << "  <rect x=\"" << x << "\" y=\"" << y 
           << "\" width=\"" << side << "\" height=\"" << side << "\"";
        
        if (obj.is_filled()) {
            ss << " fill=\"" << colorToSVG(obj.get_color()) << "\"";
        } else {
            ss << " fill=\"none\"";
        }
        
        ss << " stroke=\"" << colorToSVG(obj.get_line_color()) << "\""
           << " stroke-width=\"" << obj.get_line_width() << "\" />\n";

        // Add text if present
        if (!obj.get_text().empty()) {
            double text_x = x + side / 2;
            double text_y = y + side / 2;
            ss << "  <text x=\"" << text_x << "\" y=\"" << text_y 
               << "\" text-anchor=\"middle\" dominant-baseline=\"middle\""
               << " fill=\"" << colorToSVG(obj.get_text_color()) << "\""
               << " font-size=\"" << obj.get_text_size() << "\""
               << " " << textStyleToSVG(obj.get_text_style()) << ">"
               << obj.get_text() << "</text>\n";
        }

        svgContent += ss.str();
    }

    void SVGPrinter::print_line(const obj::Line& obj) {
        auto geom = obj.get_geometry();

        std::stringstream ss;
        ss << "  <line x1=\"" << geom[0].first << "\" y1=\"" << geom[0].second 
           << "\" x2=\"" << geom[1].first << "\" y2=\"" << geom[1].second << "\""
           << " stroke=\"" << colorToSVG(obj.get_color()) << "\""
           << " stroke-width=\"" << obj.get_width() << "\" />\n";

        // Add text if present (at midpoint)
        if (!obj.get_text().empty()) {
            double text_x = (geom[0].first + geom[1].first) / 2.0;
            double text_y = (geom[0].second + geom[1].second) / 2.0;
            ss << "  <text x=\"" << text_x << "\" y=\"" << text_y 
               << "\" text-anchor=\"middle\" dominant-baseline=\"middle\""
               << " fill=\"" << colorToSVG(obj.get_text_color()) << "\""
               << " font-size=\"" << obj.get_text_size() << "\""
               << " " << textStyleToSVG(obj.get_text_style()) << ">"
               << obj.get_text() << "</text>\n";
        }

        svgContent += ss.str();
    }

    void SVGPrinter::print_arrow(const obj::Arrow& obj) {
        auto geom = obj.get_geometry();
        double x1 = geom[0].first, y1 = geom[0].second;
        double x2 = geom[1].first, y2 = geom[1].second;

        // Calculate arrow head
        double angle = std::atan2(y2 - y1, x2 - x1);
        double arrowLength = 10.0;
        double arrowAngle = M_PI / 6; // 30 degrees

        double arrow_x1 = x2 - arrowLength * std::cos(angle - arrowAngle);
        double arrow_y1 = y2 - arrowLength * std::sin(angle - arrowAngle);
        double arrow_x2 = x2 - arrowLength * std::cos(angle + arrowAngle);
        double arrow_y2 = y2 - arrowLength * std::sin(angle + arrowAngle);

        std::stringstream ss;
        // Main line
        ss << "  <line x1=\"" << x1 << "\" y1=\"" << y1 
           << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\""
           << " stroke=\"" << colorToSVG(obj.get_color()) << "\""
           << " stroke-width=\"" << obj.get_width() << "\" />\n";

        // Arrow head (based on points_to direction)
        if (obj.points_to().find("end") != std::string::npos || 
            obj.points_to().find("right") != std::string::npos) {
            ss << "  <polygon points=\""
               << x2 << "," << y2 << " "
               << arrow_x1 << "," << arrow_y1 << " "
               << arrow_x2 << "," << arrow_y2 << "\""
               << " fill=\"" << colorToSVG(obj.get_color()) << "\" />\n";
        }

        // Add text if present
        if (!obj.get_text().empty()) {
            double text_x = (x1 + x2) / 2.0;
            double text_y = (y1 + y2) / 2.0;
            ss << "  <text x=\"" << text_x << "\" y=\"" << text_y 
               << "\" text-anchor=\"middle\" dominant-baseline=\"middle\""
               << " fill=\"" << colorToSVG(obj.get_text_color()) << "\""
               << " font-size=\"" << obj.get_text_size() << "\""
               << " " << textStyleToSVG(obj.get_text_style()) << ">"
               << obj.get_text() << "</text>\n";
        }

        svgContent += ss.str();
    }

    void SVGPrinter::print_picture(const obj::Picture& obj) {
        auto geom = obj.get_geometry();
        double x = std::min(geom[0].first, geom[1].first);
        double y = std::min(geom[0].second, geom[1].second);
        double width = obj.get_width();
        double height = obj.get_height();

        std::stringstream ss;
        // Embed image using xlink:href
        ss << "  <image x=\"" << x << "\" y=\"" << y 
           << "\" width=\"" << width << "\" height=\"" << height << "\""
           << " href=\"" << obj.get_path() << "\" />\n";

        // Optional border
        if (obj.get_line_width() > 0) {
            ss << "  <rect x=\"" << x << "\" y=\"" << y 
               << "\" width=\"" << width << "\" height=\"" << height << "\""
               << " fill=\"none\""
               << " stroke=\"" << colorToSVG(obj.get_line_color()) << "\""
               << " stroke-width=\"" << obj.get_line_width() << "\" />\n";
        }

        // Add text if present
        if (!obj.get_text().empty()) {
            double text_x = x + width / 2;
            double text_y = y + height + 15; // Below the image
            ss << "  <text x=\"" << text_x << "\" y=\"" << text_y 
               << "\" text-anchor=\"middle\""
               << " fill=\"" << colorToSVG(obj.get_text_color()) << "\""
               << " font-size=\"" << obj.get_text_size() << "\""
               << " " << textStyleToSVG(obj.get_text_style()) << ">"
               << obj.get_text() << "</text>\n";
        }

        svgContent += ss.str();
    }

    void SVGPrinter::print_text(const obj::Text& obj) {
        auto geom = obj.get_geometry();
        double x = geom[0].first;
        double y = geom[0].second;

        std::stringstream ss;
        ss << "  <text x=\"" << x << "\" y=\"" << y 
           << "\" fill=\"" << colorToSVG(obj.get_color()) << "\""
           << " font-size=\"" << obj.get_size() << "\""
           << " " << textStyleToSVG(obj.get_style()) << ">"
           << obj.get_text() << "</text>\n";

        svgContent += ss.str();
    }

    // Method to get the complete SVG content
    std::string SVGPrinter::getSVGContent() const {
        return svgContent;
    }

    // Method to clear content for new slide
    void SVGPrinter::clearContent() {
        svgContent.clear();
    }

    // Method to add content
    void SVGPrinter::addContent(const std::string& content) {
        svgContent += content;
    }
}
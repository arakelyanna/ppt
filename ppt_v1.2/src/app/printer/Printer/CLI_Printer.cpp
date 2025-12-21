#include "Printer.h"
#include "../../../objects/Shapes/Shape.h"

namespace out{
    void CLIPrinter::printSlide(std::shared_ptr<doc::Slide> slide) {
        output << "\n|||||||||||||||||||| Slide " << slide->get_id() << " ||||||||||||||||||||\n";
    }
    
    void CLIPrinter::print_rectangle(const obj::Rectangle& obj) {
        output << "===============Rectangle===============\n";
        output << "Type: " << obj.get_type() << "\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  "), " << " (" << obj.get_geometry()[1].first << ", "<< obj.get_geometry()[1].second <<  ")}\n"
            << "Height: " << obj.get_height() << '\n'
            << "Width: " << obj.get_width() << '\n'
            << "Filling: " << std::boolalpha <<  obj.is_filled() << '\n'
            << "Filling Color: " << obj.get_color() << '\n'
            << "Line Color: " << obj.get_line_color() << '\n'
            << "Line Width: " << obj.get_line_width() << '\n'
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_text_color() << '\n'
            << "Text Size: " << obj.get_text_size() << '\n'
            << "Text Style: " << obj.get_text_style() << '\n';
        output << "==============================\n";
    }

    void CLIPrinter::print_triangle(const obj::Triangle& obj) {
        output << "===============Triangle===============\n";
        output << "Type: " << obj.get_type() << "\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  "), " << " (" << obj.get_geometry()[1].first << ", "<< obj.get_geometry()[1].second <<  "), " << obj.get_geometry()[2].first << ", "<< obj.get_geometry()[2].second << ")}\n"
            << "Sides: " << obj.get_sides()[0] << ", " << obj.get_sides()[1] << ", " << obj.get_sides()[2]<< '\n'
            << "Filling: " << std::boolalpha <<  obj.is_filled() << '\n'
            << "Filling Color: " << obj.get_color() << '\n'
            << "Line Color: " << obj.get_line_color() << '\n'
            << "Line Width: " << obj.get_line_width() << '\n'
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_text_color() << '\n'
            << "Text Size: " << obj.get_text_size() << '\n'
            << "Text Style: " << obj.get_text_style() << '\n';
        output << "==============================\n";
    }

    void CLIPrinter::print_circle(const obj::Circle& obj) {
        output << "===============Circle===============\n";
        output << "Type: " << obj.get_type() << "\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  "), " << " (" << obj.get_geometry()[1].first << ", "<< obj.get_geometry()[1].second <<  ")}\n"
            << "Radius: " << obj.get_radius() << '\n'
            << "Filling: " << std::boolalpha <<  obj.is_filled() << '\n'
            << "Filling Color: " << obj.get_color() << '\n'
            << "Line Color: " << obj.get_line_color() << '\n'
            << "Line Width: " << obj.get_line_width() << '\n'
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_text_color() << '\n'
            << "Text Size: " << obj.get_text_size() << '\n'
            << "Text Style: " << obj.get_text_style() << '\n';
        output << "==============================\n";
    }

    void CLIPrinter::print_square(const obj::Square& obj) {
        output << "===============Square===============\n";
        output << "Type: " << obj.get_type() << "\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  "), " << " (" << obj.get_geometry()[1].first << ", "<< obj.get_geometry()[1].second <<  ")}\n"
            << "Side: " << obj.get_side() << '\n'
            << "Filling: " << std::boolalpha <<  obj.is_filled() << '\n'
            << "Filling Color: " << obj.get_color() << '\n'
            << "Line Color: " << obj.get_line_color() << '\n'
            << "Line Width: " << obj.get_line_width() << '\n'
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_text_color() << '\n'
            << "Text Size: " << obj.get_text_size() << '\n'
            << "Text Style: " << obj.get_text_style() << '\n';
        output << "==============================\n";
    }

    void CLIPrinter::print_line(const obj::Line& obj) {
        output << "===============Line===============\n";
        output << "Type: " << obj.get_type() << "\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  "), " << " (" << obj.get_geometry()[1].first << ", "<< obj.get_geometry()[1].second <<  ")}\n"
            << "Length: " << obj.get_length() << '\n'
            << "Line Color: " << obj.get_color() << '\n'
            << "Line Width: " << obj.get_width() << '\n'
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_text_color() << '\n'
            << "Text Size: " << obj.get_text_size() << '\n'
            << "Text Style: " << obj.get_text_style() << '\n';
        output << "==============================\n";
    }

    void CLIPrinter::print_arrow(const obj::Arrow& obj) {
        output << "===============Arrow===============\n";
        output << "Type: " << obj.get_type() << "\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  "), " << " (" << obj.get_geometry()[1].first << ", "<< obj.get_geometry()[1].second <<  ")}\n"
            << "Length: " << obj.get_length() << '\n'
            << "Pointing: " << obj.points_to() << '\n'
            << "Line Color: " << obj.get_color() << '\n'
            << "Line Width: " << obj.get_width() << '\n'
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_text_color() << '\n'
            << "Text Size: " << obj.get_text_size() << '\n'
            << "Text Style: " << obj.get_text_style() << '\n';
        output << "==============================\n";
    }

    void CLIPrinter::print_picture(const obj::Picture& obj) {
        output << "===============Picture===============\n";
        output << "Type: " << obj.get_type() << "\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  "), " << " (" << obj.get_geometry()[1].first << ", "<< obj.get_geometry()[1].second <<  ")}\n"
            << "Height: " << obj.get_height() << '\n'
            << "Width: " << obj.get_width() << '\n'
            << "Path: " << obj.get_path() << '\n'
            << "Line Color: " << obj.get_line_color() << '\n'
            << "Line Width: " << obj.get_line_width() << '\n'
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_text_color() << '\n'
            << "Text Size: " << obj.get_text_size() << '\n'
            << "Text Style: " << obj.get_text_style() << '\n';
        output << "==============================\n";
    }

    void CLIPrinter::print_text(const obj::Text& obj) {
        output << "===============Text===============\n";
        output << "Type: Text\n"
            << "Geometry: {(" << obj.get_geometry()[0].first << ", "<< obj.get_geometry()[0].second <<  ")}\n"
            << "Text: " << obj.get_text() << '\n'
            << "Text Color: " << obj.get_color() << '\n'
            << "Text Size: " << obj.get_size() << '\n'
            << "Text Style: " << obj.get_style() << '\n';
        output << "==============================\n";
        
    }

}
#include "Visitor.h"
#include <fstream>
#include <sstream>

namespace out {
    
    void SVGPrinterVisitor::print() {
        if (!ppt) return;
        
        // Generate SVG for each slide
        for (size_t i = 0; i < ppt->size(); ++i) {
            printSlide(i);
        }
    }

    void SVGPrinterVisitor::printSlide(size_t pos) {
        if (!ppt || pos >= ppt->size()) return;
        
        auto slide = (*ppt)[pos];
        if (!slide) return;

        // Create SVG printer and set it as the current printer
        auto svgCreator = std::make_shared<SVGPrinter>();
        printer = svgCreator;

        // Start SVG document
        std::stringstream svg;
        svg << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
        svg << "<svg width=\"960\" height=\"720\" xmlns=\"http://www.w3.org/2000/svg\" ";
        svg << "xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n";
        svg << "  <!-- Slide " << slide->get_id() << " -->\n";
        svg << "  <rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
        
        svgCreator->addContent(svg.str());
        
        // Visit all objects on the slide using iterators
        for (auto it = slide->begin(); it != slide->end(); ++it) {
            const auto& obj = *it;
            if (obj) {
                obj->accept(*this);
            }
        }
        
        // Close SVG document
        svgCreator->addContent("</svg>\n");
        
        // Save to file
        std::string filename = "./ztest/drawings/slide_" + std::to_string(pos) + ".svg";
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << svgCreator->getSVGContent();
            outFile.close();
            std::cout << "SVG saved to: " << filename << std::endl;
        } else {
            std::cerr << "Error: Could not create file " << filename << std::endl;
        }
    }

    void SVGPrinterVisitor::visit(const obj::Rectangle& obj) const {
        if (printer) {
            printer->print_rectangle(obj);
        }
    }

    void SVGPrinterVisitor::visit(const obj::Triangle& obj) const {
        if (printer) {
            printer->print_triangle(obj);
        }
    }

    void SVGPrinterVisitor::visit(const obj::Circle& obj) const {
        if (printer) {
            printer->print_circle(obj);
        }
    }

    void SVGPrinterVisitor::visit(const obj::Square& obj) const {
        if (printer) {
            printer->print_square(obj);
        }
    }

    void SVGPrinterVisitor::visit(const obj::Picture& obj) const {
        if (printer) {
            printer->print_picture(obj);
        }
    }

    void SVGPrinterVisitor::visit(const obj::Text& obj) const {
        if (printer) {
            printer->print_text(obj);
        }
    }

    void SVGPrinterVisitor::visit(const obj::Line& obj) const {
        if (printer) {
            printer->print_line(obj);
        }
    }

    void SVGPrinterVisitor::visit(const obj::Arrow& obj) const {
        if (printer) {
            printer->print_arrow(obj);
        }
    }
}
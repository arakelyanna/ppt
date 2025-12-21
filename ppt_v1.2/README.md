# PowerPoint Presentation Editor (CLI)

A command-line based presentation editor written in C++20 that supports creating, editing, and exporting slides with various shapes, text, and images.

## Features

### 🎨 Shape Support
- **Filled Shapes**: Rectangle, Circle, Square, Triangle
- **Line Shapes**: Line, Arrow
- **Media**: Pictures (image embedding), Text
- **Styling**: Colors, line widths, fill options, text formatting

### 📊 Slide Management
- Create and remove slides
- Navigate between slides (current slide tracking)
- View slides in CLI or export as SVG
- Multi-slide presentations

### 💾 File Operations
- Open existing presentations
- Save presentations
- Serialization/Deserialization support

### ⚡ Advanced Features
- **Undo/Redo**: Full command history with undo/redo support
- **Visitor Pattern**: Extensible rendering system
  - CLI Printer (console output)
  - SVG Printer (vector graphics export)
- **Parser**: Natural language command parsing

## Building

### Prerequisites
- C++20 compatible compiler (GCC 10+ recommended)
- Make

### Compilation
```bash
make
```

### Running
```bash
# Start with new presentation
./ppt

# Open existing file
./ppt path/to/presentation.ppt
```

## Usage

### Basic Commands

#### Slide Management
```bash
# Add a new slide
add slide # removes first slide by default
add slide -at <index>

# Remove a slide
remove slide # removes first slide by default
remove slide -at <index>

# Show current slide number
current slide

# Set current slide
set current slide -to <index>

# Show specific slide in CLI
show slide -at <index>

# Show all slides in CLI
show

# Export specific slide as SVG
draw slide -at <index>

# Export all slides as SVG
draw
```

#### Adding Shapes
```bash
# Add a rectangle
add shape -rectangle -geometry (x1,y1) (x2,y2) -fill true -color red -line_color black -line_width 2 -text "Hello" -text_color white -text_size 16

# Add a circle
add shape -circle -geometry (cx,cy) (radius_point) -fill true -color blue

# Add a triangle
add shape -triangle -geometry (x1,y1) (x2,y2) (x3,y3) -fill false -line_color green -line_width 3

# Add a square
add shape -square -geometry (x1,y1) (x2,y2) -fill true -color yellow

# Add a line
add shape -line -geometry (x1,y1) (x2,y2) -color black -width 2

# Add an arrow
add shape -arrow -geometry (x1,y1) (x2,y2) -color black -width 2 -points_to end
```

#### Adding Text
```bash
add text -geometry (x,y) -text "My Text" -color black -size 24 -style bold
```

#### Adding Pictures
```bash
add picture -geometry (x1,y1) (x2,y2) -path /path/to/image.png -line_color black -line_width 2
```

#### Object Management
```bash
# Remove object at coordinate
remove object -at (x,y)
```

#### File Operations
```bash
# Save current presentation
save
save -file /path/to/file.ppt

# Open a presentation
open -file /path/to/file.ppt
```

#### History
```bash
# Undo last action
undo

# Redo last undone action
redo
```

#### Exit
```bash
# Exit the application
exit
# or
q
```

## Command Options Reference

### Shape Options
| Option | Type | Description | Shapes |
|--------|------|-------------|--------|
| `-shape` | string | Shape type (rectangle, circle, triangle, square, line, arrow) | All |
| `-geometry` | coords | Position coordinates | All |
| `-fill` | boolean | Fill the shape | Filled shapes |
| `-color` | string | Fill color or line color | All |
| `-line_color` | string | Border/line color | Filled shapes, Picture |
| `-line_width` | number | Border/line thickness | All |
| `-width` | number | Line thickness | Line, Arrow |
| `-text` | string | Text label | All shapes |
| `-text_color` | string | Text color | All shapes |
| `-text_size` | number | Text font size | All shapes |
| `-text_style` | string | Text style (bold, italic) | All shapes |
| `-points_to` | string | Arrow direction (start, end, both) | Arrow |

### Text Options
| Option | Type | Description |
|--------|------|-------------|
| `-geometry` | coord | Text position (x,y) |
| `-text` | string | Text content |
| `-color` | string | Text color |
| `-size` | number | Font size |
| `-style` | string | Font style (bold, italic) |

### Picture Options
| Option | Type | Description |
|--------|------|-------------|
| `-geometry` | coords | Position and size (x1,y1) (x2,y2) |
| `-path` | string | Image file path |
| `-line_color` | string | Border color |
| `-line_width` | number | Border thickness |

### General Options
| Option | Type | Description |
|--------|------|-------------|
| `-at` | number | Slide index or coordinate |
| `-to` | number | Target slide index |
| `-path` | string | File path |

## Architecture

### Core Components

```
├── app/
│   ├── cmd/           # Command system
│   │   ├── Commands/      # Command implementations
│   │   ├── CmdCreator/    # Command factories
│   │   └── CmdRegister/   # Command registry
│   ├── doc/           # Document model
│   │   ├── ppt/           # Presentation class
│   │   ├── Slide/         # Slide class
│   │   └── Editor/        # Editor with undo/redo
│   ├── printer/       # Output system
│   │   ├── Printer/       # Printer implementations
│   │   └── Visitor/       # Visitor implementations
│   └── files/         # Serialization
├── objects/           # Shape objects
│   ├── Shapes/        # Shape implementations
│   └── Text/          # Text object
└── parser/            # Command parser
    ├── Parser.cpp     # State machine parser
    ├── Tokenizer.cpp  # Lexical analyzer
    └── Token.cpp      # Token definitions
```

## Output Formats

### CLI Output
View slides directly in the terminal with detailed shape information:
```bash
show slide -at 0
```

### SVG Export
Export slides as scalable vector graphics:
```bash
draw                    # Export all slides
draw slide -at 0        # Export specific slide
```

Output: `slide_0.svg`, `slide_1.svg`, etc.


## Coordinate System

- Origin: Top-left corner (0, 0)
- X-axis: Increases to the right
- Y-axis: Increases downward
- Default canvas: 960x270(can be adjusted in `SVGPrinterVisitor.cpp`)

## Examples

### Create a Simple Presentation

```bash
# Start the application
./ppt

# Add a title slide with text
add text -geometry (400,300) -text "My Presentation" -color black -size 48 -style bold

# Add a rectangle behind the text
add shape -rectangle -geometry (200,250) (600,350) -fill true -color lightblue -line_color blue -line_width 3

# Add a new slide
add slide

# Add shapes on second slide
add shape -circle -geometry (400,300) (450,300) -fill true -color red
add shape -triangle -geometry (300,400) (500,400) (400,250) -fill true -color green

# Export as SVG
draw

# Save the presentation
save

# Exit
exit
```

### Undo/Redo Example

```bash
add slide              # Action 1
add shape -circle -geometry (100,100) (150,100)  # Action 2
undo                   # Undo Action 2
undo                   # Undo Action 1
redo                   # Redo Action 1
```
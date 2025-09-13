PPT-CLI
--------

PPT is a command-line tool for creating and editing slide presentations directly from your terminal.  
It supports adding text, pictures, and shapes with customizable properties, as well as basic slide management and history tracking.


USAGE
-----

Create and Open Files:
    new -n filename        Create a new board (presentation)
    open filename          Open an existing board

Slide Management:
    newslide -<int>        Add a new slide at position <int>
    current                Show the current slide
    info                   Show usage help

Adding Elements:

    addtext
        placement          Coordinates (x,y)
        font size          Numeric value
        font family        Example: Arial, Times New Roman
        color              Hex or named color
        value              Text content

    addpicture
        filepath           Path to image file
        placement          Coordinates
        size               (Width, Height)

    addshape -<type>
        Supported types: line, rectangle, square, triangle, circle, arrow

        line:
            placement
            angle
            length
            width
            color

        rectangle:
            placement
            angle
            height, width
            color
            filled (true/false)
            borderline width
            borderline color

        square:
            placement
            angle
            height
            color
            filled (true/false)
            borderline width
            borderline color

        triangle:
            placement
            angle
            sides (a, b, c)
            color
            filled (true/false)
            borderline width
            borderline color

        circle:
            placement
            radius
            color
            filled (true/false)
            borderline width
            borderline color

        arrow:
            placement
            angle
            length
            width
            color
            pointing <bool> (right, left)

Editing and History:
    undo                   Undo last action
    redo                   Redo last undone action
    history                Show history of actions

Saving:
    save                   Save current board
    save as -n newname -p /path/to/dir
                           Save as a new file (default path is ./)

NOTES
-----
- Angles are in degrees.
- Colors accept hex (#FF0000) or names (red).
- Placements use x,y coordinates relative to the slide’s top-left corner.


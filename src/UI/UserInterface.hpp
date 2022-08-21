#include <ncurses.h>

#include "Menu.hpp"

using namespace std;

/**
 * Uses ncurses to allow user to use this programs functionaly through terminal.
 */
class UserInterface{
public:
    /**
     * Constructor that initializes screen from ncurses while creating
     * root directory and NodeController.
     * @param root Pointer to root directory.
     * @param height Height of terminals' window.
     * @param width Width of terminals' window.
     */
    UserInterface( Directory * root, int height, int width );

    /**
     * Destructor ends ncurses with endwin()
     * which frees memory allocated by ncurses.
     */
    ~UserInterface() = default;

    /**
     * Runs user interface functionality.
     * Infinite cycle of reading input.
     * Method breaks when Q or q key is pressed.
     */
    void Run();

    /**
     * Toggles between left and right panel.
     */
    void TogglePanel();

    /**
     * Refreshes ncurses by loading new height and width.
     * Calls refresh methods of windows.
     */
    void Refresh();
private:
    /**
     * Height in lines of terminal window.
     */
    int _height;
    
    /**
     * Width in number of chars in line of terminal window.
     */
    int _width;
    
    /**
     * Pointer to root directory.
     */
    Directory * _root;
    
    /**
     * Left panel of screen.
     */
    Controller _left;
    
    /**
     * Right panel of screen.
     */
    Menu _right;
    
    /**
     * Pointer to currently using window. _left or _right.
     */
    Window * _using;
};

#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

const unsigned char PADDING = 2;

/**
 * Virtual class for types of windows used in user interface.
 */
class Window{
public:
    /**
     * Implicit constructor that initializes window big as terminal's window.
     */
    Window();

    /**
     * Constructor that initializes exact position and size of window.
     * @param height Height to be used.
     * @param width Width to be used.
     * @param sY Y coordination to window's left upper corner.
     * @param sX X coordination to window's left upper corner.
     */
    Window( int height, int width, int sY, int sX );
    
    /**
     * Virtual destructor.
     */
    virtual ~Window();

    /**
     * Virtual refreshing method that updates window's height and width.
     * Must be implemented in childen classes.
     * @param height Height of a box to which it should renspond.
     * @param width Width of a box to which it should renspond.
     */
    virtual void Refresh( int height, int width ) = 0;

    /**
     * Virtual showing method that shows content in a window.
     * Must be implemented in childen classes.
     */
    virtual void Show() const = 0;
    
    /**
     * Virtual inputting method. Handles input.
     * Must be implemented in childen classes.
     * @param choice Value of a already managed input to be used.
     * @return Boolean to tell if was input used by this method.
     */
    virtual bool Input( int choice ) = 0;
protected:
    
    /**
     * Height of a window.
     */
    int _height;
    
    /**
     * Width of a window.
     */
    int _width;
    
    /**
     * Y coordination to window's left upper corner.
     */
    int _startY;
    
    /**
     * X coordination to window's left upper corner.
     */
    int _startX;
    WINDOW * _win;
};

#endif /* WINDOW_H */

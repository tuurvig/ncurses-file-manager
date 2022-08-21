#ifndef MENU_H
#define MENU_H

#include "Controller.hpp"

using namespace std;

/**
 * Shows window with menubar options.
 */
class Menu : public Window{
public:
    /**
     * Menu constructor.
     * @param control Pointer to a Controller. Menubar options calls Controllers methods.
     * @param height Height to be used.
     * @param width Width to be used.
     * @param sY Y coordination to menu's left upper corner.
     * @param sX X coordination to menu's left upper corner.
     */
    Menu( Controller * control, int height, int width, int sY, int sX );
    
    /**
     * Overriden refreshing method that updates window's height and width.
     * @param height Height of a box to which it should renspond.
     * @param width Width of a box to which it should renspond.
     */
    void Refresh( int height, int width ) override;
    
    /**
     * Overriden showing method that shows menubar options.
     */
    void Show() const override;

    /**
     * Overriden inputting method. Handles input.
     * @param choice Value of a already managed input to be used.
     * @return Boolean to tell if was input used by this method.
     */
    bool Input( int choice ) override;
private:
    /**
     * Changes selection of menubar options in upward direction.
     */
    void MoveUp();
    
    /**
     * Changes selection of menubar options in downward direction.
     */
    void MoveDown();
    
    /**
     * Manipulates with methods in Controller class. Called by pressing ENTER.
     */
    void Manipulate();

    /**
     * Pointer to a Controller. Menubar options calls Controllers methods.
     */
    Controller * _remote;

    /**
     * Index of currently highlighted option in menubar.
     */
    unsigned _highlighted;

    /**
     * Menubar options.
     */
    vector< string > _choices;

    /**
     * Count of shown menubar options.
     */
    size_t _size; 
};

#endif /* MENU_H */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <regex>

#include "../Core/DirNavigation.hpp"
#include "Dialog/Info.hpp"
#include "Dialog/TextBox.hpp"
#include "Dialog/YesNo.hpp"

using namespace std;

/**
 * Controls DirNavigation, shows contents of directories and manipulates with nodes in directory.
 */
class Controller : public Window{
public:
    /**
     * Constructor initializes DirNavigation and starts in root Directory.
     * @param root Pointer to a root Directory.
     * @param height Height to be used.
     * @param width Width to be used.
     * @param sY Y coordination to controller's left upper corner.
     * @param sX X coordination to controller's left upper corner.
     */
    Controller( Directory * root, int height, int width, int sY, int sX );

    /**
     * Overriden inputting method. Handles input.
     * @param choice Value of a already managed input to be used.
     * @return Boolean to tell if was input used by this method.
     */
    bool Input( int choice ) override;

    /**
     * Virtual refreshing method that updates window's height and width.
     * @param height Height of a box to which it should renspond.
     * @param width Width of a box to which it should renspond.
     */
    void Refresh( int height, int width ) override;

    /**
     * Shows content of a current directory. Only a limited number of nodes.
     */
    void Show() const override;

    /**
     * Creates node in a directory.
     * @param type tells which node it should make.
     * @return If operation was successful.
     */
    bool Create( int type );

    /**
     * Erases node from a directory.
     * @return If operation was successful.
     */
    bool Erase();

    /**
     * Renames node.
     * @return If operation was successful.
     */
    bool Rename();

    /**
     * Copies node.
     * @return If operation was successful.
     */
    bool Copy();
    
    /**
     * Moves node.
     * @return If operation was successful.
     */
    bool Move();

    /**
     * @return if currently highlighted directory is not that iterates back. 
     */
    bool IsPrevious() const;
private:
    /**
     * Opens dialog and takes user defined regular expression.
     */
    void SetRegex();

    /**
     * Takes regular expression and executes Erase function on nodes that match.
     */
    bool RegexErase();
    
    /**
     * Takes regular expression and executes Copy function on nodes that match.
     */
    bool RegexCopy();

    /**
     * Takes regular expression and executes Move function on nodes that match.
     */
    bool RegexMove();

    /**
     * Method that resets screen when big update happens, so it won't leave residue after itself.
     */
    void resetScreen();
    
    /**
     * Changes currently highlighted node in upward direction until it hits the first one.
     */
    void MoveUp();
    
    /**
     * Changes currently highlighted node in downward direction until it hits the last one.
     */
    void MoveDown();

    /**
     * Iterates into a currently highlighted directory.
     */
    void Advance();

    /**
     * Iterates back into a parent directory.
     */
    void Retreat();

    /**
     * Instance of a class that handles directory iteration.
     */
    DirNavigation _control;
    
    /**
     * Index to a first shown directory node in Controller.
     */
    unsigned _min;
    
    /**
     * Index to a last shown directory node in Controller.
     */
    unsigned _max;

    /**
     * Index to a currently highlighted directory node in Controller.
     */
    unsigned _highlighted;

    string _check;
};

#endif /* CONTROLLER_H */

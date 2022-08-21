#ifndef DIALOG_H
#define DIALOG_H

#include <string>
#include "../Window.hpp"

using namespace std;

/**
 * Virtual class Dialog is a parent class types of Dialog windows.
 */
class Dialog : public Window{
public:
    /**
     * Move constructor.
     * @param message String to a mandatory message that shows in dialog.
     */
    Dialog( string && message ) noexcept;

    /**
     * Copy constructor.
     * @param message String to a mandatory message that shows in dialog.
     */
    Dialog( const string & message );
    
    /**
     * Implicit method Refresh that gets terminals width and height 
     * and then calls the latter function.
     */
    void Refresh();

    /**
     * Overriden refreshing method that updates window's height and width.
     * @param height Height of a box to which it should renspond.
     * @param width Width of a box to which it should renspond.
     */
    void Refresh( int height, int width ) override;
    
    /**
     * Overriden showing method that shows string in a dialog window.
     */
    void Show() const override;

    /**
     * Virtual method that opens Dialog a waits in infinite loop until
     * the action of a dialog windows is finished.
     * Must be implemented in it's children.
     * @return Boolean that describes what happened in dialog. 
     */
    virtual bool Open() = 0;

    /**
     * Virtual inputting method. Handles input.
     * @param choice Value of an already managed input to be used.
     * @return Boolean to tell if was input used by this method.
     */
    bool Input( int choice ) override = 0;
protected:
    /**
     * Virtual method that shows dialogs functionaly.
     * Must be implemented in it's children.
     */
    virtual void showWindow() const = 0;

    /**
     * Message shown in dialog.
     */
    string _message;
};

#endif /* DIALOG_H */
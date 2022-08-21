#ifndef INFO_H
#define INFO_H

#include "Dialog.hpp"

/**
 * Info dialog only informs.
 */
class Info : public Dialog{
public:
    /**
     * Move constructor
     * @msg Information that will be shown in this dialog.
     */
    Info( string && msg ) noexcept;
    
    /**
     * Copy constructor
     * @msg Information that will be shown in this dialog.
     */
    Info( const string & msg );

    /**
     * Overriden method that opens Dialog a waits in infinite loop until
     * the action of a dialog windows is finished.
     * @return Boolean that describes what happened in dialog.
     */
    bool Open() override;

    /**
     * Overriden inputting method. Handles input.
     * @param choice Value of an already managed input to be used.
     * @return Boolean to tell if was input used by this method.
     */
    bool Input( int choice ) override;
private:
    /**
     * Overriden method that shows dialogs functionaly.
     * Must be implemented in it's children.
     */
    void showWindow() const;
};

#endif /* INFO_H */
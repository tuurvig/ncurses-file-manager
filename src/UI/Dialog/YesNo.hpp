#ifndef YESNO_H
#define YESNO_H

#include "Dialog.hpp"

/**
 * YesNo dialog, that has two buttons. Asks questions.
 */
class YesNo : public Dialog{
public:
    /**
     * Move constructor
     * @msg Question that will be shown in this dialog.
     */
    YesNo( string && msg ) noexcept;

    /**
     * Move constructor
     * @msg Question that will be shown in this dialog.
     */
    YesNo( const string & msg );
    
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

    /**
     * Contains "Yes" and "No".
     */
    string _choices[2];

    /**
     * Tells which option is currently selected.
     */
    bool _answer;
};

#endif /* YESNO_H */
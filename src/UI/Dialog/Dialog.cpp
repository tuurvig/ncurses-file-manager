#include "Dialog.hpp"

Dialog::Dialog( string && message ) noexcept : _message( move( message ) ){}

Dialog::Dialog( const string & message ) : _message( message ){}

void Dialog::Refresh(){
    int height, width;
    getmaxyx( stdscr, height, width );
    Refresh( height, width );
}

void Dialog::Refresh( int height, int width ){
    if( _height != height || _width != width ){
        _height = height;
        _width = width;

        wclear( _win );
        delwin( _win );
        _win = newwin( _height, _width, _startY, _startX );
    }
}

void Dialog::Show() const{
    wclear( _win );
    box( _win, 0, 0 );

    mvwprintw( _win, _height / 3 + 1, _width / 2 + 1 - _message.size() / 2, _message.c_str() );

    showWindow();

    wrefresh( _win );
}

#include "YesNo.hpp"

YesNo::YesNo( string && msg ) noexcept : Dialog( move( msg ) ), 
_choices( { " No ", " Yes " } ), _answer( false ){
    keypad( _win, true );
}

YesNo::YesNo( const string & msg ) : Dialog( msg ), 
_choices( { " No ", " Yes " } ), _answer( false ){
    keypad( _win, true );
}

bool YesNo::Open(){
    int choice;
    while( true ){
        Refresh();

        Show();

        choice = wgetch( _win );

        if( Input( choice ) ) break;
    }
    wclear( stdscr );

    return _answer;
}

bool YesNo::Input( int choice ){
    switch( choice ){
        case 10: return true;
        case KEY_LEFT : _answer = !_answer;
            return false;
        case KEY_RIGHT : _answer = !_answer;
            return false;
        default: return false;
    }
}

void YesNo::showWindow() const{
    int h = ( _height * 2 ) / 3;
    int w;

    for( int i = 0; i < 2; i++ ){
        w = ( _width * ( i + 1 ) ) / 3 - 2;
        if( _answer == i ){
            wattron( _win, A_REVERSE );
            wmove( _win, h - 1, w - 2 );
            whline( _win, ' ', 4 + i );
            wmove( _win, h + 1, w - 2 );
            whline( _win, ' ', 4 + i );
        }
        mvwprintw( _win, h, w - 2, ( _choices[ i ] ).c_str() );
        wattroff( _win, A_REVERSE ); 
    }
}
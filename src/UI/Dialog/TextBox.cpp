#include "TextBox.hpp"

TextBox::TextBox( string && msg, string && check ) noexcept : Dialog( move( msg ) ),
_answer( false ), _choices( { " Cancel ", "   OK   " } ),
_check( move( check ) ){
    keypad( _win, true );
} 

TextBox::TextBox( const string & msg, const string & check ) : Dialog( msg ),
_answer( false ), _choices( { " Cancel ", "   OK   " } ),
_check( check ){
    keypad( _win, true );
}

bool TextBox::Open(){
    int choice;
    while( true ){
        Refresh();

        Show();

        choice = wgetch( _win );

        if( Input( choice ) ) break;
    }
    wclear( stdscr );
    curs_set( 0 );
    if( _input.empty() ) return false;
    else return _answer;
}

bool TextBox::Input( int choice ){
    switch( choice ){
        case 10: return true;
        case KEY_LEFT : _answer = !_answer;
            return false;
        case KEY_RIGHT : _answer = !_answer;
            return false;
        case KEY_BACKSPACE : if( !_input.empty() )_input.pop_back();
            return false;
        default: Append( choice );
            return false;
    }
}

void TextBox::Append( int letter ){
    if( ( size_t )( _width - 4 ) > _input.size() ){
        _input += letter;
        if( !regex_match( _input, _check ) ){
            _input.pop_back();
        }
    }
}

void TextBox::showWindow() const{
    curs_set( 0 );

    int h, w;
    h = ( _height * 3 ) / 4;
    for( int i = 0; i < 2; i++ ){
        w = ( _width * ( i + 1 ) ) / 3 - 2;
        if( _answer == i ){
            wattron( _win, A_REVERSE );
            wmove( _win, h - 1, w - 2 );
            whline( _win, ' ', 8 );
            wmove( _win, h + 1, w - 2 );
            whline( _win, ' ', 8 );
        }
        mvwprintw( _win, h, w - 2, ( _choices[ i ] ).c_str() );
        wattroff( _win, A_REVERSE ); 
    }

    curs_set( 1 );

    h = ( _height * 3 ) / 5;

    mvwprintw( _win, h - 2, _width / 2 - _input.size() / 2, _input.c_str() );

    wrefresh( _win );
}
#include "Info.hpp"

Info::Info( string && msg ) noexcept : Dialog( move( msg ) ){}

Info::Info( const string & msg ) : Dialog( msg ){}

bool Info::Open(){
    int choice;
    while( true ){
        Refresh();

        Show();

        choice = wgetch( _win );

        if( Input( choice ) ) break;
    }

    wclear( _win );

    return true;
}

bool Info::Input( int choice ){
    switch( choice ){
        case 10: return true;
        default: return false;
    }
}

void Info::showWindow() const{
    int h = ( _height * 2 ) / 3;
    int w = _width / 2;

    wattron( _win, A_REVERSE );
    wmove( _win, h - 1, w - 2 );
    whline( _win, ' ', 4 );
    mvwprintw( _win, h, w - 2, " OK " );
    wmove( _win, h + 1, w - 2 );
    whline( _win, ' ', 4 );
    
    wattroff( _win, A_REVERSE ); 
}
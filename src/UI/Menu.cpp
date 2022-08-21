#include "Menu.hpp"

using namespace std;

Menu::Menu( Controller * control, int height, int width, int sY, int sX )
: Window( height, width, sY, sX ), _remote( control ), _highlighted( 0 ),
_choices({ "Create directory", "Create File", "Create symbolic link", "Erase", "Move", "Copy", "Rename" }){
    _size = _choices.size();
}

void Menu::Refresh( int height, int width ){
   if( _remote->IsPrevious() ){
       _size = 3;
       if( _highlighted >= _size ) _highlighted = 0;
   }
   else _size = _choices.size();
   if( height - 2 != _height || ( width - PADDING ) / 2 != _width ){
      _height = height - 2;
      _width = ( width - PADDING ) / 2;
      _startX = ( width + PADDING ) / 2;

      delwin( _win );
      _win = newwin( _height, _width, _startY, _startX );
   }
}

void Menu::Show() const{
   box( _win, 0, 0 );
   mvwprintw( _win, 0, ( _width - PADDING ) / 2 - 2, " Menu " );
   for( unsigned i = 0; i < _choices.size(); i++ ){
       if( i >= _size ){
           wmove( _win, i + ( ( _height - PADDING ) / 2 ) - ( _choices.size() / 2 ), 1 );
           whline( _win, ' ', _width - PADDING - 2 );
       }
       else{
            if( i == _highlighted )
                wattron( _win, A_REVERSE );
            mvwprintw( _win, i + ( ( _height - PADDING ) / 2 ) - ( _choices.size() / 2 ),
            ( ( _width - PADDING ) / 2 ) - ( _choices[i].size() / 2 + 1 ),
            ( ' ' + _choices[ i ] + ' ' ).c_str() );
            wattroff( _win, A_REVERSE );
       }
   }
   wrefresh( _win );
}

bool Menu::Input( int choice ){
    switch( choice ){
      case KEY_UP : MoveUp();
         return true;
      case KEY_DOWN : MoveDown();
        return true;
      case 10 : Manipulate();
      default : break;
   }
   return false;
}

void Menu::MoveUp(){
   if( _highlighted > 0 ) --_highlighted;
   else _highlighted = _size - 1;
}

void Menu::MoveDown(){
   if( _highlighted < _size - 1 ) ++_highlighted;
   else _highlighted = 0;
}

void Menu::Manipulate(){
    if( _highlighted < 3 ) _remote->Create( _highlighted );
    switch( _highlighted ){
        case 3 : _remote->Erase(); 
            break;
        case 4 : _remote->Move();
            break;
        case 5 : _remote->Copy();
            break;
        case 6 : _remote->Rename();
            break;
    }
}
#include "UserInterface.hpp"

using namespace std;

UserInterface::UserInterface( Directory * root, int height, int width )
: _height( height ), _width( width ), _root( root ),
_left( root, height - 2, ( width / 2 ) - 2, 1, 1 ),
_right( &_left, height - 2, ( width / 2 ) - 1, 1, width / 2 + 1 ),
_using( &_left ){
   keypad( stdscr, true );
   curs_set( 0 );
}

void UserInterface::Refresh(){
   getmaxyx( stdscr, _height, _width );
   _left.Refresh( _height, _width );
   _right.Refresh( _height, _width );
}

void UserInterface::TogglePanel(){
  if( _using == &_left ) _using = &_right;
  else _using = &_left;
}

void UserInterface::Run(){
   refresh();

   while( true ){
      Refresh();

      _left.Show();
      _right.Show();

      int choice = getch();

      switch( choice ){
         case 'q' : case 'Q' : return;
         case '\t' : TogglePanel(); continue;
         default : break;
      }

      if( _using->Input( choice ) ) continue;
   }
}

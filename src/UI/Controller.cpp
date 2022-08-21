#include "Controller.hpp"

using namespace std;

Controller::Controller( Directory * root, int height, int width, int sY, int sX )
: Window( height, width, sY, sX ), _control( root ),
_min( 0 ), _max( _height - PADDING ),
_highlighted( 0 ){
   keypad( _win, true );
}

void Controller::Show() const{
   string print;
   box( _win, 0, 0 );
   wattron( _win, A_REVERSE );
   mvwprintw( _win, 0, 2, _control->ShowPath( _width ).c_str() );
   wattroff( _win, A_REVERSE );

   for( unsigned i = _min; i < _max && i < _control->NodeCount(); i++ ){
      print = _control[ i ]->Show( _width );
      if( i == _highlighted )
         wattron( _win, A_REVERSE );
      mvwprintw( _win, i - _min + 1, 1, print.c_str() );
      whline( _win, ' ', _width - print.size() - PADDING );
      wattroff( _win, A_REVERSE );
   }
   wrefresh( _win );
}

bool Controller::Input( int choice ){
   switch( choice ){
      case KEY_UP : MoveUp();
         return true;
      case KEY_DOWN : MoveDown();
         return true;
      case 10 : if( _control[ _highlighted ]->IsDIR() ) Advance();
         return true;
      case KEY_BACKSPACE : if( _control->Path() != "/" ) Retreat();
         return true;
      case 'h' : case 'H' :
         _control->ToggleHidden();
         _control->LoadContents();
         resetScreen();
         return true;
      default : break;
   }
   return false;
}

void Controller::Refresh( int height, int width ){
   if( height - PADDING != _height || width / 2 != _width ){
      _height = height - PADDING;
      _width = width / 2;

      unsigned lower = ( _height - PADDING ) / 2;
      unsigned upper = _height - lower;
      if( _highlighted - _min <= lower ){ _min = 0; _max = _height - PADDING; }
      else if( _control->NodeCount() - _highlighted <= upper ){ 
          _max = _height - PADDING + _highlighted; 
          _min = _max - _height + PADDING;
        }
      else{ _min = _highlighted - lower; _max = _highlighted + upper; }

      delwin( _win );
      _win = newwin( _height, _width, _startX, _startY );
   }
}

bool Controller::Create( int type ){
    bool x = false;
    string choices[ 3 ] = { "directory", "file", "symbolic link" };
    TextBox userInput( "Enter name for new " + choices[ type ] + ":", "[\\w\\-\\. ]+" );
    if( userInput.Open() ){
        switch( type ){
            case 0: x = _control->CreateDir( userInput.GetInput() );
                break;
            case 1: x = _control->CreateFile( userInput.GetInput() );
                break;
            case 2: 
                TextBox absolute( "Enter absolute path for link:", "[\\w\\-\\./ ]+" );
                if( absolute.Open() ){
                    x = _control->CreateLink( userInput.GetInput(), absolute.GetInput() );
                }
                break;
        }
        if( !x ){
            Info error( "Sorry, " + choices[ type ] + " can't be created.");
            error.Open();
        }
    }
    return x;
}

bool Controller::Erase(){
    bool x = false;
        YesNo question(
            "Do you really wish to delete \"" + _control[ _highlighted ]->GetName() + "\"?" );
        if( question.Open() ){
            x = _control[ _highlighted ]->Erase();
            if( x ){
                _control->RemoveNode( _highlighted );
                resetScreen();
            }
            else{
                Info error( "An error occured. Can't be deleted." );
                error.Open();
            }
        }
    return x;
}

bool Controller::Rename(){
    bool x = false;
    TextBox userInput( "Enter new name for " + _control[ _highlighted ]->GetName() + ":", "[\\w\\-\\. ]+" );
    if( userInput.Open() ){
        x = _control[ _highlighted ]->Rename( userInput.GetInput() );
        if( !x ){
            Info error( "An error occured. Can't be renamed." );
            error.Open();
        }
    }
    return x;
}

bool Controller::Copy(){
    bool x = false;
        TextBox userInput( "Enter absolute path to directory where " + _control[ _highlighted ]->GetName() + " will be copied:", "[\\w\\-\\./ ]+" );
        if( userInput.Open() ){
            string newfile = userInput.GetInput() + _control[ _highlighted ]->GetName(); 
            struct stat buf;
            bool write = true;
            if( stat( newfile.c_str(), &buf ) != -1 ){
                YesNo question( "Already exists. Overwrite anyway?");
                write = question.Open();
            }
            if( write ){
                x = _control[ _highlighted ]->Copy( newfile );
                if( !x ){
                    Info error( "An error occured. Can't be copied." );
                    error.Open();
                }
            } 
        }
    return x;
}

bool Controller::Move(){
    bool x = false;
        TextBox userInput( "Enter absolute path to directory where " + _control[ _highlighted ]->GetName() + " will be moved:", "[\\w\\-\\./ ]+" );
        if( userInput.Open() ){
            string newfile = userInput.GetInput() + _control[ _highlighted ]->GetName();
            struct stat buf;
            bool write = true;
            if( stat( newfile.c_str(), &buf ) != -1 ){
                YesNo question( "Already exists. Overwrite anyway?");
                write = question.Open();
            }
            if( write ){
                x = _control[ _highlighted ]->Move( newfile );
                if( !x ){
                    Info error( "An error occured. Can't be moved." );
                    error.Open();
                }
                else{
                    _control->RemoveNode( _highlighted );
                    resetScreen();
                }
            } 
        }
    return x;
}

void Controller::resetScreen(){
   _highlighted = _min = 0;
   _max = _height - PADDING;
   wclear( _win );
}

void Controller::MoveUp(){
   if( _highlighted > 0 ){
      if( _highlighted == _min ){ --_min; --_max; }
      --_highlighted;
   }
}

void Controller::MoveDown(){
   if( _highlighted < _control->NodeCount() - 1 ){
      ++_highlighted;
      if( _highlighted == _max ){ ++_min; ++_max; }
   }
}

void Controller::Advance(){
   if( _control[ _highlighted ]->IsDIR() ){
      Directory * cur = ( Directory * )_control[ _highlighted ];
      if( cur->Path() == "/.." )
         Retreat();
      else{
         _control.Push( cur );
         resetScreen();
      }
   }
}

void Controller::Retreat(){
   _control.Pop();
   resetScreen();
}

bool Controller::IsPrevious() const{
    return _control[ _highlighted ]->GetName() == "..";
}


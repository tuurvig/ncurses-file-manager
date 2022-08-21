#include "Window.hpp"

using namespace std;

Window::Window(){
   getmaxyx( stdscr, _height, _width );
   _startX = _startY = 0;
   _win = newwin( _height, _width, _startY, _startX );
}

Window::Window( int height, int width, int sY, int sX )
: _height( height ), _width( width ), _startY( sY ), _startX( sX ){
   _win = newwin( _height, _width, _startY, _startX );
}

Window::~Window(){
   delwin( _win );
}
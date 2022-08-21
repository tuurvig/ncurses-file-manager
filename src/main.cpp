#include <iostream>
#include <string>
#include <ncurses.h>

using namespace std;

#include "UI/UserInterface.hpp"

int main() {
   int width, height;
   Directory root;

   initscr();
   noecho();
   cbreak();
   nodelay( stdscr, TRUE );

   getmaxyx( stdscr, height, width );
   UserInterface UI( &root, height, width );

   UI.Run();

   endwin();

   return 0;
}

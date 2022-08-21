#include "DirNavigation.hpp"

using namespace std;

DirNavigation::DirNavigation( Directory * root ){
   _nav.emplace_back( root );
}

Directory * & DirNavigation::Pop(){
   if( _nav.size() > 1 ){
      _nav.pop_back();
      _nav.back()->LoadContents();
   }
   return _nav.back();
}

void DirNavigation::Push( Directory * dir ){
   _nav.emplace_back( dir );
   _nav.back()->LoadContents();
}
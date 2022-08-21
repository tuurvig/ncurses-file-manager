#include "SymLink.hpp"

using namespace std;

SymLink::SymLink( const string &name, const string &path, Directory *parent ) : HierarchyNode( name, parent ){
   char buffer[ PATH_MAX ] = {0};
   if( readlink( path.c_str(), buffer, sizeof( buffer ) - 1 ) >= 0 ){
      if( buffer[0] != '/' )
         _link = GetAbsolutePath( buffer );
      else _link = buffer;
   }
}

const string& SymLink::GetLink() const{
   return _link;
}

string SymLink::Show( int width ) const{
   if( _name.size() > ( unsigned long )( width - 8 ) ){
      string ret = "@";
      ret.append( _name, 0, width - 8 );
      return ret + "...";
   }
   else return '@' + _name;
}

bool SymLink::Erase(){
    return ::remove( ( _parent->Path() + _name ).c_str() ) == 0;
}

bool SymLink::Rename( const string &name ){
    struct stat buf;
    string newFile = _parent->Path() + name;
    if( stat( newFile.c_str(), &buf ) == -1 
        && ::rename( ( _parent->Path() + _name ).c_str(), newFile.c_str() ) == 0 ){
        _name = name;
        return true;
    }
   return false;
}

bool SymLink::Copy( const string &path ){
    return symlink( _link.c_str(), path.c_str() ) == 0;
}

bool SymLink::Move( const string &path ){
    ::remove( path.c_str() );
    return ( Copy( path ) && Erase() );
}
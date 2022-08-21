#include "File.hpp"

using namespace std;

File::File(const string &name, size_t size, Directory *parent)
: HierarchyNode( name, parent ), _size( size ){}

string File::Show( int width ) const{
   if( _name.size() > ( unsigned long )( width - 8 ) ){
      string ret = " ";
      ret.append( _name, 0, width - 8 );
      return ret + "...";
   }
   else return ' ' + _name;
}

size_t File::Size() const{
   return _size;
}

bool File::Rename( const string &name ){
    struct stat buf;
    string newFile = _parent->Path() + name;
    if( stat( newFile.c_str(), &buf ) == -1 
        && ::rename( ( _parent->Path() + _name ).c_str(), newFile.c_str() ) == 0 ){
        _name = name;
        return true;
    }
   return false;
}

bool File::Erase(){
   return ::remove( ( _parent->Path() + _name ).c_str() ) == 0;
}

bool File::Copy( const string &path ){
    ifstream oldfile( _parent->Path() + _name, std::ios::binary );
    ofstream newfile( path, std::ios::binary );

    if( !oldfile.is_open() || !newfile.is_open() ) return false;
    newfile << oldfile.rdbuf();
    return true;
}

bool File::Move( const string &path ){
    return ::rename( ( _parent->Path() + _name ).c_str(), path.c_str() ) == 0;
}
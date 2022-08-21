#include "Directory.hpp"

using namespace std;

Directory::Directory()
: HierarchyNode( "", nullptr ), _path( "/" ), _showHidden( false ){
   LoadContents();
}

Directory::Directory( const string &name, const string & path, Directory * parent )
: HierarchyNode( name, parent ){
   if( parent != nullptr )
      _path = parent->Path() + name + '/';
   else _path = '/' + name;
   _showHidden = false;
}

const string & Directory::Path() const{
   return _path;
}

void Directory::RemoveNode( unsigned index ){
    _contents.erase( begin() + index );
}

void Directory::Append( const struct stat &buffer, const string &name, const string &path ){
   unique_ptr< HierarchyNode > node;
   bool add = false;
   if( name != ".." && ( name[ 0 ] != '.' || _showHidden ) && name != "." ){
      if( S_ISDIR( buffer.st_mode ) ){
         node = make_unique< Directory >( name, _path, this );
         add = true;
      }
      else if( S_ISREG( buffer.st_mode ) ){
         node = make_unique< File >( name, buffer.st_size, this );
         add = true;
      }
      else if( S_ISLNK( buffer.st_mode ) ){
         node = make_unique< SymLink >( name, path, this );
         add = true;
      }
      if( add ){
         auto it = lower_bound( _contents.begin(), _contents.end(), node, CompareNames );
         if( it != _contents.end() ) _contents.insert( it, move( node ) );
         else _contents.emplace_back( move( node ) );
      }
   }
}

bool Directory::CreateDir( const string & name ){
    string dir = _path + name;
    if( ::mkdir( dir.c_str(), 0755 ) == 0 ){
        unique_ptr< HierarchyNode > node = make_unique< Directory >( name, _path, this );
        auto it = lower_bound( _contents.begin(), _contents.end(), node, CompareNames );
        if( it != _contents.end() ) _contents.insert( it, move( node ) );
        else _contents.emplace_back( move( node ) );
        return true;
    }
    return false;
}

bool Directory::CreateFile( const string & name ){
    struct stat buf;
    string newFile = _path + name;
    if( stat( newFile.c_str(), &buf ) == -1 ){
        ofstream file( newFile );
        if( file.is_open() ){
            file << "";
            file.close();
            
            unique_ptr< HierarchyNode > node = make_unique< File >( name, 0, this );
            auto it = lower_bound( _contents.begin(), _contents.end(), node, CompareNames );
            if( it != _contents.end() ) _contents.insert( it, move( node ) );
            else _contents.emplace_back( move( node ) );
            return true;
        }
    }
    return false;
}
bool Directory::CreateLink( const string & name, const string & path ){
    if( symlink( path.c_str(), ( _path + name ).c_str() ) == 0 ){
        unique_ptr< HierarchyNode > node = make_unique< SymLink >( name, path, this );
        auto it = lower_bound( _contents.begin(), _contents.end(), node, CompareNames );
        if( it != _contents.end() ) _contents.insert( it, move( node ) );
        else _contents.emplace_back( move( node ) );
           return true;
    }
    return false;
}

bool Directory::__compareNames::operator()( const unique_ptr< HierarchyNode > &lhs, const unique_ptr< HierarchyNode > &rhs ){
   return lhs->Compare().compare( rhs->Compare() ) < 0;
}

bool Directory::LoadContents(){
   _contents.clear();
   if( !_name.empty() ) _contents.emplace_back( move( make_unique< Directory >( "..", "", nullptr ) ) );
   DIR *dir;
   string name, nodePath;
   struct dirent *sd;
   struct stat buf;
   dir = opendir( _path.c_str() );
   if( dir == nullptr ) return false;

   while( ( sd = readdir( dir ) ) ){
      name = sd->d_name;
      nodePath = _path + name;
      lstat( nodePath.c_str(), &buf );
      Append( buf, name, nodePath );
   }

   closedir( dir );

   return true;
}

string Directory::Show( int width ) const{
   if( _name.size() > ( unsigned long )( width - 8 ) ){
      string ret = "/";
      ret.append( _name, 0, width - 8 );
      return ret + "...";
   }
   else return '/' + _name;
}

string Directory::ShowPath( int width ) const{
   if( _path.size() > ( unsigned long )( width - 9 ) ){
      string ret = "/...";
      return ret.append( _path, _path.size() - ( width - 9 ), _path.size() );
   }
   else return _path;
}

bool Directory::Rename( const string &name ){
    LoadContents();
    string newDir = _parent->Path() + name;
    ::mkdir( newDir.c_str(), 0755 );

    for( unsigned i = 1; i < _contents.size(); i++ ){
        if( !_contents[ i ]->Move( newDir + '/' + _contents[ i ]->GetName() ) ) return false;
    }
    _name = name;
    ::rmdir( _path.c_str() );
    _path = _parent->Path() + name + '/';
    LoadContents();
    return true;
}

bool Directory::Erase(){
    LoadContents();
    for( unsigned i = 1; i < _contents.size(); i++ ){
        if( !_contents[ i ]->Erase() ) return false;
    }
    return ::rmdir( _path.c_str() ) == 0;
}

bool Directory::Copy( const string &path ){
    LoadContents();
    ::mkdir( path.c_str(), 0755 );
    for( unsigned i = 1; i < _contents.size(); i++ ){
        if( !_contents[ i ]->Copy( path + '/' + _contents[ i ]->GetName() ) ) return false;
    }
    
    return true;
}

bool Directory::Move( const string &path ){
    LoadContents();
    ::mkdir( path.c_str(), 0755 );

    for( unsigned i = 1; i < _contents.size(); i++ ){
        if( !_contents[ i ]->Move( path + '/' + _contents[ i ]->GetName() ) ) return false;
    }
    ::rmdir( _path.c_str() );

    return true;
}

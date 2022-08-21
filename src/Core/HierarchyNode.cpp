#include "HierarchyNode.hpp"

using namespace std;

HierarchyNode::HierarchyNode( const string &name, Directory * parent )
: _name( name ), _parent( parent ){}

string HierarchyNode::GetAbsolutePath( const string &path ) const{
   char buffer[ PATH_MAX ] = {0};
   if( realpath( path.c_str(), buffer ) == nullptr ) return "";
   else return buffer;
}
